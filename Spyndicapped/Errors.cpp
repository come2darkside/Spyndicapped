#include "Errors.h"

void PrintErrorFromHRESULT(HRESULT hr) {
	_com_error err(hr);
	LPCTSTR errMsg = err.ErrorMessage();

	std::wcout << L"[-] Err msg: " << errMsg << std::endl;
}
