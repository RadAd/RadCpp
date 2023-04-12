#pragma once
#include <string>

#include "SourceLocation.h"

enum class LogLevel
{
    Warning,
    Error,
    Debug,
    Trace,
    None,
};

typedef void (*LogTraceAT)(LogLevel l, SourceLocation<char> sl, const char* msg);
typedef void  (*LogTraceWT)(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg);

void LogInit();

void LogRegister(LogTraceAT lt, LogLevel l, bool reg = true);
void LogRegister(LogTraceWT lt, LogLevel l, bool reg = true);

void LogMessage(LogLevel l, SourceLocation<char> sl, const char* msg);
void LogMessage(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg);

void LogTraceStdOutA(LogLevel l, SourceLocation<char> sl, const char* msg);
void LogTraceStdOutW(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg);
void LogTraceMessageBoxA(LogLevel l, SourceLocation<char> sl, const char* msg);
void LogTraceMessageBoxW(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg);
