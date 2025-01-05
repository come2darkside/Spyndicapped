#include "Logger.h"


std::mutex logMutex;

void Log(const std::wstring& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (!g_LogFileName.empty()) {
        FILE* logFile = nullptr;
        errno_t err = _wfopen_s(&logFile, g_LogFileName.c_str(), L"a, ccs=UTF-16LE");
        if (logFile == nullptr || err != 0)
        {
            std::wcout << L"Can't create logfile" << std::endl;
            return;
        }
        _setmode(_fileno(logFile), _O_U16TEXT);
    

        switch (level) {
        case EMPTY:
            fwprintf(logFile, L"%ls\n", message.c_str());
            break;

        case INFO:
            fwprintf(logFile, L"[INFO] %ls\n", message.c_str());
            break;

        case DBG:
            if (g_DebugModeEnable) {
                fwprintf(logFile, L"[DEBUG] %ls\n", message.c_str());
            }
            break;

        case WARNING:
            fwprintf(logFile, L"[WARNING] %ls\n", message.c_str());
            break;

        default:
            break;
        }
        fclose(logFile);
    }
    else {
        switch (level) {
        case EMPTY:
            std::wcout << message << std::endl;
            break;
        case INFO:
            std::wcout << L"[INFO] " << message << std::endl;
            break;
        case DBG:
            if (g_DebugModeEnable) {
                std::wcout << L"[DEBUG] " << message << std::endl;
            }
            break;
        case WARNING:
            std::wcout << L"[WARNING] " << message << std::endl;
            break;
        default:
            break;
        }
    }
}
