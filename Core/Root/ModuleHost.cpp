#include "ModuleHost.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>

#if defined(_WIN32)
  #include <windows.h>
  typedef HMODULE LibHandle;
  static LibHandle OpenLib(const char* p) { return LoadLibraryA(p); }
  static void* LibSym(LibHandle h, const char* p) { return (void*)GetProcAddress(h, p); }
  static void CloseLib(LibHandle h) { FreeLibrary(h); }
#else
  #include <dlfcn.h>
  typedef void* LibHandle;
  static LibHandle OpenLib(const char* p) { return dlopen(p, RTLD_NOW | RTLD_LOCAL); }
  static void* LibSym(LibHandle h, const char* p) { return dlsym(h, p); }
  static void CloseLib(LibHandle h) { dlclose(h); }
#endif

#include <dirent.h>
#include <sys/stat.h>

namespace gs {

bool CWorldKernelHost::RegisterProcess(uint32_t dwMsgType, IModule* pModule) {
    m_oMsgHandlers[dwMsgType] = pModule;
    return true;
}

bool CWorldKernelHost::SetProcess(uint32_t dwMode, void* pProcessor) {
    m_oProcessors[dwMode] = pProcessor;
    return true;
}

IModule* CWorldKernelHost::FindProcess(uint32_t dwMsgType) const {
    auto it = m_oMsgHandlers.find(dwMsgType);
    return it == m_oMsgHandlers.end() ? nullptr : it->second;
}

CModuleHost& CModuleHost::Instance() {
    static CModuleHost s_oHost;
    return s_oHost;
}

bool CModuleHost::LoadOne(const std::string& sPath) {
    LibHandle hLib = OpenLib(sPath.c_str());
    if (!hLib) {
        std::cerr << "[ModuleHost] cannot load " << sPath << std::endl;
        return false;
    }
    using CreateFn = IModule* (*)(IWorldKernel*, uint32_t, void*, void*);
    CreateFn fnCreate = (CreateFn)LibSym(hLib, "ModuleCreate");
    if (!fnCreate) {
        std::cerr << "[ModuleHost] " << sPath << " has no ModuleCreate export" << std::endl;
        CloseLib(hLib);
        return false;
    }
    uint32_t dwIndex = (uint32_t)m_oModules.size();
    IModule* pModule = fnCreate(&m_oKernel, dwIndex, nullptr, nullptr);
    if (!pModule) {
        std::cerr << "[ModuleHost] " << sPath << " ModuleCreate failed" << std::endl;
        CloseLib(hLib);
        return false;
    }
    std::cout << "[ModuleHost] loaded " << pModule->GetModuleName()
              << " (" << sPath << ", index " << dwIndex << ")" << std::endl;
    m_oModules.push_back({(void*)hLib, pModule, sPath});
    return true;
}

bool CModuleHost::LoadDirectory(const char* pDirPath) {
    DIR* pDir = opendir(pDirPath);
    if (!pDir) {
        std::cerr << "[ModuleHost] cannot open module dir " << pDirPath << std::endl;
        return false;
    }
    std::vector<std::string> oFiles;
    while (struct dirent* e = readdir(pDir)) {
        std::string s = e->d_name;
        std::string sLower = s;
        std::transform(sLower.begin(), sLower.end(), sLower.begin(), ::tolower);
        const std::string sExt =
#if defined(_WIN32)
            ".dll";
#else
            ".so";
#endif
        if (sLower.size() > sExt.size() &&
            sLower.compare(sLower.size() - sExt.size(), sExt.size(), sExt) == 0)
            oFiles.push_back(s);
    }
    closedir(pDir);
    std::sort(oFiles.begin(), oFiles.end());
    for (const std::string& s : oFiles)
        LoadOne(std::string(pDirPath) + "/" + s);
    std::cout << "[ModuleHost] " << m_oModules.size() << " modules, "
              << m_oKernel.MsgTypeCount() << " message types registered" << std::endl;
    return !m_oModules.empty();
}

void CModuleHost::TickAll() {
    for (auto& m : m_oModules)
        if (m.pModule) m.pModule->OnProcess();
}

void CModuleHost::ShutdownAll() {
    for (auto& m : m_oModules) {
        if (m.pModule) {
            m.pModule->Shutdown();
            delete m.pModule;
            m.pModule = nullptr;
        }
    }
    for (auto& m : m_oModules) {
        if (m.hLib) {
            CloseLib((LibHandle)m.hLib);
            m.hLib = nullptr;
        }
    }
    m_oModules.clear();
}

} // namespace gs
