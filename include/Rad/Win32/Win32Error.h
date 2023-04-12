#pragma once

// https://gist.github.com/bbolli/710010adb309d5063111889530237d6d

#include <system_error>
#include <Windows.h>
#include <string>

/// Wrap the Win32 error code so we have a distinct type.
struct win32_error_code
{
    explicit win32_error_code(DWORD e = GetLastError()) noexcept : error(e) {}
    DWORD error;

    std::string message() const
    {
        return message(error);
    }

    std::wstring wmessage() const
    {
        return wmessage(error);
    }

    static std::string message(DWORD e, HMODULE h = NULL);
    static std::wstring wmessage(DWORD e, HMODULE h = NULL);
};

/// Return a static instance of the custom category.
extern std::error_category const& win32_category();

// Overload the global make_error_code() free function with our
// custom error. It will be found via ADL by the compiler if needed.
inline std::error_code make_error_code(win32_error_code const& we)
{
    return std::error_code(static_cast<int>(we.error), win32_category());
}

namespace std
{
    // Tell the C++ 11 STL metaprogramming that win32_error_code
    // is registered with the standard error code system.
    template <>
    struct is_error_code_enum<win32_error_code> : std::true_type {};
}

[[noreturn]] inline void throw_win32_system_error(DWORD e = GetLastError())
{
    throw std::system_error(win32_error_code(e));
}

[[noreturn]] inline void throw_win32_system_error(const std::string& Message, DWORD e = GetLastError())
{
    throw std::system_error(win32_error_code(e), Message);
}
