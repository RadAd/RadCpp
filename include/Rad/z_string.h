#include <cstring>
#include <cwchar>
#include <stdexcept>

struct zstring_sentinel
{
};

template <class T>
class basic_z_string_view
{
public:
    using pointer_t = const T*;
    using size_t = std::size_t;
    using iterator = pointer_t;
    static const size_t npos = static_cast<size_t>(-1);

    basic_z_string_view(pointer_t p)
        : p(p)
    {
    }

    pointer_t c_str() const
    {
        return p;
    }

    pointer_t data() const
    {
        return p;
    }

    size_t size() const { return length(); }
    size_t length() const;
    bool empty() const;
    int compare(basic_z_string_view q) const;
    int compare(size_t pos, size_t len, basic_z_string_view q) const;
    size_t find(T c, size_t pos = 0) const;
    size_t find(basic_z_string_view q, size_t pos = 0) const;
    //pointer_t find(basic_z_string_view q, size_t pos, size_t n) const;
    size_t rfind(T c, size_t pos = npos) const;
    //size_t rfind(basic_z_string_view q, size_t pos = 0) const;
    size_t find_first_of(char c, size_t pos = 0) const { return find(c, pos); }
    size_t find_first_of(basic_z_string_view s, size_t pos = 0) const;
    //size_t find_first_of(basic_z_string_view s, size_t pos, size_t n) const;
    size_t find_last_of(char c, size_t pos = npos) const { return rfind(c, pos); }
    size_t find_last_of(basic_z_string_view s, size_t pos = npos) const
    {
        size_t i = npos;
        size_t j = find_first_of(s);
        while (j <= pos && j != npos)
        {
            i = j;
            j = find_first_of(s, i + 1);
        }
        return i;
    }
    //size_t find_last_of(basic_z_string_view s, size_t pos, size_t n) const;
    size_t find_first_not_of(char c, size_t pos = 0) const;
    size_t find_first_not_of(basic_z_string_view s, size_t pos = 0) const;
    //size_t find_first_not_of(basic_z_string_view s, size_t pos, size_t n) const;
    size_t find_last_not_of(char c, size_t pos = npos) const
    {
        size_t i = npos;
        size_t j = find_first_not_of(c);
        while (j <= pos && j != npos)
        {
            i = j;
            j = find_first_not_of(c, i + 1);
        }
        return i;
    }
    size_t find_last_not_of(basic_z_string_view s, size_t pos = npos) const
    {
        size_t i = npos;
        size_t j = find_first_not_of(s);
        while (j <= pos && j != npos)
        {
            i = j;
            j = find_first_not_of(s, i + 1);
        }
        return i;
    }
    //size_t find_last_not_of(basic_z_string_view s, size_t pos, size_t n) const;
    basic_z_string_view substr(size_t pos = 0) const { return p + pos; }


    //int collate(pointer_t q) const;
    //size_t span(pointer_t q) const;
    //size_t cspan(pointer_t q) const;
    //pointer_t pbreak(pointer_t breakset) const;

    iterator begin() const { return p; }
    //iterator end() const { return p + length(); }
    zstring_sentinel end() const { return {}; }

    const T& at(size_t i) const { if (i >= length()) throw std::out_of_range(); return p[i]; }
    const T& front() const { return p[0]; }
    const T& back() const { return p[length() - 1]; }

    const T& operator[](size_t i) const { return p[i]; }

private:
    size_t to_index(pointer_t e) const
    {
        return e == nullptr ? npos : e - p;
    }

    pointer_t p;
};

#if 0
template <class T>
inline int operator<=>(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b);
}
#else

template <class T>
inline bool operator==(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b) == 0;
}

template <class T>
inline bool operator<(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b) < 0;
}

template <class T>
inline bool operator<=(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b) <= 0;
}

template <class T>
inline bool operator>(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b) > 0;
}

template <class T>
inline bool operator>=(basic_z_string_view<T> a, basic_z_string_view<T> b)
{
    return a.compare(b) >= 0;
}
#endif

// ----- char

typedef basic_z_string_view<char> z_string_view;

inline bool operator!=(z_string_view::iterator it, zstring_sentinel)
{
    return *it != '\0';
}

template <>
inline size_t basic_z_string_view<char>::length() const
{
    return std::strlen(p);
}

template <>
inline bool basic_z_string_view<char>::empty() const
{
    return *p == '\0';
}

template <>
inline size_t basic_z_string_view<char>::find(char c, const size_t pos) const
{
    return to_index(std::strchr(p + pos, c));
}

template <>
inline size_t basic_z_string_view<char>::find(basic_z_string_view q, const size_t pos) const
{
    return to_index(std::strstr(p + pos, q.p));
}

