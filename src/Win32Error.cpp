#include <Rad/Win32/Win32Error.h>

std::string win32_error_code::message(DWORD e, HMODULE h)
{
    char error[256];
    auto len = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | (h != NULL ? FORMAT_MESSAGE_FROM_HMODULE : 0), h,
        e, 0, error, static_cast<DWORD>(std::size(error)),
        NULL);
    if (len == 0)
        return "N/A";
    // trim trailing newline
    while (len && (error[len - 1] == '\r' || error[len - 1] == '\n'))
        --len;
    return std::string(error, len);
}

std::wstring win32_error_code::wmessage(DWORD e, HMODULE h)
{
    wchar_t error[256];
    auto len = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | (h != NULL ? FORMAT_MESSAGE_FROM_HMODULE : 0), h,
        e, 0, error, static_cast<DWORD>(std::size(error)),
        NULL);
    if (len == 0)
        return L"N/A";
    // trim trailing newline
    while (len && (error[len - 1] == L'\r' || error[len - 1] == L'\n'))
        --len;
    return std::wstring(error, len);
}

namespace
{
    /// The Win32 error code category.
    class win32_error_category : public std::error_category
    {
    public:
        /// Return a short descriptive name for the category.
        char const* name() const noexcept override final { return "Win32Error"; }

        /// Return what each error code means in text.
        std::string message(int c) const override final
        {
            return win32_error_code::message(static_cast<DWORD>(c));
        }
    };
}

extern std::error_category const& win32_category()
{
    static ::win32_error_category c;
    return c;
}
