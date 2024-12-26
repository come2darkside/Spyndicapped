#pragma once
#include <Windows.h>
#include <iostream>
#include <comdef.h>
#include <UIAutomationClient.h>
#include <fstream>
#include <codecvt>
#include <locale>
#include <mutex>

extern std::wstring g_LogFileName;
extern bool g_DebugModeEnable;

enum LogLevel {
    EMPTY,
    INFO,
    DBG,
    WARNING
};

void Log(const std::wstring& message, LogLevel level);

