#include "pch.h"
#include "Utils.h"
#include <bitset>

namespace utils {

    /*!
     * 窄字节转宽字节
     *
     * \param str 窄字节
     * \param uCodePage 窄字节编码
     * \return 宽字节
     */
    std::wstring string_to_wstring(const std::string& str, UINT uCodePage) {
        int nLength = ::MultiByteToWideChar(uCodePage, 0, str.c_str(), -1, NULL, 0);
        if (0 == nLength) {
            throw std::exception("A2W Error");
        }
        std::wstring strW(nLength, L'\0');
        int nResult = ::MultiByteToWideChar(uCodePage, 0, str.c_str(), -1, &strW[0], nLength);
        if (nResult != nLength) {
            throw std::exception("A2W Error");
        }
        strW.resize(nLength - 1);
        return strW;
    }

    /*!
     * 宽字节转窄字节
     *
     * \param str 宽字节
     * \param uCodePage 窄字节编码
     * \return 窄字节
     */
    std::string wstring_to_string(const std::wstring& str, UINT uCodePage) {
        int nLength = ::WideCharToMultiByte(uCodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
        if (0 == nLength) {
            throw std::exception("W2A Error");
        }
        std::string strA(nLength, '\0');
        int nResult = ::WideCharToMultiByte(uCodePage, 0, str.c_str(), -1, &strA[0], nLength, NULL, NULL);
        if (nResult != nLength) {
            throw std::exception("W2A Error");
        }
        strA.resize(nLength - 1);
        return strA;
    }

    std::string gbkToUtf8(const char* src_str) {
        int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len + 1];
        memset(wstr, 0, len + 1);
        MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len + 1];
        memset(str, 0, len + 1);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
        std::string strTemp = str;
        if (wstr)
            delete[] wstr;
        if (str)
            delete[] str;
        return strTemp;
    }

    std::string utf8ToGbk(const char* src_str) {
        int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
        wchar_t* wszGBK = new wchar_t[len + 1];
        memset(wszGBK, 0, len * 2 + 2);
        MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
        len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
        char* szGBK = new char[len + 1];
        memset(szGBK, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
        std::string strTemp(szGBK);
        if (wszGBK)
            delete[] wszGBK;
        if (szGBK)
            delete[] szGBK;
        return strTemp;
    }

    std::wstring string2wstring(std::string str) {
        std::wstring result;
        //获取缓冲区大小，并申请空间，缓冲区大小按字符计算
        int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
        TCHAR* buffer = new TCHAR[len + 1];
        //多字节编码转换成宽字节编码
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
        buffer[len] = '\0'; //添加字符串结尾
        //删除缓冲区并返回值
        result.append(buffer);
        delete[] buffer;
        return result;
    }

    //将wstring转换成string
    std::string wstring2string(std::wstring wstr) {
        std::string result;
        //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的
        int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
        char* buffer = new char[len + 1];
        //宽字节编码转换成多字节编码
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
        buffer[len] = '\0';
        //删除缓冲区并返回值
        result.append(buffer);
        delete[] buffer;
        return result;
    }
    std::string charToBinary(char value) {
        //字符转化成二进制串
        std::bitset<8> bits{static_cast<unsigned long long>(value)};
        std::bitset<1> tmp;
        //二进制翻转
        for (int i = 0; i < 4; i++) {
            tmp[0] = bits[i];
            bits[i] = bits[7 - i];
            bits[7 - i] = tmp[0];
        }
        //输出
        return bits.to_string();

    }
    std::string charToHex(char value) { 
        std::string hexStr;
        static std::string str2{"0123456789abcdef"};
        int b;
        b = 0x0f & (value >> 4);
        char s1 = str2.at(b);
        hexStr.append(1, str2.at(b));
        b = 0x0f & value;
        hexStr.append(1, str2.at(b));
        char s2 = str2.at(b);
        return hexStr; 
    }
} // namespace utils
