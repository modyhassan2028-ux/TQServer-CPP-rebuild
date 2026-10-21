#include "Root.h"

CRoot* CRoot::s_pInstance = nullptr;

CRoot::CRoot() { s_pInstance = this; }
CRoot::~CRoot() { if (s_pInstance == this) s_pInstance = nullptr; }

CRoot* CRoot::CurrentInstanceGet() { return s_pInstance; }
bool CRoot::GameCreate() {
    if (!s_pInstance) {
        new CRoot();
    }
    return true;
}

extern "C" __declspec(dllexport) CRoot* CurrentInstanceGet() {
    return CRoot::CurrentInstanceGet();
}

extern "C" __declspec(dllexport) bool GameCreate() {
    return CRoot::GameCreate();
}