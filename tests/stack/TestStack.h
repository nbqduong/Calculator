//
// Created by duong on 16/09/2024.
//

#ifndef TESTSTACK_H
#define TESTSTACK_H

#include "Stack.h"
#include <catch2/catch_test_macros.hpp>

using std::vector;
using std::vector;
using std::string;
using std::shared_ptr;
using std::unique_ptr;

class StackChangedObserver : public Cal::Observer
{
public:
    StackChangedObserver(string name);
    unsigned int changeCount() const { return changeCount_; }
    void notifyImpl(const std::any&);

private:
    unsigned int changeCount_;
};

StackChangedObserver::StackChangedObserver(string name)
: Cal::Observer{name}
, changeCount_{0}
{
}

void StackChangedObserver::notifyImpl(const std::any&)
{
    ++changeCount_;
}

class StackErrorObserver : public Cal::Observer
{
public:
    StackErrorObserver(string name);
    const vector<string>& errorMessages() const { return messages_; }
    const vector<Cal::StackErrorData::ErrorConditions>& errors() const { return errors_; }
    void notifyImpl(const std::any&);

private:
    vector<string> messages_;
    vector<Cal::StackErrorData::ErrorConditions> errors_;
};

StackErrorObserver::StackErrorObserver(string name)
: Cal::Observer{name}
{
}

void StackErrorObserver::notifyImpl(const std::any& data)
{
    auto p = std::any_cast<Cal::StackErrorData>(data);
    messages_.push_back(p.message());
    errors_.push_back(p.error());

    return;
}



#endif //TESTSTACK_H
