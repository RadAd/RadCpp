#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>

#if 0 // Auto convert to underlying pointer
template<class d>
struct unique_ptr : public std::unique_ptr<typename d::pointer, d>
{
    using std::unique_ptr<typename d::pointer, d>::unique_ptr;
    using std::unique_ptr<typename d::pointer, d>::get;
    operator typename d::pointer() const { return get(); }
};
#endif

#if 0 // Cant use a function as a template parameter
template <class T, void(F*)(T*)>
struct deleter_function
{
    void operator()(T* t) { F(t); }
};
#endif

#define DefineDeleter(t, f) \
struct t##Deleter \
{ \
    typedef t pointer; \
    void operator()(t h) { f(h); } \
}; \
typedef std::unique_ptr<t##Deleter::pointer, t##Deleter> Unique##t

DefineDeleter(HDC, DeleteDC);
DefineDeleter(HMENU, DestroyMenu);
DefineDeleter(HBITMAP, DeleteObject);
DefineDeleter(HPEN, DeleteObject);
DefineDeleter(HBRUSH, DeleteObject);

struct DCReleaser
{
    struct Data
    {
        HWND hWnd;
        HDC  hDC;

        operator bool() const
        {
            return hDC != NULL;
        }

        Data& operator=(HDC h)
        {
            hDC = h;
            return *this;
        }

        operator HDC() const
        {
            return hDC;
        }
    };

    typedef Data pointer;

    void operator()(Data h)
    {
        ReleaseDC(h.hWnd, h.hDC);
    }
};

inline std::unique_ptr<DCReleaser::pointer, DCReleaser> MakeGetDC(HWND hWnd)
{
    return std::unique_ptr<DCReleaser::pointer, DCReleaser>({ hWnd, GetDC(hWnd) });
}

// TODO This should go in a devcontext header
struct ObjectSelecter
{
    struct Data
    {
        HDC  hDC;
        HGDIOBJ hObj;

        operator bool() const
        {
            return hObj != NULL;
        }

        Data& operator=(HGDIOBJ h)
        {
            hObj = h;
            return *this;
        }

        operator HGDIOBJ() const
        {
            return hObj;
        }
    };

    typedef Data pointer;

    void operator()(Data h)
    {
        SelectObject(h.hDC, h.hObj);
    }
};

inline std::unique_ptr<ObjectSelecter::pointer, ObjectSelecter> SelectTempObject(HDC hDC, HGDIOBJ hObj)
{
    return std::unique_ptr<ObjectSelecter::pointer, ObjectSelecter>({ hDC, SelectObject(hDC, hObj) });
}
