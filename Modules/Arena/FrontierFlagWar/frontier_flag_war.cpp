// FrontierFlagWarModule module implementation - faithful ABI rebuild of FrontierFlagWar.dll
// Registration sequence extracted verbatim from the decompiled ModuleCreate.
#include "frontier_flag_war.h"
#include <new>

EXPORT_MODULE_FULL(frontier_flag_war::CFrontierFlagWarModule,
pKernel->RegisterProcess(2502, pModule);
        pKernel->RegisterProcess(2506, pModule);
        pKernel->RegisterProcess(2504, pModule);
        pKernel->RegisterProcess(2507, pModule);
        pKernel->SetProcess(pModule->GetModuleIndex(), pModule->GetProcessor());
        pKernel->SetProcess(37, pModule->GetProcessor());)
