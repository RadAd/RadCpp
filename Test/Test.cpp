#include <gtest/gtest.h>
#include <Rad/Logger.h>

class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    void SetUp() override
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
        LogInit();
    }

    void TearDown() override
    {
    }
};

testing::Environment* const env = testing::AddGlobalTestEnvironment(new Environment);
