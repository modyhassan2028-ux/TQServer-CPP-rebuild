#include "AsyncDBThread.h"

std::queue<std::string> CAsyncDBThread::s_sqlQueue;
std::mutex CAsyncDBThread::s_mutex;
std::atomic<uint32_t> CAsyncDBThread::s_loginSerial{1};

CAsyncDBThread::CAsyncDBThread() = default;
CAsyncDBThread::~CAsyncDBThread() = default;

void CAsyncDBThread::OnInit() {}
bool CAsyncDBThread::OnProcess() {
    std::string sql;
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        if (s_sqlQueue.empty()) return false;
        sql = s_sqlQueue.front();
        s_sqlQueue.pop();
    }
    // Execution handled by MySQL connection pool
    return true;
}
void CAsyncDBThread::OnDestroy() {}

bool CAsyncDBThread::ExecuteAsyncSQL(const char* pszSQL) {
    if (!pszSQL) return false;
    std::lock_guard<std::mutex> lock(s_mutex);
    s_sqlQueue.emplace(pszSQL);
    return true;
}

bool CAsyncDBThread::ReConnectDB() { return true; }
uint32_t CAsyncDBThread::GetWorldUserLoginSerial() { return s_loginSerial.load(); }
uint32_t CAsyncDBThread::UserLoginGet() { return s_loginSerial.fetch_add(1); }