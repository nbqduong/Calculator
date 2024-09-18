//
// Created by duong on 18/09/2024.
//

#ifndef APPOBSERVERS_H
#define APPOBSERVERS_H

#include "Controller.h"
#include "Exception.h"
#include "Observer.h"
#include "UserInterface.h"


#include <any>
#include <string>
using std::string;
using std::any;

namespace Cal {

class CommandIssuedObserver : public Observer
{
public:
    explicit CommandIssuedObserver(Controller& ci);

private:
    void notifyImpl(const any&) override;

    Controller& ci_;
};

class StackUpdatedObserver : public Observer
{
public:
    explicit StackUpdatedObserver(UserInterface& ui);

private:
    void notifyImpl(const any&) override;

    UserInterface& ui_;
};

CommandIssuedObserver::CommandIssuedObserver(Controller& ci)
: Observer{"CommandIssued"}
, ci_{ci}
{ }

void CommandIssuedObserver::notifyImpl(const any& data)
{
    try
    {
        const auto& d = std::any_cast<string>(data);
        ci_.commandEntered(d);
    }
    catch(const std::bad_any_cast&)
    {
        throw Exception("Could not convert CommandIssued data to a string");
    }

    return;
}

StackUpdatedObserver::StackUpdatedObserver(UserInterface& ui)
: Observer{"StackUpdated"}
, ui_{ui}
{ }

void StackUpdatedObserver::notifyImpl(const any&)
{
    ui_.stackChanged();

    return;
}

}


#endif //APPOBSERVERS_H
