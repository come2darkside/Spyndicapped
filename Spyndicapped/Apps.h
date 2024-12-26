#pragma once
#include <Windows.h>
#include <UIAutomationClient.h>
#include <UIAutomation.h>

class App
{
protected:
    ULONG eventCount;

public:
    App() : eventCount(0) {} 
    virtual ~App() {} 

    virtual HRESULT HandleEvent(IUIAutomationElement* pAutomationElement, EVENTID eventId) = 0;

    ULONG GetEventCount() const {
        return eventCount;
    }

    void IncrementEventCount() {
        InterlockedIncrement(&eventCount);
    }
};

