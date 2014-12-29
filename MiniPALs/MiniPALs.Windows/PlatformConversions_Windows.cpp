#include "PlatformConversions_Windows.h"

Platform::String^ convertToPlatformString(std::string string)
{
	std::wstring wString = std::wstring(string.begin(), string.end());
	auto pString = ref new Platform::String(wString.data());
	return pString;
}