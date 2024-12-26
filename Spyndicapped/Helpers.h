#pragma once
#include <Windows.h>
#include <iostream>
#include <UIAutomationClient.h>
#include <unordered_map>

class Helpers {
public:
	static std::wstring EventIdToString(EVENTID eventID);
	static uint32_t hash(const std::wstring& data) noexcept;
	static std::wstring GetApplicationName(const std::wstring& fullPath);
};