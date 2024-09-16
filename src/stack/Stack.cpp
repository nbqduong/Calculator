//
// Created by duong on 15/09/2024.
//

#include "Stack.h"

#include "Exception.h"

#include <deque>
namespace Cal
 {
//Stack error data implement
const char* StackErrorData::Message(StackErrorData::ErrorConditions ec)
{
    switch(ec)
    {
    case ErrorConditions::Empty: return "Attempting to pop empty stack";
    case ErrorConditions::TooFewArguments: return "Need at least two stack elements to swap top";
    default: return "Unknown error";
    };
}

const char* StackErrorData::message() const
{
    return Message(err_);
}

string Stack::StackChanged()
{
    return "stackChanged";
}

string Stack::StackError()
{
    return "error";
}


//Implementation of stack
 class Stack::StackImpl
 {
 public:
     explicit StackImpl(const Stack&);
     void push(double d, bool suppressChangeEvent);
     double pop(bool suppressChangeEvent);
     void swapTop();
     vector<double> getElements(size_t n) const;
     void getElements(size_t n, vector<double>& v) const;
     size_t size() const { return stack_.size(); }
     void clear();
     double top() const;

 private:
     const Stack& parent_; // for raising events
     std::deque<double> stack_;
 };

Stack::StackImpl::StackImpl(const Stack& s)
: parent_(s)
{

}

void Stack::StackImpl::push(double d, bool suppressChangeEvent)
{
    stack_.push_back(d);
    if(!suppressChangeEvent) parent_.raise(Stack::StackChanged(), nullptr);

    return;
}

double Stack::StackImpl::pop(bool suppressChangeEvent)
{
    if( stack_.empty() )
    {
        parent_.raise(Stack::StackError(),
            std::make_shared<StackErrorData>(StackErrorData::ErrorConditions::Empty));

        throw Exception{StackErrorData::Message(StackErrorData::ErrorConditions::Empty)};
    }
    else
    {
        auto val = stack_.back();
        stack_.pop_back();
        if(!suppressChangeEvent) parent_.raise(Stack::StackChanged(), nullptr);
        return val;
    }
}

void Stack::StackImpl::swapTop()
{
    if( stack_.size() < 2 )
    {
        parent_.raise(Stack::StackError(),
            std::make_shared<StackErrorData>(StackErrorData::ErrorConditions::TooFewArguments));

        throw Exception{StackErrorData::Message(StackErrorData::ErrorConditions::TooFewArguments)};
    }
    else
    {
        auto first = stack_.back();
        stack_.pop_back();
        auto second = stack_.back();
        stack_.pop_back();
        stack_.push_back(first);
        stack_.push_back(second);

        parent_.raise(Stack::StackChanged(), nullptr);
    }

    return;
}

vector<double> Stack::StackImpl::getElements(size_t n) const
{
    vector<double> v;
    getElements(n, v);
    return v;
}

void Stack::StackImpl::getElements(size_t n, vector<double>& v) const
{
    // if n is > stack's size, just return size of stack
    if(n > stack_.size()) n = stack_.size();

    v.insert(v.end(), stack_.rbegin(), stack_.rbegin() + n);

    return;
}

void Stack::StackImpl::clear()
{
    stack_.clear();

    parent_.raise(Stack::StackChanged(), nullptr);

    return;
}

double Stack::StackImpl::top() const
{
    return stack_.back();
}

//Stack features

Stack& Stack::Instance()
{
    static Stack instance;
    return instance;
}

void Stack::push(double d, bool suppressChangeEvent)
{
    pimpl_->push(d, suppressChangeEvent);
    return;
}

double Stack::pop(bool suppressChangeEvent)
{
    return pimpl_->pop(suppressChangeEvent);
}

void Stack::swapTop()
{
    pimpl_->swapTop();
    return;
}

vector<double> Stack::getElements(size_t n) const
{
    return pimpl_->getElements(n);
}

void Stack::getElements(size_t n, vector<double>& v) const
{
    pimpl_->getElements(n, v);
    return;
}

size_t Stack::size() const
{
    return pimpl_->size();
}

void Stack::clear() const
{
    pimpl_->clear();
    return;
}

Stack::Stack()
{
    pimpl_ = std::make_unique<StackImpl>(*this);
    registerEvent(StackChanged());
    registerEvent(StackError());
}

Stack::~Stack()
{
}

 }