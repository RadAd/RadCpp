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

typedef void (*LogTraceAT)(LogLevel l, SourceLocationA sl, const char* msg);
typedef void  (*LogTraceWT)(LogLevel l, SourceLocationW sl, const wchar_t* msg);

void LogInit();

void LogRegister(LogTraceAT lt, LogLevel l, bool reg = true);
void LogRegister(LogTraceWT lt, LogLevel l, bool reg = true);

void LogMessage(LogLevel l, SourceLocationA sl, const char* msg);
void LogMessage(LogLevel l, SourceLocationW sl, const wchar_t* msg);

void LogTraceStdOutA(LogLevel l, SourceLocationA sl, const char* msg);
void LogTraceStdOutW(LogLevel l, SourceLocationW sl, const wchar_t* msg);
void LogTraceMessageBoxA(LogLevel l, SourceLocationA sl, const char* msg);
void LogTraceMessageBoxW(LogLevel l, SourceLocationW sl, const wchar_t* msg);
