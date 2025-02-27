#pragma once
#include <string_view>
#include <stringapiset.h>
#include <sphelper.h>
#include <system_error>

template <typename CharT>
constexpr bool EqualsIgnoreCase(std::basic_string_view<CharT> a, std::basic_string_view<CharT> b) noexcept
{
	if (a.size() != b.size())
		return false;
	const CharT* pa = a.data(), * pb = b.data(), * paend = pa + a.size();
	for (; pa != paend; pa++, pb++)
	{
		CharT ca = *pa, cb = *pb;
		if (ca >= 'A' && ca <= 'Z') ca += 'a' - 'A';
		if (cb >= 'A' && cb <= 'Z') cb += 'a' - 'A';
		if (ca != cb)
			return false;
	}
	return true;
}

// these two overloads are added because the template cannot accept types convertible to string_view

constexpr bool EqualsIgnoreCase(std::string_view a, std::string_view b) noexcept
{
	return EqualsIgnoreCase<char>(a, b);
}

constexpr bool EqualsIgnoreCase(std::wstring_view a, std::wstring_view b) noexcept
{
	return EqualsIgnoreCase<wchar_t>(a, b);
}

inline std::wstring StringToWString(std::string_view str, UINT codePage = CP_ACP)
{
	if (str.empty()) return {};
	int size = MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, str.data(), (int)str.size(), nullptr, 0);
	if (size == 0) throw std::system_error(GetLastError(), std::system_category());
	std::wstring ret;
	ret.resize_and_overwrite(size, [str, codePage](wchar_t* buf, size_t size)
		{
			return MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, str.data(), (int)str.size(), buf, (int)size);
		});
	return ret;
}

inline std::string WStringToString(std::wstring_view str, UINT codePage = CP_ACP)
{
	if (str.empty()) return {};
	int size = WideCharToMultiByte(codePage, 0, str.data(), (int)str.size(), nullptr, 0, nullptr, nullptr);
	if (size == 0) throw std::system_error(GetLastError(), std::system_category());
	std::string ret;
	ret.resize_and_overwrite(size, [str, codePage](char* buf, size_t size)
		{
			return WideCharToMultiByte(codePage, 0, str.data(), (int)str.size(), buf, (int)size, nullptr, nullptr);
		});
	return ret;
}

inline std::wstring UTF8ToWString(std::string_view str)
{
	return StringToWString(str, CP_UTF8);
}

inline std::string WStringToUTF8(std::wstring_view str)
{
	return WStringToString(str, CP_UTF8);
}

inline std::string UTF8ToAnsi(std::string_view str)
{
	return WStringToString(UTF8ToWString(str));
}

inline std::string AnsiToUTF8(std::string_view str)
{
	return WStringToUTF8(StringToWString(str));
}

inline std::string_view TrimWhitespaces(std::string_view stringview) noexcept
{
	const char* pStart = stringview.data(), * pEnd = pStart + stringview.size();
	for (; pStart != pEnd; pStart++)
	{
		if (!isspace(*pStart))
			break;
	}
	if (pStart == pEnd)
		return std::string_view();
	do
	{
		pEnd--;
		if (!isspace(*pEnd))
			break;
	} while (pEnd != pStart);
	return std::string_view(pStart, pEnd + 1);
}

inline HRESULT MergeIntoCoString(CSpDynamicString& destString, std::wstring_view str1, std::wstring_view str2) noexcept
{
	LPWSTR p = reinterpret_cast<LPWSTR>(CoTaskMemAlloc((str1.size() + str2.size() + 1) * sizeof(wchar_t)));
	if (!p) return E_OUTOFMEMORY;
	memcpy(p, str1.data(), str1.size() * sizeof(wchar_t));
	memcpy(p + str1.size(), str2.data(), str2.size() * sizeof(wchar_t));
	p[str1.size() + str2.size()] = L'\0';
	destString.m_psz = p;
	return S_OK;
}

inline std::wstring_view GetResString(UINT uID) noexcept
{
	HMODULE hThisModule = reinterpret_cast<HMODULE>(&__ImageBase);
	LPWSTR pStr = nullptr;
	int cch = LoadStringW(hThisModule, uID, reinterpret_cast<LPWSTR>(&pStr), 0);
	return std::wstring_view(pStr, cch);
}

inline std::string_view GetResData(LPCWSTR name, LPCWSTR type)
{
	HMODULE hThisModule = reinterpret_cast<HMODULE>(&__ImageBase);
	HRSRC hResInfo = FindResourceW(hThisModule, name, type);
	if (!hResInfo)
		throw std::system_error(GetLastError(), std::system_category());
	HGLOBAL hRes = LoadResource(hThisModule, hResInfo);
	if (!hRes)
		throw std::system_error(GetLastError(), std::system_category());
	DWORD size = SizeofResource(hThisModule, hResInfo);
	LPSTR pContent = static_cast<LPSTR>(LockResource(hRes));
	return std::string_view(pContent, size);
}
