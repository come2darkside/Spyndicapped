#include "Errors.h"

bool g_DebugModeEnable = false;

void PrintErrorFromHRESULT(HRESULT hr) {
	_com_error err(hr);
	LPCTSTR errMsg = err.ErrorMessage();

	std::wcout << L"[-] Err msg: " << errMsg << std::endl;
}

void Log(const std::wstring& message, LogLevel level) {

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