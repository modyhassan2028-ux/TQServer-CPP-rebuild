// TotemModule module implementation - faithful ABI rebuild of Totem.dll
// Registration sequence extracted verbatim from the decompiled ModuleCreate.
#include "totem.h"
#include <new>

EXPORT_MODULE_FULL(totem::CTotemModule,
pKernel->RegisterProcess(2203, pModule);
        pKernel->RegisterProcess(2202, pModule);
        pKernel->RegisterProcess(2204, pModule);
        pKernel->SetProcess(21, pModule->GetProcessor());)
