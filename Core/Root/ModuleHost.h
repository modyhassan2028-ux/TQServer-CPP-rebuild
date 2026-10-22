// CModuleHost + CWorldKernelHost - the module-loading side of the original ABI.
//
// The original MsgServer builds every game-system DLL from Modules/<System>/
// and each DLL's exported ModuleCreate(kernel, index, r1, r2) registers its
// message types and processor with the world kernel. This host reproduces
// that wiring: it loads the DLLs, passes the kernel, records every
// RegisterProcess/SetProcess call, and ticks the modules.
#pragma once
#include "Common/IModule.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace gs {

class CWorldKernelHost : public IWorldKernel {
public:
    bool RegisterProcess(uint32_t dwMsgType, IModule* pModule) override;
    bool SetProcess(uint32_t dwMode, void* pProcessor) override;

    IModule* FindProcess(uint32_t dwMsgType) const;
    size_t MsgTypeCount() const { return m_oMsgHandlers.size(); }
    size_t ProcessorCount() const { return m_oProcessors.size(); }

private:
    std::unordered_map<uint32_t, IModule*> m_oMsgHandlers;
    std::unordered_map<uint32_t, void*> m_oProcessors;
};

class CModuleHost {
public:
    // Load every module DLL found in the directory (Windows: *.dll, POSIX: *.so)
    bool LoadDirectory(const char* pDirPath);
    // Poll modules (original: host calls OnProcess on each module per tick)
    void TickAll();
    void ShutdownAll();

    size_t Count() const { return m_oModules.size(); }
    CWorldKernelHost& Kernel() { return m_oKernel; }

    static CModuleHost& Instance();

private:
    struct LoadedModule {
        void* hLib;
        IModule* pModule;
        std::string sFile;
    };
    bool LoadOne(const std::string& sPath);

    CWorldKernelHost m_oKernel;
    std::vector<LoadedModule> m_oModules;
};

} // namespace gs
