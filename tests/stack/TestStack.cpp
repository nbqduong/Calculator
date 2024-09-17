//
// Created by duong on 16/09/2024.
//

#include "TestStack.h"

#include "Exception.h"

using Catch::Matchers::WithinRel;

TEST_CASE("Stack push top", "[stack]")
{

    Cal::Stack& stack = Cal::Stack::Instance();
    stack.clear();
    StackChangedObserver* raw = new StackChangedObserver{"StackChangedObserver"};
    stack.attach( Cal::Stack::StackChanged(), unique_ptr<Cal::Observer>{raw} );

    REQUIRE( stack.size() == 0 );

    vector<double> cur{ stack.getElements(100) };

    REQUIRE( cur.size() == 0 );

    stack.push(3.14159);
    stack.push(17.3);

    REQUIRE( stack.size() == 2 );

    stack.push(2.0);

    cur = stack.getElements(2);

    REQUIRE_THAT( cur[0], WithinRel(2.0, 0.001) );
    REQUIRE_THAT( cur[1], WithinRel(17.3, 0.001) );
    
    cur = stack.getElements(3);
    
    REQUIRE_THAT( cur[0], WithinRel(2.0, 0.001) );
    REQUIRE_THAT( cur[1], WithinRel(17.3 , 0.001));
    REQUIRE_THAT( cur[2], WithinRel(3.14159 , 0.001));
    
    double val = stack.pop();
    REQUIRE_THAT(val, WithinRel(2.0, 0.001));
    REQUIRE( stack.size() == 2 );
    
    cur = stack.getElements(2);
    REQUIRE_THAT( cur[0], WithinRel(17.3 , 0.001));
    REQUIRE_THAT( cur[1], WithinRel(3.14159 , 0.001));
    
    stack.push(3.0);
    
    cur = stack.getElements(3);
    
    REQUIRE_THAT( cur[0], WithinRel(3.0 , 0.001));
    REQUIRE_THAT( cur[1], WithinRel(17.3 , 0.001));
    REQUIRE_THAT( cur[2], WithinRel(3.14159 , 0.001));
    
    REQUIRE_THAT(raw->changeCount(), WithinRel(5u, 0.001));
    
    stack.push(5.0, true);
    stack.pop(true);
    
    REQUIRE_THAT(raw->changeCount(), WithinRel(5u, 0.001));

    stack.clear();
    stack.detach(Cal::Stack::StackChanged(), "StackChangedObserver");

}


TEST_CASE("Stack error message", "[stack]")
{
    Cal::Stack& stack = Cal::Stack::Instance();
    stack.clear();
    StackErrorObserver* raw = new StackErrorObserver{"StackErrorObserver"};
    stack.attach( Cal::Stack::StackError(), unique_ptr<Cal::Observer>{raw} );

    const string emptyMsg = Cal::StackErrorData::Message(Cal::StackErrorData::ErrorConditions::Empty);
    const string swapMsg = Cal::StackErrorData::Message(Cal::StackErrorData::ErrorConditions::TooFewArguments);

    try
    {
        stack.pop();
        REQUIRE(false);
    }
    catch(Cal::Exception& e)
    {
        REQUIRE(e.what() == emptyMsg);
    }

    try
    {
        stack.swapTop();
        REQUIRE(false);
    }
    catch(Cal::Exception& e)
    {
        REQUIRE(e.what() == swapMsg);
    }

    const vector<string>& msgs { raw->errorMessages() };
    REQUIRE(msgs.size() == 2);
    REQUIRE(msgs[0]==emptyMsg);
    REQUIRE(msgs[1]== swapMsg);

    const vector<Cal::StackErrorData::ErrorConditions> errors { raw->errors() };
    REQUIRE(errors.size() == 2);
    REQUIRE(errors[0]== Cal::StackErrorData::ErrorConditions::Empty);
    REQUIRE(errors[1]== Cal::StackErrorData::ErrorConditions::TooFewArguments);

    stack.clear();
    stack.detach(Cal::Stack::StackError(), "StackErrorObserver");
}