#include <string.h>
#include "../Include/Printf.h"
#include "catch.hpp"
#include "limits.h"

TEST_CASE("normalInput", "[printf]")
{
    char buffer[13] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};

    const char* g_inputstring1 = "ABCD";
    char*       g_result1      = Printf(buffer, buffer + 12, g_inputstring1);
    const char* g_expectation1 = "ABCD";

    SECTION("static-string that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result1 == buffer + 4);
        REQUIRE(*g_result1 == '\0');
        REQUIRE(strcmp(buffer, g_expectation1) == 0);
    }

    const char* g_inputstring2 = "%u";
    char*       g_result2      = Printf(buffer, buffer + 12, g_inputstring2, 123);
    const char* g_expectation2 = "123";

    SECTION("dynamic unsingned int that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result2 == buffer + 3);
        REQUIRE(*g_result2 == '\0');
        REQUIRE(strcmp(buffer, g_expectation2) == 0);
    }

    const char* g_inputstring3 = "%c";
    char*       g_result3      = Printf(buffer, buffer + 12, g_inputstring3, 'g');
    const char* g_expectation3 = "g";

    SECTION("dynamic int that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result3 == buffer + 1);
        REQUIRE(*g_result3 == '\0');
        REQUIRE(strcmp(buffer, g_expectation3) == 0);
    }

    const char* g_inputstring4 = "%s";
    char*       g_result4      = Printf(buffer, buffer + 12, g_inputstring4, "A1B2CD");
    const char* g_expectation4 = "A1B2CD";

    SECTION("dynamic string that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result4 == buffer + 6);
        REQUIRE(*g_result4 == '\0');
        REQUIRE(strcmp(buffer, g_expectation4) == 0);
    }

    const char* g_inputstring41 = "%x";
    char*       g_result41      = Printf(buffer, buffer + 12, g_inputstring41, 123);
    const char* g_expectation41 = "0x7b";

    SECTION("dynamic hex that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result41 == buffer + 4);
        REQUIRE(*g_result41 == '\0');
        REQUIRE(strcmp(buffer, g_expectation41) == 0);
    }

    const char* g_inputstring5 = "%b";
    char*       g_result5      = Printf(buffer, buffer + 12, g_inputstring5, 123);
    const char* g_expectation5 = "0b1111011";

    SECTION("dynamic binary that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result5 == buffer + 9);
        REQUIRE(*g_result5 == '\0');
        REQUIRE(strcmp(buffer, g_expectation5) == 0);
    }

    const char* g_inputstring6 = "%%";
    char*       g_result6      = Printf(buffer, buffer + 12, g_inputstring6, 123);
    const char* g_expectation6 = "%";

    SECTION("dynamic % that is smaller than buffer-size is saved")
    {
        REQUIRE(g_result6 == buffer + 1);
        REQUIRE(*g_result6 == '\0');
        REQUIRE(strcmp(buffer, g_expectation6) == 0);
    }
}

TEST_CASE("Incorrect syntax is detected")
{
    SECTION("Format errors are detected")
    {
        char  tmp_test[128] = {'\0'};
        char* returnvalue;

        returnvalue = Printf(tmp_test, tmp_test + 127, "%s%", "Test");
        REQUIRE(returnvalue == nullptr);

        returnvalue = Printf(tmp_test, tmp_test + 127, "%r");
        REQUIRE(returnvalue == nullptr);
    }

    SECTION("Nullpointer will be seen")
    {
        char  test[128] = {'\0'};
        char* returnvalue;

        returnvalue = Printf(test, nullptr, "%s", "Test");
        REQUIRE(returnvalue == nullptr);

        returnvalue = Printf(test, test + 127, nullptr, "Test");
        REQUIRE(returnvalue == nullptr);

        returnvalue = Printf(nullptr, test + 127, "%s", "Test");
        REQUIRE(returnvalue == nullptr);

        returnvalue = Printf(test, test + 127, "%s", nullptr);
        REQUIRE(returnvalue == nullptr);
    }
}

