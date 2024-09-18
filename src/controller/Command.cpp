//
// Created by duong on 17/09/2024.
//

#include "Command.h"

#include "../stack/Stack.h"
#include "Exception.h"

using std::string_view;

namespace Cal
{
void Command::execute()
{
    checkPreconditionsImpl();
    executeImpl();
    return;
}

void Command::undo()
{
    undoImpl();
    return;
}

Command* Command::clone() const
{
    return cloneImpl();
}

const char* Command::helpMessage() const
{
    return helpMessageImpl();
}

void Command::deallocate()
{
    delete this;
}

void Command::checkPreconditionsImpl() const
{
    return;
}

BinaryCommand::BinaryCommand(const BinaryCommand& rhs)
: Command(rhs)
, top_{rhs.top_}
, next_{rhs.next_}
{ }

void BinaryCommand::checkPreconditionsImpl() const
{
    if(Stack::Instance().size() < 2)
        throw Exception("Binary command requires at least two arguments.");
}

void BinaryCommand::executeImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = Stack::Instance().pop(true);
    next_ = Stack::Instance().pop(true);
    Stack::Instance().push( binaryOperation(next_, top_) );

    return;
}

void BinaryCommand::undoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().pop(true);
    Stack::Instance().push(next_, true);
    Stack::Instance().push(top_);

    return;
}

UnaryCommand::UnaryCommand(const UnaryCommand& rhs)
: Command(rhs)
, top_(rhs.top_)
{
}

void UnaryCommand::checkPreconditionsImpl() const
{
    if( Stack::Instance().size() < 1 )
        throw Exception{"Stack must have at least one element"};
}

void UnaryCommand::executeImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = Stack::Instance().pop(true);
    Stack::Instance().push( unaryOperation(top_) );

    return;
}

void UnaryCommand::undoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().pop(true);
    Stack::Instance().push(top_);

    return;
}

}