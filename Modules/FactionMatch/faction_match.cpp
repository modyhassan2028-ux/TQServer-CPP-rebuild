// FactionMatchModule module implementation - faithful ABI rebuild of FactionMatch.dll
// Registration sequence extracted verbatim from the decompiled ModuleCreate.
#include "faction_match.h"
#include <new>

EXPORT_MODULE_FULL(factionmatch::CFactionMatchModule,
pKernel->RegisterProcess(2330, pModule);
        pKernel->RegisterProcess(2333, pModule);
        pKernel->RegisterProcess(1003, pModule);
        pKernel->SetProcess(24, pModule->GetProcessor());)
