#pragma once
#include <Windows.h>
#include <UIAutomationClient.h>
#include <comdef.h>
#include <iostream>
#include <string>
#include <vector>
#include <atlbase.h>


class MyAutomationEventHandler : public IUIAutomationEventHandler
{
private:
	ULONG refCount;
public:
	MyAutomationEventHandler();
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppInterface);
	HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement* pAutomationElement, EVENTID eventID);
	static HRESULT STDMETHODCALLTYPE Deploy(wchar_t* windowName, DWORD pid);
};

