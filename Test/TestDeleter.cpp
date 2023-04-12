#include <gtest/gtest.h>
#include <Rad/Deleter.h>
#include <Rad/Win32/Deleter.h>

// https://stackoverflow.com/questions/13905661/how-to-get-list-of-gdi-handles
// https://github.com/sam-b/windows_kernel_address_leaks/blob/master/GdiSharedHandleTable/GdiSharedHandleTable/GdiSharedHandleTable.cpp

// TODO How to test that std::fclose is actually been called?
TEST(TestDeleter, FileDeleter) {
    const char* filename = "test.txt";
    const char msg[] = "Hello World\n";
    {
        FilePtr fp;
        EXPECT_EQ(fopen_s(&fp, filename, "w"), 0);
        EXPECT_EQ(std::fwrite(msg, sizeof(char), std::size(msg), -fp), std::size(msg));
        EXPECT_EQ(std::ferror(-fp), 0);
    }
    char buf[100];
    {
        FilePtr fp;
        EXPECT_EQ(fopen_s(&fp, filename, "r"), 0);
        size_t sz = std::fread(buf, sizeof(char), std::size(buf), -fp);
        EXPECT_EQ(std::ferror(-fp), 0);
        buf[sz] = '\0';
    }
    EXPECT_EQ(remove(filename), 0);
    EXPECT_EQ(strcmp(msg, buf), 0);
}

class TestWin32Deleter : public testing::Test
{
protected:
    void SetUp() override
    {
        for (DWORD i = GR_GDIOBJECTS; i <= GR_USEROBJECTS; ++i)
            m_Objects[i] = GetGuiResources(i);
    }

    void TearDown() override
    {
        for (DWORD i = GR_GDIOBJECTS; i <= GR_USEROBJECTS; ++i)
            EXPECT_EQ(m_Objects[i], GetGuiResources(i));
    }

    DWORD GetGuiResources(DWORD uFlags)
    {
        return ::GetGuiResources(m_hProcess, uFlags);
    }

    DWORD GetOrigGuiResources(DWORD uFlags)
    {
        return m_Objects[uFlags];
    }

private:
    HANDLE m_hProcess = GetCurrentProcess();
    DWORD m_Objects[2] = {};
};

TEST_F(TestWin32Deleter, UniqueHMENU) {
    UniqueHMENU menu(CreateMenu());
    EXPECT_NE(-menu, HMENU(NULL));
    EXPECT_EQ(GetOrigGuiResources(GR_USEROBJECTS) + 1, GetGuiResources(GR_USEROBJECTS));
}

TEST_F(TestWin32Deleter, MakeGetDC) {
    auto DC = MakeGetDC(NULL);
    EXPECT_EQ(GetOrigGuiResources(GR_GDIOBJECTS) + 1, GetGuiResources(GR_GDIOBJECTS));
}

// TOOD DeleteObject an a HBRUSH doesn't decrement GetGuiResources
TEST_F(TestWin32Deleter, DISABLED_UniqueHBRUSH) {
    UniqueHBRUSH brush(CreateSolidBrush(RGB(255, 0, 0)));
    EXPECT_NE(-brush, HBRUSH(NULL));
    EXPECT_EQ(GetOrigGuiResources(GR_GDIOBJECTS) + 1, GetGuiResources(GR_GDIOBJECTS));
}

TEST_F(TestWin32Deleter, UniqueHPEN) {
    UniqueHPEN pen(CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
    EXPECT_NE(-pen, HPEN(NULL));
    EXPECT_EQ(GetOrigGuiResources(GR_GDIOBJECTS) + 1, GetGuiResources(GR_GDIOBJECTS));
}

TEST_F(TestWin32Deleter, UniqueHBITMAP) {
    auto DC = MakeGetDC(NULL);
    UniqueHBITMAP bmp(CreateCompatibleBitmap(-DC, 0, 0));
    EXPECT_NE(-bmp, HBITMAP(NULL));
    // TODO CreateCompatibleBitmap doesn't increment GetGuiResources
    //EXPECT_EQ(GetOrigGuiResources(GR_GDIOBJECTS) + 2, GetGuiResources(GR_GDIOBJECTS));
}
