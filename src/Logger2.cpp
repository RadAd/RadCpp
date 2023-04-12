#include <Rad/Logger.h>

#include <set>
#include <ctime>

// TODO
// Log to debug output
// Log to file

void LogInit()
{
    const LogLevel AllLogLevel[] = {
        LogLevel::Warning,
        LogLevel::Error,
    #ifdef _DEBUG
        LogLevel::Debug,
    #endif
        LogLevel::Trace,
    };

    for (LogLevel l : AllLogLevel)
    {
        LogRegister(LogTraceStdOutA, l);
        LogRegister(LogTraceStdOutW, l);
    }

    LogRegister(LogTraceMessageBoxA, LogLevel::Error);
    LogRegister(LogTraceMessageBoxW, LogLevel::Error);
}

std::set<LogTraceAT> g_loga[static_cast<int>(LogLevel::None)];
std::set<LogTraceWT> g_logw[static_cast<int>(LogLevel::None)];

void LogRegister(LogTraceAT lt, LogLevel l, bool reg)
{
    if (reg)
        g_loga[static_cast<int>(l)].insert(lt);
    else
        g_loga[static_cast<int>(l)].erase(lt);
}

void LogRegister(LogTraceWT lt, LogLevel l, bool reg)
{
    if (reg)
        g_logw[static_cast<int>(l)].insert(lt);
    else
        g_logw[static_cast<int>(l)].erase(lt);
}

void LogMessage(LogLevel l, SourceLocation<char> sl, const char* msg)
{
    for (LogTraceAT lt : g_loga[static_cast<int>(l)])
        lt(l, sl, msg);
}

void LogMessage(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg)
{
    for (LogTraceWT lt : g_logw[static_cast<int>(l)])
        lt(l, sl, msg);
}

void LogTraceStdOutA(LogLevel l, SourceLocation<char> sl, const char* msg)
{
    const std::time_t time = std::time({});
    std::tm localtm = {};
    /*std::*/localtime_s(&localtm, &time);

    std::string timestr(100, '_');
    const std::size_t sz = strftime(timestr.data(), timestr.size(), "\033[33m%y-%m-%d %OH:%OM:%OS\033[0m", &localtm);
    timestr.resize(sz);

    const char* levelstr = [l]() {
        switch (l)
        {
        case LogLevel::Warning: return "Warning";
        case LogLevel::Error: return "\033[31mError\033[0m";
        case LogLevel::Debug: return "Debug";
        case LogLevel::Trace: return "Trace";
        default: return "Unknown";
        }
    }();

    printf("%s-%s: %s at \033[33m%s:%d\033[0m in \033[33m%s\033[0m\n", timestr.c_str(), levelstr, msg, sl.file, sl.line, sl.funcsig);
}

void LogTraceStdOutW(LogLevel l, SourceLocation<wchar_t> sl, const wchar_t* msg)
{
    const std::time_t time = std::time({});
    std::tm localtm = {};
    /*std::*/localtime_s(&localtm, &time);

    std::wstring timestr(100, L'_');
    const std::size_t sz = wcsftime(timestr.data(), timestr.size(), L"\033[33m%y-%m-%d %OH:%OM:%OS\033[0m", &localtm);
    timestr.resize(sz);

    const wchar_t* levelstr = [l]() {
        switch (l)
        {
        case LogLevel::Warning: return L"Warning";
        case LogLevel::Error: return L"\033[31mError\033[0m";
        case LogLevel::Debug: return L"Debug";
        case LogLevel::Trace: return L"Trace";
        default: return L"Unknown";
        }
    }();

    wprintf(L"%s-%s: %s at \033[33m%s:%d\033[0m in \033[33m%s\033[0m\n", timestr.c_str(), levelstr, msg, sl.file, sl.line, sl.funcsig);
}

#include <Windows.h>

void LogTraceMessageBoxA(LogLevel l, SourceLocation<char> /*sl*/, const char* msg)
{
    const UINT icon = [l]() {
        switch (l)
        {
        case LogLevel::Warning: return MB_ICONWARNING;
        case LogLevel::Error: return MB_ICONERROR;
        default: return MB_ICONINFORMATION;
        }
    }();
    MessageBoxA(NULL, msg, "Title", MB_OK | icon);
}

void LogTraceMessageBoxW(LogLevel l, SourceLocation<wchar_t> /*sl*/, const wchar_t* msg)
{
    const UINT icon = [l]() {
        switch (l)
        {
        case LogLevel::Warning: return MB_ICONWARNING;
        case LogLevel::Error: return MB_ICONERROR;
        default: return MB_ICONINFORMATION;
        }
    }();
    MessageBoxW(NULL, msg, L"Title", MB_OK | icon);
}
