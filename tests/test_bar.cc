#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "bar.h"

TEST_CASE("sum1")
{
    std::cout <<"adsfasf";
    REQUIRE(summing(0, 1) == 1);
    REQUIRE(summing(1, 0) == 1);
}

TEST_CASE("branch1")
{
    CHECK(fn_branch(true, false) == 0);
    REQUIRE(fn_branch(true, true) == 0);
    REQUIRE(fn_branch(false, true) == 0);
    REQUIRE(fn_branch(false, false) == 1);
}
