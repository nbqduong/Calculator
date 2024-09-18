//
// Created by duong on 17/09/2024.
//

#include "Controller.h"

#include "Command.h"
#include "CommandFactory.h"
#include "CommandManager.h"
#include "Exception.h"
#include "ICommand.h"
#include "UserInterface.h"
#include <regex>

using std::set;
using std::unique_ptr;
using std::set;
using std::string_view;

namespace Cal {

class Controller::ControllerImpl
{
public:
    explicit ControllerImpl(UserInterface& ui);

    void executeCommand(const string& command);


private:
    bool isNum(const string&, double& d);
    void handleCommand(CommandPtr command);
    void printHelp() const;

    CommandManager manager_;
    UserInterface& ui_;
};

Controller::ControllerImpl::ControllerImpl(UserInterface& ui)
: ui_(ui)
{ }

void Controller::ControllerImpl::executeCommand(const string& command)
{
    string_view sv{command};

    // entry of a number simply goes onto the the stack
    if(double d; isNum(command, d) )
        manager_.executeCommand(MakeCommandPtr<EnterNumber>(d));
    else if(command == "undo")
        manager_.undo();
    else if(command == "redo")
        manager_.redo();
    else if(command == "help")
        printHelp();
    else
    {
        if( auto c = CommandFactory::Instance().allocateCommand(command) )
        {
            handleCommand( std::move(c) );
        }
        else
        {
            auto t = std::string("Command "+command+" is not a known command");
            ui_.postMessage(t);
        }
    }

    return;
}

void Controller::ControllerImpl::handleCommand(CommandPtr c)
{
    try
    {
        manager_.executeCommand( std::move(c) );
    }
    catch(Exception& e)
    {
        // ui_.postMessage( e.what() );
    }

    return;
}

void Controller::ControllerImpl::printHelp() const
{
    string help = "\n"
                  "undo: undo last operation\n"
                  "redo: redo last operation\n";

    set<string> allCommands = CommandFactory::Instance().getAllCommandNames();
    for(auto i : allCommands)
    {
        help += CommandFactory::Instance().helpMessage(i) + "\n";
    }

    ui_.postMessage( help );

    return;
}

// uses a C++11 regular expression to check if this is a valid double number
// if so, converts it into one and returns it
bool Controller::ControllerImpl::isNum(const string& s, double& d)
{
     if(s == "+" || s == "-") return false;

     std::regex dpRegex("((\\+|-)?[[:digit:]]*)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
     bool isNumber{ std::regex_match(s, dpRegex) };

     if(isNumber)
     {
         d = std::stod(s);
     }

     return isNumber;
}

void Controller::commandEntered(const string& command)
{
    pimpl_->executeCommand(command);

    return;
}

Controller::Controller(UserInterface& ui)
: pimpl_{ std::make_unique<ControllerImpl>(ui) }
{

}

Controller::~Controller()
{ }

}