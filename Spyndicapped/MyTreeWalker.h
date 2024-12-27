#pragma once
#include <Windows.h>
#include <UIAutomationClient.h>

class MyTreeWalker
{
private:
	IUIAutomation* pAutomation = NULL;
	IUIAutomationTreeWalker* pWalker = NULL;

public:
	MyTreeWalker(IUIAutomation*);
	~MyTreeWalker();
	IUIAutomationElement* GetParent(IUIAutomationElement* child);
};

extern MyTreeWalker* g_pMyTreeWalker;
