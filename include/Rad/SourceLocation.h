#pragma once

template <class T>
struct SourceLocation
{
    SourceLocation(int line, const T* file, const T* function, const T* funcsig)
        : line(line)
        , file(file)
        , function(function)
        , funcsig(funcsig)
    {
    }

    int line;
    const T* file;
    const T* function;
    const T* funcsig;
};

#define SRC_LOC_A SourceLocation<char>(__LINE__, __FILE__, __FUNCTION__, __FUNCSIG__)
#define SRC_LOC_W SourceLocation<wchar_t>(__LINE__, L"" __FILE__, L"" __FUNCTION__, L"" __FUNCSIG__)

#ifdef _UNICODE
#define SrcLoc SourceLocation<wchar_t>
#define SRC_LOC SRC_LOC_W
#else
#define SrcLoc SourceLocation<char>
#define SRC_LOC SRC_LOC_A
#endif
