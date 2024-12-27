#pragma once
#include <Windows.h>
#include <iostream>
#include <UIAutomationClient.h>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>


class Helpers {
public:
	static std::wstring ControlTypeIdToString(CONTROLTYPEID controlTypeId);
	static std::wstring EventIdToString(EVENTID eventID);
	static uint32_t hash(const std::wstring& data) noexcept;
	static std::wstring GetApplicationName(const std::wstring& fullPath);
	static std::wstring GetCurrentDateTime();
	static std::wstring ConvertToLower(const std::wstring& string);
};