TEST_CASE("More Input than Buffer", "[printf]")
{
    char        buffer[13]  = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};
    const char* inputstring = "ABCDEFGHIJKLMNOPQRSTUVW";
    char*       result      = Printf(buffer, buffer + 12, inputstring);
    const char* expectation = "ABCDEFGHIJKL";

    SECTION("Pointer is correct") { REQUIRE(result == buffer + 12); }
    SECTION("Null-Termination in the End") { REQUIRE(*result == '\0'); }
    SECTION("Content is correct") { REQUIRE(strcmp(buffer, expectation) == 0); }
}

TEST_CASE("Wrong Input Params")
{
    char  buffer[13] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};
    char* b_result1  = Printf(buffer, buffer - 1, "ABC");
    char* b_result2  = Printf(buffer, buffer, "ABC");
    char* b_result3  = Printf(nullptr, buffer, "ABC");
    char* b_result4  = Printf(buffer, nullptr, "ABC");
    char* b_result5  = Printf(nullptr, nullptr, "ABC");

    SECTION("return nullptr for bad input params")
    {
        REQUIRE(b_result1 == nullptr);
        REQUIRE(b_result2 == nullptr);
        REQUIRE(b_result3 == nullptr);
        REQUIRE(b_result4 == nullptr);
        REQUIRE(b_result5 == nullptr);
    }
}

TEST_CASE("Parameter edge cases")
{
    SECTION("d")
    {
        char  test[128] = {'\0'};
        char* ret;

        ret = Printf(test, test + 127, "%d", INT_MIN);
        REQUIRE(!strcmp(test, "-2147483648"));
        REQUIRE(ret == test + 11);

        ret = Printf(test, test + 127, "%d", INT_MAX);
        REQUIRE(!strcmp(test, "2147483647"));
        REQUIRE(ret == test + 10);
    }

    SECTION("u")
    {
        char  test[128] = {'\0'};
        char* ret;

        ret = Printf(test, test + 127, "%u", UINT_MAX);
        REQUIRE(!strcmp(test, "4294967295"));
        REQUIRE(ret == test + 10);

        ret = Printf(test, test + 127, "%u", -1);
        REQUIRE(!strcmp(test, "4294967295"));
        REQUIRE(ret == test + 10);
    }

    SECTION("x")
    {
        char  test[128] = {'\0'};
        char* ret;

        ret = Printf(test, test + 127, "%x", INT_MIN);
        REQUIRE(!strcmp(test, "0x80000000"));
        REQUIRE(ret == test + 10);

        ret = Printf(test, test + 127, "%x", -1);
        REQUIRE(!strcmp(test, "0xffffffff"));
        REQUIRE(ret == test + 10);

        ret = Printf(test, test + 127, "%x", 0);
        REQUIRE(!strcmp(test, "0x0"));
        REQUIRE(ret == test + 3);

        ret = Printf(test, test + 127, "%x", 15);
        REQUIRE(!strcmp(test, "0xf"));
        REQUIRE(ret == test + 3);

        ret = Printf(test, test + 127, "%x", INT_MAX);
        REQUIRE(!strcmp(test, "0x7fffffff"));
        REQUIRE(ret == test + 10);
    }

    SECTION("b")
    {
        char  test[128] = {'\0'};
        char* ret;

        ret = Printf(test, test + 127, "%b", INT_MIN);
        REQUIRE(!strcmp(test, "0b10000000000000000000000000000000"));
        REQUIRE(ret == test + 34);

        ret = Printf(test, test + 127, "%b", -1);
        REQUIRE(!strcmp(test, "0b11111111111111111111111111111111"));
        REQUIRE(ret == test + 34);

        ret = Printf(test, test + 127, "%b", 0);
        REQUIRE(!strcmp(test, "0b0"));
        REQUIRE(ret == test + 3);

        ret = Printf(test, test + 127, "%b", 10);
        REQUIRE(!strcmp(test, "0b1010"));
        REQUIRE(ret == test + 6);

        ret = Printf(test, test + 127, "%b", INT_MAX);
        REQUIRE(!strcmp(test, "0b1111111111111111111111111111111"));
        REQUIRE(ret == test + 33);
    }
}