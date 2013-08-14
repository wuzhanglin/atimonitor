#pragma once

#include <windows.h>
#include <string>

LONG GetStringRegKey(HKEY hKey, const std::string &strValueName, std::string &strValue, const std::string &strDefaultValue);