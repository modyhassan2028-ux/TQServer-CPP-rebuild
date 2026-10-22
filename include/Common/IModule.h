#pragma once
#include <cstdint>

namespace gs {

// ---------------------------------------------------------------------------
// IWorldKernel - the host-side interface every module DLL receives.
//
// Faithful to the original ABI recovered from the decompiled DLLs:
//   ModuleCreate(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex,
//                void* pReserved1, void* pReserved2)
// Every module's init calls, verbatim from the decompiled C:
//   kernel->RegisterProcess(msgId, this)   // decompiled: kernel->vt+8 / +0x10
//   kernel->SetProcess(mode, pProcessor)    // decompiled: kernel->vt+0x18
// ---------------------------------------------------------------------------
class IModule;

class IWorldKernel {
public:
    virtual ~IWorldKernel() = default;

    // Register the module as the handler of a message type.
    virtual bool RegisterProcess(uint32_t dwMsgType, IModule* pModule) = 0;
    // Attach the module's message processor to a kernel processing mode.
    virtual bool SetProcess(uint32_t dwMode, void* pProcessor) = 0;
};

// ---------------------------------------------------------------------------
// IModule - base class of every module DLL (original gs::IModule vftable).
// ---------------------------------------------------------------------------
class IModule {
public:
    virtual ~IModule() = default;
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void OnProcess() = 0;
    virtual const char* GetModuleName() const = 0;
};

// Legacy export used by the pre-module Syndicate/Trade stubs (no kernel arg).
#define EXPORT_MODULE(ModuleClass) \
    extern "C" gs::IModule* ModuleCreate(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex, void*, void*) { \
        (void)pKernel; (void)dwModuleIndex; \
        auto* pModule = new (std::nothrow) ModuleClass(); \
        if (!pModule) return nullptr; \
        if (!pModule->Initialize()) { delete pModule; return nullptr; } \
        return pModule; \
    }

// Full original ABI export with the exact registration sequence the
// decompiled ModuleCreate performs (reg code runs BEFORE Initialize,
// matching the original: ctor -> init(registration) -> Initialize).
#define EXPORT_MODULE_FULL(ModuleClass, REG_CODE) \
    extern "C" gs::IModule* ModuleCreate(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex, void* pReserved1, void* pReserved2) { \
        (void)pReserved1; (void)pReserved2; \
        auto* pModule = new (std::nothrow) ModuleClass(pKernel, dwModuleIndex); \
        if (!pModule) return nullptr; \
        REG_CODE \
        if (!pModule->Initialize()) { delete pModule; return nullptr; } \
        return pModule; \
    }

} // namespace gs
