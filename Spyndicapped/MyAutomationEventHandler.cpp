#include "MyAutomationEventHandler.h"
#include "Errors.h"

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