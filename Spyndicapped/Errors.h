#pragma once
#include <Windows.h>
#include <iostream>
#include <comdef.h>

enum LogLevel {
    EMPTY,
    INFO,
    DBG,
    WARNING
};

extern bool g_DebugModeEnable;

void PrintErrorFromHRESULT(HRESULT hr);
void Log(const std::wstring& message, LogLevel level);