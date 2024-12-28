#include "Helpers.h"

std::wstring Helpers::ControlTypeIdToString(CONTROLTYPEID controlTypeId)
{
	static const std::unordered_map<CONTROLTYPEID, std::wstring> controlTypeIdMap = {
		{ UIA_AnnotationAnnotationTypeIdPropertyId, L"UIA_AnnotationAnnotationTypeIdPropertyId" },
		{ UIA_AnnotationAnnotationTypeNamePropertyId, L"UIA_AnnotationAnnotationTypeNamePropertyId" },
		{ UIA_AnnotationAuthorPropertyId, L"UIA_AnnotationAuthorPropertyId" },
		{ UIA_AnnotationDateTimePropertyId, L"UIA_AnnotationDateTimePropertyId" },
		{ UIA_AnnotationTargetPropertyId, L"UIA_AnnotationTargetPropertyId" },
		{ UIA_DockDockPositionPropertyId, L"UIA_DockDockPositionPropertyId" },
		{ UIA_DragDropEffectPropertyId, L"UIA_DragDropEffectPropertyId" },
		{ UIA_DragDropEffectsPropertyId, L"UIA_DragDropEffectsPropertyId" },
		{ UIA_DragIsGrabbedPropertyId, L"UIA_DragIsGrabbedPropertyId" },
		{ UIA_DragGrabbedItemsPropertyId, L"UIA_DragGrabbedItemsPropertyId" },
		{ UIA_DropTargetDropTargetEffectPropertyId, L"UIA_DropTargetDropTargetEffectPropertyId" },
		{ UIA_DropTargetDropTargetEffectsPropertyId, L"UIA_DropTargetDropTargetEffectsPropertyId" },
		{ UIA_ExpandCollapseExpandCollapseStatePropertyId, L"UIA_ExpandCollapseExpandCollapseStatePropertyId" },
		{ UIA_GridColumnCountPropertyId, L"UIA_GridColumnCountPropertyId" },
		{ UIA_GridItemColumnPropertyId, L"UIA_GridItemColumnPropertyId" },
		{ UIA_GridItemColumnSpanPropertyId, L"UIA_GridItemColumnSpanPropertyId" },
		{ UIA_GridItemContainingGridPropertyId, L"UIA_GridItemContainingGridPropertyId" },
		{ UIA_GridItemRowPropertyId, L"UIA_GridItemRowPropertyId" },
		{ UIA_GridItemRowSpanPropertyId, L"UIA_GridItemRowSpanPropertyId" },
		{ UIA_GridRowCountPropertyId, L"UIA_GridRowCountPropertyId" },
		{ UIA_LegacyIAccessibleChildIdPropertyId, L"UIA_LegacyIAccessibleChildIdPropertyId" },
		{ UIA_LegacyIAccessibleDefaultActionPropertyId, L"UIA_LegacyIAccessibleDefaultActionPropertyId" },
		{ UIA_LegacyIAccessibleDescriptionPropertyId, L"UIA_LegacyIAccessibleDescriptionPropertyId" },
		{ UIA_LegacyIAccessibleHelpPropertyId, L"UIA_LegacyIAccessibleHelpPropertyId" },
		{ UIA_LegacyIAccessibleKeyboardShortcutPropertyId, L"UIA_LegacyIAccessibleKeyboardShortcutPropertyId" },
		{ UIA_LegacyIAccessibleNamePropertyId, L"UIA_LegacyIAccessibleNamePropertyId" },
		{ UIA_LegacyIAccessibleRolePropertyId, L"UIA_LegacyIAccessibleRolePropertyId" },
		{ UIA_LegacyIAccessibleSelectionPropertyId, L"UIA_LegacyIAccessibleSelectionPropertyId" },
		{ UIA_LegacyIAccessibleStatePropertyId, L"UIA_LegacyIAccessibleStatePropertyId" },
		{ UIA_LegacyIAccessibleValuePropertyId, L"UIA_LegacyIAccessibleValuePropertyId" },
		{ UIA_MultipleViewCurrentViewPropertyId, L"UIA_MultipleViewCurrentViewPropertyId" },
		{ UIA_MultipleViewSupportedViewsPropertyId, L"UIA_MultipleViewSupportedViewsPropertyId" },
		{ UIA_RangeValueIsReadOnlyPropertyId, L"UIA_RangeValueIsReadOnlyPropertyId" },
		{ UIA_RangeValueLargeChangePropertyId, L"UIA_RangeValueLargeChangePropertyId" },
		{ UIA_RangeValueMaximumPropertyId, L"UIA_RangeValueMaximumProperty Id" },
		{ UIA_RangeValueMinimumPropertyId, L"UIA_RangeValueMinimumPropertyId" },
		{ UIA_RangeValueSmallChangePropertyId, L"UIA_RangeValueSmallChangePropertyId" },
		{ UIA_RangeValueValuePropertyId, L"UIA_RangeValueValuePropertyId" },
		{ UIA_ScrollHorizontalScrollPercentPropertyId, L"UIA_ScrollHorizontalScrollPercentPropertyId" },
		{ UIA_ScrollHorizontalViewSizePropertyId, L"UIA_ScrollHorizontalViewSizePropertyId" },
		{ UIA_ScrollVerticalScrollPercentPropertyId, L"UIA_ScrollVerticalScrollPercentPropertyId" },
		{ UIA_ScrollVerticalViewSizePropertyId, L"UIA_ScrollVerticalViewSizePropertyId" },
		{ UIA_SelectionSelectionPropertyId, L"UIA_SelectionSelectionPropertyId" },
		{ UIA_SelectionCanSelectMultiplePropertyId, L"UIA_SelectionCanSelectMultiplePropertyId" },
		{ UIA_SelectionIsSelectionRequiredPropertyId, L"UIA_SelectionIsSelectionRequiredPropertyId" },
		{ UIA_TableColumnHeadersPropertyId, L"UIA_TableColumnHeadersPropertyId" },
		{ UIA_TableItemColumnHeaderItemsPropertyId, L"UIA_TableItemColumnHeaderItemsPropertyId" },
		{ UIA_TableItemRowHeaderItemsPropertyId, L"UIA_TableItemRowHeaderItemsPropertyId" },
		{ UIA_TableRowHeadersPropertyId, L"UIA_TableRowHeadersPropertyId" },
		{ UIA_TextControlTypeId, L"UIA_TextControlTypeId" },
		{ UIA_ValueValuePropertyId, L"UIA_ValueValuePropertyId" },
		{ UIA_WindowCanMaximizePropertyId, L"UIA_WindowCanMaximizePropertyId" },
		{ UIA_WindowCanMinimizePropertyId, L"UIA_WindowCanMinimizePropertyId" },
		{ UIA_WindowIsModalPropertyId, L"UIA_WindowIsModalPropertyId" },
		{ UIA_WindowIsTopmostPropertyId, L"UIA_WindowIsTopmostPropertyId" },
		{ UIA_WindowWindowInteractionStatePropertyId, L"UIA_WindowWindowInteractionStatePropertyId" },
		{ UIA_WindowWindowVisualStatePropertyId, L"UIA_WindowWindowVisualStatePropertyId" }
	};

	auto it = controlTypeIdMap.find(controlTypeId);
	if (it != controlTypeIdMap.end()) {
		return it->second;
	}
	return L"Unknown Control Type";
}

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

std::wstring Helpers::GetDomainFromUrl(const std::wstring& url) {
	std::wstring domain = url;
	size_t pos = domain.find(L"://");
	if (pos != std::wstring::npos) {
		domain = domain.substr(pos + 3);
	}

	pos = domain.find(L"/");
	if (pos != std::wstring::npos) {
		domain = domain.substr(0, pos);
	}
	pos = domain.find(L":");
	if (pos != std::wstring::npos) {
		domain = domain.substr(0, pos);
	}
	return domain;
}