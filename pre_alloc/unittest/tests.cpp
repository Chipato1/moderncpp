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