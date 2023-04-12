#include <gtest/gtest.h>
#include <Rad/z_string.h>

TEST(TestZString, Length) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.length(), 5);
}

TEST(TestZString, Empty) {
    z_string_view z1 = "Hello";
    z_string_view z2 = "";

    EXPECT_FALSE(z1.empty());
    EXPECT_TRUE(z2.empty());
}

TEST(TestZString, Iterate) {
    z_string_view z1 = "Hello";

    int count = 0;
    for (char c : z1)
        ++count;

    EXPECT_EQ(count, 5);
}

TEST(TestZString, Equals) {
    z_string_view z1 = "Hello";
    z_string_view z2 = "Hello";

    EXPECT_EQ(z1, z2);
}

TEST(TestZString, CompareLen) {
    z_string_view z1 = "Hello";
    z_string_view z2 = "Help";

    EXPECT_EQ(z1.compare(0, 3, z2), 0);
}

TEST(TestZString, Find) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.find('l'), 2);
}

TEST(TestZString, RFind) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.rfind('l'), 3);
    EXPECT_EQ(z1.rfind('o', 2), z_string_view::npos);
    EXPECT_EQ(z1.rfind('l', 2), 2);
}

TEST(TestZString, FindFirstOf) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.find_first_of('l'), 2);
    EXPECT_EQ(z1.find_first_of('x'), z_string_view::npos);
    EXPECT_EQ(z1.find_first_of('e', 1), 1);
    EXPECT_EQ(z1.find_first_of('l', 1), 2);
    EXPECT_EQ(z1.find_first_of("lo"), 2);
    EXPECT_EQ(z1.find_first_of("xy"), z_string_view::npos);
    EXPECT_EQ(z1.find_first_of("lo", 1), 2);
}

TEST(TestZString, FindLastOf) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.find_last_of('l'), 3);
    EXPECT_EQ(z1.find_last_of('x'), z_string_view::npos);
    EXPECT_EQ(z1.find_last_of('e', 1), 1);
    EXPECT_EQ(z1.find_last_of('l', 1), z_string_view::npos);
    EXPECT_EQ(z1.find_last_of("le"), 3);
    EXPECT_EQ(z1.find_last_of("xy"), z_string_view::npos);
    EXPECT_EQ(z1.find_last_of("lo", 1), z_string_view::npos);
}

TEST(TestZString, FindFirstNotOf) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.find_first_not_of('l'), 0);
    EXPECT_EQ(z1.find_first_not_of('H'), 1);
    EXPECT_EQ(z1.find_first_not_of('e', 1), 2);
    EXPECT_EQ(z1.find_first_not_of('l', 1), 1);
    EXPECT_EQ(z1.find_first_not_of("lo"), 0);
    EXPECT_EQ(z1.find_first_not_of("He"), 2);
    EXPECT_EQ(z1.find_first_not_of("loHe"), z_string_view::npos);
    EXPECT_EQ(z1.find_first_not_of("le", 1), 4);

    z_string_view z2 = "aaa";
    EXPECT_EQ(z2.find_first_not_of('a'), z_string_view::npos);
}

TEST(TestZString, FindLastNotOf) {
    z_string_view z1 = "Hello";

    EXPECT_EQ(z1.find_last_not_of('l'), 4);
    EXPECT_EQ(z1.find_last_not_of('o'), 3);
    EXPECT_EQ(z1.find_last_not_of('x'), 4);
    EXPECT_EQ(z1.find_last_not_of('e', 1), 0);
    EXPECT_EQ(z1.find_last_not_of('l', 1), 1);
    EXPECT_EQ(z1.find_last_not_of("ol"), 1);
    EXPECT_EQ(z1.find_last_not_of("oleH"), z_string_view::npos);
    EXPECT_EQ(z1.find_last_not_of("eH", 1), z_string_view::npos);

    z_string_view z2 = "aaa";
    EXPECT_EQ(z2.find_last_not_of('a'), z_string_view::npos);
}
