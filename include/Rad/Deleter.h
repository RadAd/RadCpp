#pragma once

#include <cstdio>
#include <memory>

struct FileDeleter
{
    void operator()(FILE* f) const noexcept { std::fclose(f); }
};

typedef std::unique_ptr<FILE, FileDeleter> FilePtr;

template <class T, class U>
class out_ptr
{
public:
    typedef std::unique_ptr<T, U> unique_ptr;

    out_ptr(unique_ptr& up)
        : up(up), p(nullptr)
    {
    }

    ~out_ptr()
    {
        up.reset(p);
    }

    operator typename unique_ptr::pointer* ()
    {
        return &p;
    }

private:
    unique_ptr& up;
    typename unique_ptr::pointer p;
};

template <class T, class U>
out_ptr<T, U> p(std::unique_ptr<T, U>& up)
{
    return out_ptr<T, U>(up);
}

template<class T, class U>
typename out_ptr<T, U> operator&(std::unique_ptr<T, U>& up)
{
    return out_ptr<T, U>(up);
}

template<class T, class U>
typename std::unique_ptr<T, U>::pointer operator-(std::unique_ptr<T, U>& up)
{
    return up.get();
}
