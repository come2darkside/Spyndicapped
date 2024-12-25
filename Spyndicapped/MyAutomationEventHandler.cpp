#include "MyAutomationEventHandler.h"
#include "Errors.h"
#include "Find.h"

MyAutomationEventHandler::MyAutomationEventHandler() : refCount(1)
{

}

ULONG STDMETHODCALLTYPE MyAutomationEventHandler::AddRef()
{
	return InterlockedIncrement(&refCount);
}

ULONG STDMETHODCALLTYPE MyAutomationEventHandler::Release()
{
	ULONG refCount = InterlockedDecrement(&refCount);
	if (refCount == 0)
	{
		delete this;
		return 0;
	}
	return refCount;
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::QueryInterface(REFIID riid, void** ppInterface)
{
	if (riid == __uuidof(IUnknown))
		*ppInterface = static_cast<IUIAutomationEventHandler*>(this);
	else if (riid == __uuidof(IUIAutomationEventHandler))
		*ppInterface = static_cast<IUIAutomationEventHandler*>(this);
	else
	{
		*ppInterface = NULL;
		return E_NOINTERFACE;
	}
	this->AddRef();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::HandleAutomationEvent(IUIAutomationElement* pSender, EVENTID eventID)
{
	BSTR name;
	HRESULT res = pSender->get_CurrentName(&name);
	if (FAILED(res))
	{
		return ERROR_ACCESS_DENIED;
	}
	std::wstring wname(name, SysStringLen(name));
	std::wcout << L"[+] Event from window: " << wname << std::endl;
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::Deploy(wchar_t* windowName, DWORD pid)
{
	CComPtr<IUIAutomation> pAutomation;
	CComPtr<IUIAutomationElement> pAutomationElement;
	HRESULT hr;
	BSTR bName;
	
	hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&pAutomation);
	if (FAILED(hr))
	{
		Log(L"CoCreateInstance() failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}
	Log(L"IUIAutomation creating success", DBG);

	if (windowName)
	{
		pAutomationElement = Finder::GetUIAElementByName(pAutomation, windowName);
		if (pAutomationElement == NULL)
		{
			Log(L"Cant find GUI by windowname!!!. Try to use --pid", WARNING);
			return E_INVALIDARG;
		}

		Log(L"Spying " + std::wstring(windowName), DBG);
	} else if (pid != 0)
	{
		pAutomationElement = Finder::GetUIAElementByPID(pAutomation, pid);
		if (pAutomationElement == NULL)
		{
			Log(L"Cant find GUI by pid!!!. Try to use --windowname", WARNING);
			return E_INVALIDARG;
		}

		Log(L"Spying " + std::to_wstring(pid), DBG);
	}
	else
	{
		// Monitor all windows
		Log(L"Monitoring all windows", INFO);
		pAutomation->GetRootElement(&pAutomationElement);
	}

	hr = pAutomationElement->get_CurrentName(&bName);
	
	if (SUCCEEDED(hr))
	{
		std::wstring wname(bName, SysStringLen(bName));
		Log(L"Window Name: " + wname, INFO);
	}


	return 0;
}