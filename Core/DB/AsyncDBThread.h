#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>

class __declspec(dllexport) CAsyncDBThread {
public:
    CAsyncDBThread();
    virtual ~CAsyncDBThread();

    virtual void OnInit();
    virtual bool OnProcess();
    virtual void OnDestroy();

    static bool ExecuteAsyncSQL(const char* pszSQL);
    static bool ReConnectDB();
    static uint32_t GetWorldUserLoginSerial();
    static uint32_t UserLoginGet();

private:
    static std::queue<std::string> s_sqlQueue;
    static std::mutex s_mutex;
    static std::atomic<uint32_t> s_loginSerial;
};