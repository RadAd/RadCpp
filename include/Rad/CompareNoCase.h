#pragma once

#include <string_view>
#include <algorithm>
#include <cctype>
#include <cwctype>

inline int CompareNoCase(std::string_view a, std::string_view b)
{
    auto r = std::mismatch(a.begin(), a.end(), b.begin(), b.end(), [](auto ca, auto cb) { return std::tolower(ca) == std::tolower(cb); });
    if (r.first == a.end() && r.second == b.end())
        return 0;
    else if (r.first == a.end())
        return -1;
    else if (r.second == b.end())
        return 1;
    else
        return [](auto a, auto b) { return (a > b) - (a < b); } (std::tolower(*r.first), std::tolower(*r.second));
}

inline int CompareNoCase(std::wstring_view a, std::wstring_view b)
{
    auto r = std::mismatch(a.begin(), a.end(), b.begin(), b.end(), [](auto ca, auto cb) { return std::towlower(ca) == std::towlower(cb); });
    if (r.first == a.end() && r.second == b.end())
        return 0;
    else if (r.first == a.end())
        return -1;
    else if (r.second == b.end())
        return 1;
    else
        return [](auto a, auto b) { return (a > b) - (a < b); } (std::towlower(*r.first), std::towlower(*r.second));
}

inline bool EqualNoCase(std::string_view a, std::string_view b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](auto ca, auto cb) { return std::tolower(ca) == std::tolower(cb); });
}

inline bool EqualNoCase(std::wstring_view a, std::wstring_view b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](auto ca, auto cb) { return std::towlower(ca) == std::towlower(cb); });
}

inline size_t FindNoCase(std::string_view haystack, std::string_view needle)
{
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end(), [](char ch1, char ch2) { return std::tolower(ch1) == std::tolower(ch2); });
    return (it == haystack.end()) ? std::wstring_view::npos : (it - haystack.begin());
}

inline size_t FindNoCase(std::wstring_view haystack, std::wstring_view needle)
{
    auto it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end(), [](wchar_t ch1, wchar_t ch2) { return std::towlower(ch1) == std::towlower(ch2); });
    return (it == haystack.end()) ? std::wstring_view::npos : (it - haystack.begin());
}
