#include "MyPropertyChangedEventHandler.h"
#include "Logger.h"
#include "Finder.h"

MyPropertyChangedEventHandler::MyPropertyChangedEventHandler() : refCount(1), eventCount(0)
{
}

ULONG STDMETHODCALLTYPE MyPropertyChangedEventHandler::AddRef()
{
	return InterlockedIncrement(&refCount);
}

ULONG STDMETHODCALLTYPE MyPropertyChangedEventHandler::Release()
{
	ULONG refCount = InterlockedDecrement(&refCount);
	if (refCount == 0)
	{
		delete this;
		return 0;
	}
	return refCount;
}

ULONG STDMETHODCALLTYPE MyPropertyChangedEventHandler::GetEventCount()
{
	return eventCount;
}

VOID STDMETHODCALLTYPE MyPropertyChangedEventHandler::IncrementEventCount()
{
	InterlockedIncrement(&eventCount);
}

HRESULT STDMETHODCALLTYPE MyPropertyChangedEventHandler::QueryInterface(REFIID riid, void** ppInterface)
{
	if (riid == __uuidof(IUnknown))
		*ppInterface = static_cast<IUnknown*>(this);
	else if (riid == __uuidof(IUIAutomationPropertyChangedEventHandler))
		*ppInterface = static_cast<IUIAutomationPropertyChangedEventHandler*>(this);
	else
	{
		*ppInterface = NULL;
		return E_NOINTERFACE;
	}
	this->AddRef();
	return S_OK;
}

void STDMETHODCALLTYPE MyPropertyChangedEventHandler::SetEventTimeout(int seconds)
{
	this->eventTimeout = std::chrono::seconds(seconds);
}

std::chrono::seconds MyPropertyChangedEventHandler::GetEventTimeout()
{
	return this->eventTimeout;
}

HRESULT STDMETHODCALLTYPE MyPropertyChangedEventHandler::HandlePropertyChangedEvent(IUIAutomationElement* pAutomationElement, PROPERTYID prodId, VARIANT vVar)
{
	auto now = std::chrono::steady_clock::now();

	if (now - lastEventTime < GetEventTimeout())
	{
		//Log(L"Too fast events...", DBG);
		return ERROR_SUCCESS;
	}

	lastEventTime = now;

	HRESULT hr;
	DWORD pid = Finder::GetPIDByUIAutomationElement(pAutomationElement);

	if (pid == -1)
	{
		Log(L"MyAutomationEventHandler::HandleAutomationEvent() invalid PID Received", DBG);
		return ERROR_SUCCESS;
	}

	std::wstring wsFileName = Finder::GetModuleNameFromPid(pid);
	if (wsFileName.empty())
	{
		Log(L"MyAutomationEventHandler::HandleAutomationEvent() invalid wsProcName Received", DBG);
		return ERROR_SUCCESS;
	}

	IncrementEventCount();

	//todo

	return ERROR_SUCCESS;
}

HRESULT STDMETHODCALLTYPE MyPropertyChangedEventHandler::Deploy(IUIAutomation* pAutomation, IUIAutomationElement* pAutomationElement, int timeout)
{
	Log(L"Started spying using MyPropertyChangedEventHandler", INFO);
	while (1){};
	return ERROR_SUCCESS;
}