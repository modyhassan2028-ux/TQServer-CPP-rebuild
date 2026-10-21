#pragma once
#include <cstdint>

namespace gs {
    class IModule {
    public:
        virtual ~IModule() = default;
        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;
        virtual void OnProcess() = 0;
        virtual const char* GetModuleName() const = 0;
    };
}

#define EXPORT_MODULE(ModuleClass) \
    extern "C" __declspec(dllexport) gs::IModule* ModuleCreate() { \
        return new ModuleClass(); \
    }