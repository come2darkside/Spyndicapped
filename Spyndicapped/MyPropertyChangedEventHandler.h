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

class MyPropertyChangedEventHandler : public IUIAutomationPropertyChangedEventHandler {
private:
	ULONG refCount = 0;
	ULONG eventCount = 0;
	std::chrono::seconds eventTimeout;

public:
	std::chrono::steady_clock::time_point lastEventTime;

	MyPropertyChangedEventHandler();
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface);
	ULONG STDMETHODCALLTYPE GetEventCount();
	void STDMETHODCALLTYPE IncrementEventCount();
	void STDMETHODCALLTYPE SetEventTimeout(int);
	std::chrono::seconds STDMETHODCALLTYPE GetEventTimeout();
	HRESULT STDMETHODCALLTYPE HandlePropertyChangedEvent(IUIAutomationElement*, PROPERTYID, VARIANT);
	static HRESULT STDMETHODCALLTYPE Deploy(IUIAutomation*, IUIAutomationElement*, int);
};


