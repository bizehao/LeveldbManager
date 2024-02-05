#pragma once

#include <iostream>
#include <process.h>
#include <Windows.h>

namespace utils {
	/*!
		 * 窄字节转宽字节
		 *
		 * \param str 窄字节
		 * \param uCodePage 窄字节编码
		 * \return 宽字节
		 */
	std::wstring string_to_wstring(const std::string& str, UINT uCodePage = CP_UTF8);

	/*!
	 * 宽字节转窄字节
	 *
	 * \param str 宽字节
	 * \param uCodePage 窄字节编码
	 * \return 窄字节
	 */
	std::string wstring_to_string(const std::wstring& str, UINT uCodePage = CP_UTF8);

	std::string gbkToUtf8(const char* src_str);

	std::string utf8ToGbk(const char* src_str);

	std::wstring string2wstring(std::string str);

    //将wstring转换成string
	std::string wstring2string(std::wstring wstr);

	std::string charToBinary(char value);
    std::string charToHex(char value);

}

