#include <gtest/gtest.h>
#include <Rad/CompareNoCase.h>

TEST(TestCompareNoCase, CompareNoCase) {
    EXPECT_EQ(CompareNoCase("TEST1", "test1"), 0);
    EXPECT_EQ(CompareNoCase(L"TEST1", L"test1"), 0);
}

TEST(TestCompareNoCase, EqualNoCase) {
    EXPECT_TRUE(EqualNoCase("TEST1", "test1"));
    EXPECT_TRUE(EqualNoCase(L"TEST1", L"test1"));
}

TEST(TestCompareNoCase, FindNoCase) {
    EXPECT_EQ(FindNoCase("Quick brown fox", "BROWN"), 6);
    EXPECT_EQ(FindNoCase(L"Quick brown fox", L"BROWN"), 6);
}
