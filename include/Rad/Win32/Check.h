#pragma once

#include "..\Logger.h"
#include "..\SourceLocation.h"
#include "..\Format.h"
#include "Win32Error.h"

void LogWin32(LogLevel l, LPCTSTR expr, DWORD e, const SrcLoc& sl)
{
    win32_error_code ec(e);
    LogMessage(l, sl, Format(TEXT("%s: 0x%08X: %s"), expr, ec.error, ec.wmessage().c_str()).c_str());
}

#define CHECK_WIN32(x) { if (!x) { const DWORD e = GetLastError(); LogWin32(LogLevel::Error, TEXT(#x), GetLastError(), SRC_LOC); } }
#define CHECK_WIN32_RET(x, y) { if (!x) { const DWORD e = GetLastError(); LogWin32(LogLevel::Error, TEXT(#x), e, SRC_LOC); return (y); } }
#define CHECK_WIN32_THROW(x, y) { if (!x) { const DWORD e = GetLastError(); LogWin32(LogLevel::Error, TEXT(#x), e, SRC_LOC); throw (y); } }
#define CHECK_HR(x)  { const HRESULT hr = (x); if (FAILED(hr)) LogWin32(LogLevel::Error, TEXT(#x), hr, SRC_LOC); }
#define CHECK_HR_RET(x, y)  { const HRESULT hr = (x); if (FAILED(hr)) { LogWin32(LogLevel::Error, TEXT(#x), hr, SRC_LOC); return (y); } }
#define CHECK_HR_THROW(x, y)  { const HRESULT hr = (x); if (FAILED(hr)) { LogWin32(LogLevel::Error, TEXT(#x), hr, SRC_LOC); throw (y); } }