template <>
inline size_t basic_z_string_view<char>::rfind(const char c, const size_t pos) const
{
#if 0
    const size_t r = to_index(std::strrchr(p, c));
    return r < pos ? r : npos;  // TODO a bit wasteful to search beyond pos but npos would be the most common pos value
#elif 0
    if (pos == npos)
        return to_index(std::strrchr(p, c));
    else
    {
        size_t i = npos;
        size_t j = 0;
        for (const char x : *this)
        {
            if (x == c)
                i = j;
            if (j >= pos)
                break;
            ++j;
        }
        return i;
    }
#else
    if (pos == npos)
        return to_index(std::strrchr(p, c));
    else
    {
        size_t i = npos;
        size_t j = find(c);
        while (j <= pos && j != npos)
        {
            i = j;
            j = find(c, i + 1);
        }
        return i;
    }
#endif
}

template <>
inline size_t basic_z_string_view<char>::find_first_of(basic_z_string_view s, const size_t pos) const
{
    const size_t f = std::strcspn(p + pos, s.p) + pos;
    return p[f] == '\0' ? npos : f;
}

template <>
inline size_t basic_z_string_view<char>::find_first_not_of(char c, const size_t pos) const
{
    size_t i = pos;
    while (p[i] == c)
        ++i;
    return p[i] == '\0' ? npos : i;
}

template <>
inline size_t basic_z_string_view<char>::find_first_not_of(basic_z_string_view s, const size_t pos) const
{
    const size_t f = std::strspn(p + pos, s.p) + pos;
    return p[f] == '\0' ? npos : f;
}

template <>
inline int basic_z_string_view<char>::compare(basic_z_string_view q) const
{
    return std::strcmp(p, q.p);
}

template <>
inline int basic_z_string_view<char>::compare(const size_t pos, const size_t len, basic_z_string_view q) const
{
    return std::strncmp(p + pos, q.p, len);
}

inline z_string_view make_z_string_view(z_string_view::pointer_t s)
{
    return s;
}

// ----- wchar_t

typedef basic_z_string_view<wchar_t> z_wstring_view;

inline bool operator!=(z_wstring_view::iterator it, zstring_sentinel)
{
    return *it != L'\0';
}

template <>
inline size_t basic_z_string_view<wchar_t>::length() const
{
    return std::wcslen(p);
}

template <>
inline bool basic_z_string_view<wchar_t>::empty() const
{
    return *p == L'\0';
}

template <>
inline size_t basic_z_string_view<wchar_t>::find(const wchar_t c, size_t pos) const
{
    return to_index(std::wcschr(p + pos, c));
}

template <>
inline size_t basic_z_string_view<wchar_t>::find(basic_z_string_view q, const size_t pos) const
{
    return to_index(std::wcsstr(p + pos, q.p));
}

template <>
inline size_t basic_z_string_view<wchar_t>::rfind(const wchar_t c, const size_t pos) const
{
#if 0
    const size_t r = to_index(std::wcsrchr(p, c));
    return r < pos ? r : npos;  // TODO a bit wasteful to search beyond pos but npos would be the most common pos value
#elif 0
    if (pos == npos)
        return to_index(std::wcsrchr(p, c));
    else
    {
        size_t i = npos;
        size_t j = 0;
        for (const wchar_t x : *this)
        {
            if (x == c)
                i = j;
            if (j >= pos)
                break;
            ++j;
        }
        return i;
    }
#else
    if (pos == npos)
        return to_index(std::wcsrchr(p, c));
    else
    {
        size_t i = npos;
        size_t j = find(c);
        while (j <= pos)
        {
            i = j;
            j = find(c, i + 1);
        }
        return i;
    }
#endif
}

template <>
inline size_t basic_z_string_view<wchar_t>::find_first_of(basic_z_string_view s, const size_t pos) const
{
    const size_t f = std::wcscspn(p + pos, s.p);
    return p[f] == L'\0' ? npos : f;
}

template <>
inline size_t basic_z_string_view<wchar_t>::find_first_not_of(basic_z_string_view s, const size_t pos) const
{
    const size_t f = std::wcsspn(p + pos, s.p);
    return p[f] == L'\0' ? npos : f;
}

template <>
inline int basic_z_string_view<wchar_t>::compare(basic_z_string_view q) const
{
    return std::wcscmp(p, q.p);
}

template <>
inline int basic_z_string_view<wchar_t>::compare(const size_t pos, const size_t len, basic_z_string_view q) const
{
    return std::wcsncmp(p + pos, q.p, len);
}

inline z_wstring_view make_z_string_view(z_wstring_view::pointer_t s)
{
    return s;
}
