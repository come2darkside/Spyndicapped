#pragma once
#include <Windows.h>
#include <UIAutomationClient.h>
#include <comdef.h>
#include <iostream>
#include <string>
#include <vector>
#include <atlbase.h>
#include <functional>
#include <unordered_map>

extern bool g_IgnoreHandlers;

class MyAutomationEventHandler : public IUIAutomationEventHandler
{
private:
	ULONG refCount;
    ULONG eventCount;
	void HandleFirefox(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleChrome(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleExplorer(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleOther(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);

public:
	MyAutomationEventHandler();
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface);
	HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement* pAutomationElement, EVENTID eventID);
    ULONG STDMETHODCALLTYPE GetEventCount();
    void STDMETHODCALLTYPE IncrementEventCount();
	static HRESULT STDMETHODCALLTYPE Deploy(wchar_t* windowName, DWORD pid);
};


