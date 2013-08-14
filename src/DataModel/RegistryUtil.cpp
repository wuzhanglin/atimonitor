
#include "RegistryUtil.h"

LONG GetStringRegKey(HKEY key, const std::string &name, std::string &value, const std::string &default)
{
    value = default;
    TCHAR buffer[512];
    DWORD size = sizeof(buffer);
    ULONG err;
    err = RegQueryValueEx(key, name.c_str(), 0, NULL, (LPBYTE)buffer, &size);
    if (ERROR_SUCCESS == err)
    {
        value = buffer;
    }
    return err;
}