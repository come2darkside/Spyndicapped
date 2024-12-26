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
#include <chrono>

extern bool g_IgnoreHandlers;

class MyAutomationEventHandler : public IUIAutomationEventHandler
{
private:
	ULONG refCount;
    ULONG eventCount;
	std::chrono::seconds eventTimeout;
	
	void HandleFirefox(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleChrome(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleExplorer(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);
	void HandleOther(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID);

public:
	std::chrono::steady_clock::time_point lastEventTime;

	MyAutomationEventHandler();
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface);
	HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement* pAutomationElement, EVENTID eventID);
    ULONG STDMETHODCALLTYPE GetEventCount();
    void STDMETHODCALLTYPE IncrementEventCount();
	void STDMETHODCALLTYPE SetEventTimeout(int);
	std::chrono::seconds STDMETHODCALLTYPE GetEventTimeout();
	static HRESULT STDMETHODCALLTYPE Deploy(IUIAutomation*, IUIAutomationElement*, int);
};


