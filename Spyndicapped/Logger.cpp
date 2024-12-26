#include "Logger.h"


std::wstring g_LogFileName;
bool g_DebugModeEnable = false; 
std::mutex logMutex;

void Log(const std::wstring& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (!g_LogFileName.empty()) {
        std::wofstream logFile(g_LogFileName, std::ios::app);
        logFile.imbue(std::locale(""));

        if (logFile.is_open()) {
            switch (level) {
            case EMPTY:
                logFile << message << std::endl;
                break;
            case INFO:
                logFile << L"[INFO] " << message << std::endl;
                break;
            case DBG:
                if (g_DebugModeEnable) {
                    logFile << L"[DEBUG] " << message << std::endl;
                }
                break;
            case WARNING:
                logFile << L"[WARNING] " << message << std::endl;
                break;
            default:
                break;
            }
            logFile.close();
        }
        else {
            std::wcerr << L"[WARNING] Can't open LOG File " << g_LogFileName << std::endl;
        }
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
