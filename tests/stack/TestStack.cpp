//
// Created by duong on 16/09/2024.
//

#include "TestStack.h"

TEST_CASE("Stack push top", "[stack]")
{
    // REQUIRE(factorial(0) == 1);
    // REQUIRE(factorial(1) == 1);
    // REQUIRE(factorial(2) == 2);
    // REQUIRE(factorial(3) == 6);
    // REQUIRE(factorial(10) == 3628800);

    Cal::Stack& stack = Cal::Stack::Instance();
    stack.clear();
    StackChangedObserver* raw = new StackChangedObserver{"StackChangedObserver"};
    stack.attach( Cal::Stack::StackChanged(), unique_ptr<Cal::Observer>{raw} );

    REQUIRE( stack.size() == 0 );

}