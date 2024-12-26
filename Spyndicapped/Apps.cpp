#include "Apps.h"
#include "MyAutomationEventHandler.h"
#include "Logger.h"

void MyAutomationEventHandler::HandleFirefox(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"Ff!" + std::to_wstring(eventID), INFO);
}

void MyAutomationEventHandler::HandleChrome(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"Todo :))", INFO);
}

void MyAutomationEventHandler::HandleExplorer(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"Todo :))", INFO);
}

void MyAutomationEventHandler::HandleOther(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"HI!!!", INFO);
}