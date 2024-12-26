#include "Helpers.h"



std::wstring Helpers::EventIdToString(EVENTID eventID) {

    static const std::unordered_map<EVENTID, std::wstring> eventIdMap = {
        { UIA_ActiveTextPositionChangedEventId, L"UIA_ActiveTextPositionChangedEventId" },
        { UIA_AsyncContentLoadedEventId, L"UIA_AsyncContentLoadedEventId" },
        { UIA_AutomationFocusChangedEventId, L"UIA_AutomationFocusChangedEventId" },
        { UIA_AutomationPropertyChangedEventId, L"UIA_AutomationPropertyChangedEventId" },
        { UIA_ChangesEventId, L"UIA_ChangesEventId" },
        { UIA_Drag_DragCancelEventId, L"UIA_Drag_DragCancelEventId" },
        { UIA_Drag_DragCompleteEventId, L"UIA_Drag_DragCompleteEventId" },
        { UIA_Drag_DragStartEventId, L"UIA_Drag_DragStartEventId" },
        { UIA_DropTarget_DragEnterEventId, L"UIA_DropTarget_DragEnterEventId" },
        { UIA_DropTarget_DragLeaveEventId, L"UIA_DropTarget_DragLeaveEventId" },
        { UIA_DropTarget_DroppedEventId, L"UIA_DropTarget_DroppedEventId" },
        { UIA_HostedFragmentRootsInvalidatedEventId, L"UIA_HostedFragmentRootsInvalidatedEventId" },
        { UIA_InputDiscardedEventId, L"UIA_InputDiscardedEventId" },
        { UIA_InputReachedOtherElementEventId, L"UIA_InputReachedOtherElementEventId" },
        { UIA_InputReachedTargetEventId, L"UIA_InputReachedTargetEventId" },
        { UIA_Invoke_InvokedEventId, L"UIA_Invoke_InvokedEventId" },
        { UIA_LayoutInvalidatedEventId, L"UIA_LayoutInvalidatedEventId" },
        { UIA_LiveRegionChangedEventId, L"UIA_LiveRegionChangedEventId" },
        { UIA_MenuClosedEventId, L"UIA_MenuClosedEventId" },
        { UIA_MenuModeEndEventId, L"UIA_MenuModeEndEventId" },
        { UIA_MenuModeStartEventId, L"UIA_MenuModeStartEventId" },
        { UIA_MenuOpenedEventId, L"UIA_MenuOpenedEventId" },
        { UIA_NotificationEventId, L"UIA_NotificationEventId" },
        { UIA_Selection_InvalidatedEventId, L"UIA_Selection_InvalidatedEventId" },
        { UIA_SelectionItem_ElementAddedToSelectionEventId, L"UIA_SelectionItem_ElementAddedToSelectionEventId" },
        { UIA_SelectionItem_ElementRemovedFromSelectionEventId, L"UIA_SelectionItem_ElementRemovedFromSelectionEventId" },
        { UIA_SelectionItem_ElementSelectedEventId, L"UIA_SelectionItem_ElementSelectedEventId" },
        { UIA_StructureChangedEventId, L"UIA_StructureChangedEventId" },
        { UIA_SystemAlertEventId, L"UIA_SystemAlertEventId" },
        { UIA_Text_TextChangedEventId, L"UIA_Text_TextChangedEventId" },
        { UIA_Text_TextSelectionChangedEventId, L"UIA_Text_TextSelectionChangedEventId" },
        { UIA_TextEdit_ConversionTargetChangedEventId, L"UIA_TextEdit_ConversionTargetChangedEventId" },
        { UIA_TextEdit_TextChangedEventId, L"UIA_TextEdit_TextChangedEventId" },
        { UIA_ToolTipClosedEventId, L"UIA_ToolTipClosedEventId" },
        { UIA_ToolTipOpenedEventId, L"UIA_ToolTipOpenedEventId" },
        { UIA_Window_WindowClosedEventId, L"UIA_Window_WindowClosedEventId" },
        { UIA_Window_WindowOpenedEventId, L"UIA_Window_WindowOpenedEventId" }
    };

    auto it = eventIdMap.find(eventID);
    if (it != eventIdMap.end()) {
        return it->second;
    }
    else {
        return L"Unknown Event";
    }
}

uint32_t Helpers::hash(const std::wstring& data) noexcept {
    uint32_t hash = 5381;

    for (wchar_t c : data) {
        hash = ((hash << 5) + hash) + static_cast<uint32_t>(c);
    }

    return hash;
}

std::wstring Helpers::GetApplicationName(const std::wstring& fullPath) {
    size_t lastSlashPos = fullPath.find_last_of(L"\\");
    if (lastSlashPos != std::wstring::npos) {
        return fullPath.substr(lastSlashPos + 1);

    }
    return fullPath;
}

std::wstring Helpers::GetCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm localTime;
    localtime_s(&localTime, &now_c);


    std::wostringstream oss;
    oss << L'['
        << std::put_time(&localTime, L"%Y-%m-%d") 
        << L" | "
        << std::put_time(&localTime, L"%H:%M:%S") 
        << L']';

    return oss.str();
}

std::wstring Helpers::ConvertToLower(const std::wstring& input)
{
    std::wstring output = input;
    std::transform(input.begin(), input.end(), output.begin(), ::tolower);
    return output; 
}