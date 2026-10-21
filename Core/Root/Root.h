#pragma once

class __declspec(dllexport) CRoot {
public:
    CRoot();
    ~CRoot();
    static CRoot* CurrentInstanceGet();
    static bool GameCreate();
private:
    static CRoot* s_pInstance;
};