// modules_load_test.cpp - load every generated module DLL natively and verify
// its ModuleCreate registers EXACTLY the message types / process modes that
// were extracted verbatim from the original decompiled DLLs (abi.json).
#include "Common/IModule.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#if defined(_WIN32)
  #include <windows.h>
  #define OPEN_LIB(p) LoadLibraryA(p)
  #define LIB_SYM(h, s) (void*)GetProcAddress(h, s)
  #define CLOSE_LIB(h) FreeLibrary(h)
  #define EXT ".dll"
#else
  #include <dlfcn.h>
  #define OPEN_LIB(p) dlopen(p, RTLD_NOW | RTLD_LOCAL)
  #define LIB_SYM(h, s) dlsym(h, s)
  #define CLOSE_LIB(h) dlclose(h)
  #define EXT ".so"
#endif

static int g_failures = 0;
static int g_loaded = 0;

struct Expect {
    std::string sDll;
    std::vector<uint32_t> oMsgs, oModes;
    bool bModeFromIndex = false;
};

// kernel mock: records registrations
class MockKernel : public gs::IWorldKernel {
public:
    bool RegisterProcess(uint32_t dwMsgType, gs::IModule* pModule) override {
        m_oMsgs.push_back(dwMsgType);
        (void)pModule;
        return true;
    }
    bool SetProcess(uint32_t dwMode, void* pProcessor) override {
        m_oModes.push_back(dwMode);
        (void)pProcessor;
        return true;
    }
    std::vector<uint32_t> m_oMsgs, m_oModes;
};

int main(int argc, char** argv) {
    const char* pModDir = argc > 1 ? argv[1] : "build_native/Modules";
    const char* pAbi = argc > 2 ? argv[2] : "tools/modules/abi.json";

    // parse the abi.json manifest (flat, generator-controlled format)
    std::vector<Expect> oExpects;
    {
        FILE* f = fopen(pAbi, "r");
        if (!f) { fprintf(stderr, "cannot open %s\n", pAbi); return 1; }
        char buf[1 << 20];
        size_t n = fread(buf, 1, sizeof(buf) - 1, f);
        buf[n] = 0;
        fclose(f);
        std::string s(buf);
        // each record: { "folder": "...", ... "dll": "...", "msgs": [...], "modes": [...] }
        size_t p = 0;
        while ((p = s.find("\"dll\"", p)) != std::string::npos) {
            Expect e;
            size_t q = s.find('"', s.find(':', p) + 1);
            size_t q2 = s.find('"', q + 1);
            e.sDll = s.substr(q + 1, q2 - q - 1);          // e.g. Title.dll
            auto parse_list = [&](const char* key, std::vector<uint32_t>& out) {
                size_t k = s.find(key, p);
                if (k == std::string::npos || k > s.find('}', q2)) return;
                size_t b = s.find('[', k), e2 = s.find(']', b);
                size_t i = b + 1;
                while (i < e2) {
                    if (isdigit((unsigned char)s[i])) {
                        out.push_back((uint32_t)strtoul(s.c_str() + i, nullptr, 10));
                        while (i < e2 && s[i] != ',') i++;
                    } else i++;
                }
            };
            parse_list("\"msgs\"", e.oMsgs);
            parse_list("\"modes\"", e.oModes);
            e.bModeFromIndex = s.find("\"mode_from_index\": true", q2) < s.find('}', q2);
            oExpects.push_back(e);
            p = q2;
        }
    }

    DIR* d = opendir(pModDir);
    if (!d) { fprintf(stderr, "cannot open %s\n", pModDir); return 1; }
    std::vector<std::string> files;
    const size_t nExt = strlen(EXT);
    while (dirent* e = readdir(d)) {
        std::string s = e->d_name;
        if (s.size() > nExt && s.compare(s.size() - nExt, nExt, EXT) == 0) files.push_back(s);
    }
    closedir(d);
    std::sort(files.begin(), files.end());

    for (const std::string& f : files) {
        std::string path = std::string(pModDir) + "/" + f;
        void* h = OPEN_LIB(path.c_str());
        if (!h) { fprintf(stderr, "FAIL load %s\n", path.c_str()); ++g_failures; continue; }
        auto create = (gs::IModule * (*)(gs::IWorldKernel*, uint32_t, void*, void*))LIB_SYM(h, "ModuleCreate");
        if (!create) { fprintf(stderr, "FAIL %s: no ModuleCreate\n", f.c_str()); CLOSE_LIB(h); ++g_failures; continue; }

        MockKernel k;
        gs::IModule* m = create(&k, 0, nullptr, nullptr);
        if (!m) { fprintf(stderr, "FAIL %s: ModuleCreate returned null\n", f.c_str()); CLOSE_LIB(h); ++g_failures; continue; }
        m->OnProcess();   // tick must not crash
        delete m;
        CLOSE_LIB(h);
        ++g_loaded;

        // verify against the manifest entry with the same dll name
        std::string stem = f.substr(0, f.size() - strlen(EXT));
        const Expect* pE = nullptr;
        for (auto& e : oExpects) {
            std::string dllStem = e.sDll.substr(0, e.sDll.size() - 4);  // ".dll"
            if (dllStem == stem) { pE = &e; break; }
        }
        if (!pE) { fprintf(stderr, "FAIL %s: no manifest entry\n", f.c_str()); ++g_failures; continue; }

        std::vector<uint32_t> gotMsgs = k.m_oMsgs, gotModes = k.m_oModes;
        std::sort(gotMsgs.begin(), gotMsgs.end());
        std::sort(gotModes.begin(), gotModes.end());
        std::vector<uint32_t> wantMsgs = pE->oMsgs, wantModes = pE->oModes;
        if (pE->bModeFromIndex) wantModes.push_back(0);  // the loader passes index 0 in this test
        std::sort(wantMsgs.begin(), wantMsgs.end());
        std::sort(wantModes.begin(), wantModes.end());
        if (gotMsgs != wantMsgs || gotModes != wantModes) {
            fprintf(stderr, "FAIL %s: msgs/modes mismatch (got %zu msgs/%zu modes, want %zu/%zu)\n",
                    f.c_str(), gotMsgs.size(), gotModes.size(), wantMsgs.size(), wantModes.size());
            ++g_failures;
        }
    }

    printf("modules load test: %d loaded, %d failures (manifest: %zu systems)\n",
           g_loaded, g_failures, oExpects.size());
    return g_failures ? 1 : 0;
}
