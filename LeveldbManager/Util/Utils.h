#pragma once

#include <iostream>
#include <process.h>
#include <Windows.h>

namespace utils {
	/*!
		 * խ�ֽ�ת���ֽ�
		 *
		 * \param str խ�ֽ�
		 * \param uCodePage խ�ֽڱ���
		 * \return ���ֽ�
		 */
	std::wstring string_to_wstring(const std::string& str, UINT uCodePage = CP_UTF8);

	/*!
	 * ���ֽ�תխ�ֽ�
	 *
	 * \param str ���ֽ�
	 * \param uCodePage խ�ֽڱ���
	 * \return խ�ֽ�
	 */
	std::string wstring_to_string(const std::wstring& str, UINT uCodePage = CP_UTF8);

	std::string gbkToUtf8(const char* src_str);

	std::string utf8ToGbk(const char* src_str);

	std::wstring string2wstring(std::string str);

    //��wstringת����string
	std::string wstring2string(std::wstring wstr);

	std::string charToBinary(char value);
    std::string charToHex(char value);

}

