#include <gtest/gtest.h>
#include <Rad/Format.h>

TEST(TestFormat, Format) {
    EXPECT_EQ(Format("Hello %s", "World"), "Hello World");
    EXPECT_EQ(Format("Hello %d", 100), "Hello 100");
    EXPECT_EQ(Format(L"Hello %s", L"World"), L"Hello World");
    EXPECT_EQ(Format(L"Hello %d", 100), L"Hello 100");
}

TEST(TestFormat, Format2) {
    std::string s1;
    Format(s1, "Hello %s", "World");
    EXPECT_EQ(s1, "Hello World");
    Format(s1, "Hello %d", 100);
    EXPECT_EQ(s1, "Hello 100");
    std::wstring s2;
    Format(s2, L"Hello %s", L"World");
    EXPECT_EQ(s2, L"Hello World");
    Format(s2, L"Hello %d", 100);
    EXPECT_EQ(s2, L"Hello 100");
}

TEST(TestFormat, FormatTime) {
    const tm time = { 0, 0, 12, 25, 11, 93 };
    EXPECT_EQ(Format("%x", time), "12/25/93");
    EXPECT_EQ(Format("%X", time), "12:00:00");
}
