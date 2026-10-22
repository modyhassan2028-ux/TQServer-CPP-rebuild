// TitleModule module implementation - faithful ABI rebuild of Title.dll
// Registration sequence extracted verbatim from the decompiled ModuleCreate.
#include "title.h"
#include <new>

EXPORT_MODULE_FULL(title::CTitleModule,
pKernel->RegisterProcess(1130, pModule);
        pKernel->RegisterProcess(1002, pModule);
        pKernel->RegisterProcess(1003, pModule);
        pKernel->SetProcess(14, pModule->GetProcessor());)
