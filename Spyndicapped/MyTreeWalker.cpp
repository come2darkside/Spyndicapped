#include "MyTreeWalker.h"
#include "Logger.h"
#include "Errors.h"

MyTreeWalker::MyTreeWalker(IUIAutomation* pUIAutomation)
{
	if (pUIAutomation == NULL)
	{
		Log(L"Failed to create TreeWalker. pUIAutomation was NULL", WARNING);
		return;
	}

	HRESULT hr = pUIAutomation->get_RawViewWalker(&pWalker);
	if (FAILED(hr))
	{
		Log(L"Failed to create TreeWalker.", WARNING);
		PrintErrorFromHRESULT(hr);
		return;
	}
}

MyTreeWalker::~MyTreeWalker()
{
	if (pWalker != NULL)
	{
		pWalker->Release();
	}
}

IUIAutomationElement* MyTreeWalker::GetParent(IUIAutomationElement* pChild)
{
	IUIAutomationElement* pParent;

	if (pWalker == NULL)
	{
		Log(L"pWalker was null", WARNING);
		return pParent;
	}

	HRESULT hr = pWalker->GetParentElement(pChild, &pParent);
	if (FAILED(hr))
	{
		Log(L"Failed to get parent.", WARNING);
		PrintErrorFromHRESULT(hr);
	}
	return pParent;
}