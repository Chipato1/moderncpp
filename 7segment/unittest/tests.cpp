#include "catch.hpp"
#include "../Include/7Segment.h"
#include <string.h>

TEST_CASE("Test different Combinations", "[operator]")
{
    SECTION("Multiple Numbers")
    {
        MultiDigit md1{4, 2, 0};
        REQUIRE(strcmp("     -   - \n| |   | | |\n -   -     \n  | |   | |\n     -   - ", static_cast<const char*>(md1)) == 0);
    }
	SECTION("Single Numbers")
	{ 
		MultiDigit md0{0};
		MultiDigit md1{1};
        MultiDigit md2{2};
        MultiDigit md3{3};
        MultiDigit md4{4};
        MultiDigit md5{5};
        MultiDigit md6{6};
        MultiDigit md7{7};
        MultiDigit md8{8};
        MultiDigit md9{9};

        REQUIRE(strcmp(" - \n| |\n   \n| |\n - ", static_cast<const char*>(md0)) == 0);
        REQUIRE(strcmp("   \n  |\n   \n  |\n   ", static_cast<const char*>(md1)) == 0);
        REQUIRE(strcmp(" - \n  |\n - \n|  \n - ", static_cast<const char*>(md2)) == 0);
        REQUIRE(strcmp(" - \n  |\n - \n  |\n - ", static_cast<const char*>(md3)) == 0);
        REQUIRE(strcmp("   \n| |\n - \n  |\n   ", static_cast<const char*>(md4)) == 0);
        REQUIRE(strcmp(" - \n|  \n - \n  |\n - ", static_cast<const char*>(md5)) == 0);
        REQUIRE(strcmp(" - \n|  \n - \n| |\n - ", static_cast<const char*>(md6)) == 0);
        REQUIRE(strcmp(" - \n  |\n   \n  |\n   ", static_cast<const char*>(md7)) == 0);
        REQUIRE(strcmp(" - \n| |\n - \n| |\n - ", static_cast<const char*>(md8)) == 0);
        REQUIRE(strcmp(" - \n| |\n - \n  |\n - ", static_cast<const char*>(md9)) == 0);
	}
    SECTION("Test no digit")
    {
        MultiDigit md1{};
        REQUIRE(strcmp("", static_cast<const char*>(md1)) == 0);
    }
}
