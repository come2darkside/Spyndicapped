#include "Find.h"
#include "Errors.h"

std::wstring GetModuleNameFromPid(DWORD pid) {

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

	if (hProcess == NULL) {
		return L"";
	}

	HMODULE hMods[1024];
	DWORD cbNeeded;

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
		wchar_t moduleName[MAX_PATH];
		if (GetModuleFileNameEx(hProcess, hMods[0], moduleName, sizeof(moduleName) / sizeof(wchar_t))) {
			CloseHandle(hProcess);
			return std::wstring(moduleName);
		}
	}

	CloseHandle(hProcess); 
	return L"";
}

ULONG FindWindows()
{
	HRESULT hr;
	int length = 0;

	CComPtr<IUIAutomation> pAutomation;
	CComPtr<IUIAutomationElement> pTargetElement;
	CComPtr<IUIAutomationElementArray> pElementsArray;
	CComPtr<IUIAutomationCondition> pCondition;

	hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
	if (FAILED(hr))
	{
		Log(L"CoCreateInstance() failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}
	Log(L"IUIAutomation creating success", DBG);

	hr = pAutomation->GetRootElement(&pTargetElement);
	if (FAILED(hr))
	{
		Log(L"pAutomation->GetRootElement() failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}
	Log(L"IUIAutomation->GetRootElement() creating success", DBG);

	hr = pAutomation->CreateTrueCondition(&pCondition);
	if (FAILED(hr))
	{
		Log(L"pAutomation->CreateTrueCondition() failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}
	Log(L"IUIAutomation->CreateTrueCondition() success", DBG);

	hr = pTargetElement->FindAll(TreeScope_Children, pCondition, &pElementsArray);
	if (FAILED(hr))
	{
		Log(L"pAutomation->FindAll() failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}
	
	
	pElementsArray->get_Length(&length);
	Log(L"Found active windows: " + std::to_wstring(length), INFO);

	for (int i = 0; i < length; i++)
	{
		CComPtr<IUIAutomationElement> pChildEl;
		hr = pElementsArray->GetElement(i, &pChildEl);

		if (FAILED(hr))
		{
			Log(L"pElementsArray->GetElement() failed", DBG);
			continue;
		}

		BSTR bWindowName;
		hr = pChildEl->get_CurrentName(&bWindowName);
		if (FAILED(hr))
		{
			Log(L"pChildEl->get_CurrentName() failed", DBG);
			continue;
		}

		std::wstring wsWindowName(bWindowName, SysStringLen(bWindowName));
		
		if (wsWindowName.length() == 0)
		{
			wsWindowName = L"<Empty>";
		}

		VARIANT vPid;
		hr = pChildEl->GetCurrentPropertyValue(UIA_ProcessIdPropertyId, &vPid);
		if (FAILED(hr))
		{
			Log(L"pChildEl->GetCurrentPropertyValue(PID) failed", DBG);
			continue;
		}

		if (V_VT(&vPid) == VT_I4)
		{
			Log(
				L"[" + std::to_wstring(i) + L"] " +
				L" | PID: " + std::to_wstring(V_I4(&vPid)) +
				L" | Name: " + GetModuleNameFromPid(V_I4(&vPid)) +
				L" | Window name: " + wsWindowName +
				L" |",
				EMPTY
			);
		}
		else {
			Log(
				L"[" + std::to_wstring(i) + L"] " +
				L"| PID: Unknown " +
				L"| Window name: Unknown |",
				EMPTY
			);
		}
	}

	return 0;
}