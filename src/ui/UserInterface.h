//
// Created by duong on 18/09/2024.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Publisher.h"


#include <iostream>
#include <memory>
#include <string>
#include <string_view>

using std::unique_ptr;
using std::string;
using std::string_view;
using std::istream;
using std::ostream;

namespace Cal
{
export class UserInterface : protected Publisher
{
public:
    UserInterface() { registerEvent( CommandEntered() ); }
    virtual ~UserInterface() = default;

    // post a message to the user
    virtual void postMessage(string_view m) = 0;

    // notifies the interface that the stack has changed
    virtual void stackChanged() = 0;

    using Publisher::attach;
    using Publisher::detach;

    // defines the event this publisher can raise
    // note that the string is defined in main.cpp of the application since
    // class UserInterface has no implementation file (in test driver for same
    // reason)

    // static function instead of member to avoid manual Windows dllexport requirements
    static string CommandEntered(){ return "CommandIssued";};
};
}

#endif //USERINTERFACE_H
