#include <Gosu/Directories.hpp>
#include <Gosu/WinUtility.hpp>
#include <cwchar>
#include <stdexcept>
#include <shlobj.h>

namespace
{
	std::wstring specialFolderPath(int csidl)
	{
		WCHAR buf[MAX_PATH + 2];
		if (!SHGetSpecialFolderPath(0, buf, csidl, TRUE))
			throw std::runtime_error("Error getting special folder path");
		std::size_t len = std::wcslen(buf);
		if (buf[len - 1] != '\\')
		{
			buf[len] = L'\\';
			buf[len + 1] = L'\0';
		}
		return buf;
	}
}

std::wstring Gosu::resourcePrefix()
{
	return Win::appDirectory();
}

std::wstring Gosu::sharedResourcePrefix()
{
	return Win::appDirectory();
}

std::wstring Gosu::userSettingsPrefix()
{
	return specialFolderPath(CSIDL_APPDATA);
}

std::wstring Gosu::userDocsPrefix()
{
	return specialFolderPath(CSIDL_PERSONAL);
}