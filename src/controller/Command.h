//
// Created by duong on 17/09/2024.
//

#ifndef COMMAND_H
#define COMMAND_H



#include <string>
#include <string_view>
#include <memory>
#include <functional>
#include <concepts>

using std::string_view;
using std::string;
using std::unique_ptr;

export namespace Cal
{
class Command
{
public:
    virtual ~Command() = default;

    // executes the command
    void execute();

    // undoes the command
    void undo();

    // create a polymorphic copy of the command
    Command* clone() const;

    // supplies a short help message for the command
    const char* helpMessage() const;

    // Deletes commands. This should only be overridden in plugins. By default,
    // simply deletes command. In plugins, delete must happen in the plugin.
    virtual void deallocate();

protected:
    Command() = default;
    Command(const Command&) = default;

private:
    // this function is not pure virtual because a command that needs no preconditions
    // shouldn't be forced to check for any...thus, this defaults to not throwing
    virtual void checkPreconditionsImpl() const;

    virtual void executeImpl() noexcept = 0;
    virtual void undoImpl() noexcept = 0;
    virtual Command* cloneImpl() const = 0;

    // all commands should have a short help
    virtual const char* helpMessageImpl() const noexcept = 0;

    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;
};

// Base class for binary operations: take two elements from stack and return
// one result. For any binary operation x and stack with top and next,
// the binary operation is applied as next x top
// Precondition: Binary operations must have at least two elements
// on the stack
// The reason to have a binary operations class is because undo,
// redo, and preconditions can be implemented identically
class BinaryCommand : public Command
{
public:
    virtual ~BinaryCommand() = default;

protected:
    // throws an exception if the stack size is less than two
    void checkPreconditionsImpl() const override;

    BinaryCommand() = default;
    BinaryCommand(const BinaryCommand&);

private:
    BinaryCommand(BinaryCommand&&) = delete;
    BinaryCommand& operator=(const BinaryCommand&) = delete;
    BinaryCommand& operator=(BinaryCommand&&) = delete;

    // takes two elements from the stack, applies the binary operation
    // and returns the result to the stack
    void executeImpl() noexcept final override;

    // drops the result and returns the original two numbers to the stack
    void undoImpl() noexcept final override;

    virtual double binaryOperation(double next, double top) const noexcept = 0;

    double top_;
    double next_;
};

// Base class for unary operations: take one element from the stack and return
// one result.
// Precondition: Unary operations must have at least one element on the stack.
// The reason to have a unary operations class is to avoid repetition for
// all classes implementing a unary interface.
class UnaryCommand : public Command
{
public:
    virtual ~UnaryCommand() = default;

protected:
    // throws an exception if the stack size is less than one
    void checkPreconditionsImpl() const override;

    UnaryCommand() = default;
    UnaryCommand(const UnaryCommand&);

private:
    UnaryCommand(UnaryCommand&&) = delete;
    UnaryCommand& operator=(const UnaryCommand&) = delete;
    UnaryCommand& operator=(UnaryCommand&&) = delete;

    // takes one element from the stack, applies the binary operation
    // and returns the result to teh stack
    void executeImpl() noexcept final override;

    // drops the result and returns the original number to the stack
    void undoImpl() noexcept final override;

    virtual double unaryOperation(double top) const noexcept = 0;

    double top_;
};

inline void CommandDeleter(Command* p)
{
    if(p) p->deallocate();
    return;
}

class PluginCommand : public Command
{
public:
    virtual ~PluginCommand() = default;

private:
    virtual const char* checkPluginPreconditions() const noexcept = 0;
    virtual PluginCommand* clonePluginImpl() const noexcept = 0;

    void checkPreconditionsImpl() const override final;
    PluginCommand* cloneImpl() const override final;
};




using CommandPtr = unique_ptr<Command, decltype(&CommandDeleter)>;

inline auto MakeCommandPtr(Command* p)
{
    return CommandPtr{p, &CommandDeleter};
}


template<typename T, typename... Args>
auto MakeCommandPtr(Args&&... args)
{
    static_assert(std::is_base_of<Command, T>::value, "T must be derived from Command");
    return CommandPtr{new T{std::forward<Args>(args)...}, &CommandDeleter};
}



}
#endif //COMMAND_H
