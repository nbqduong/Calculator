//
// Created by duong on 17/09/2024.
//

#include "CommandFactory.h"
#include "Command.h"
#include "Exception.h"
#include "ICommand.h"
#include "UserInterface.h"
namespace Cal
{

set<string> CommandFactory::getAllCommandNames() const
{
    set<string> tmp;

    for(const auto& itr : factory_)
    {
        tmp.insert(itr.first);
    }

    return tmp;
}

string CommandFactory::helpMessage(const string& command) const
{
    auto it = factory_.find(command);

    return command + string (it != factory_.end() ? it->second->helpMessage() : "no help entry found");
}

void CommandFactory::registerCommand(const string& name, CommandPtr c)
{
    if( hasKey(name) )
    {
        auto t = string("Command " + name + " already registered");
        throw Exception{t};
    }
    else
        factory_.emplace( name, std::move(c) );

    return;
}

CommandPtr CommandFactory::deregisterCommand(const string& name)
{
    if( hasKey(name) )
    {
        auto i = factory_.find(name);
        auto tmp = MakeCommandPtr( i->second.release() );
        factory_.erase(i);
        return tmp;
    }
    else return MakeCommandPtr(nullptr);
}

CommandPtr CommandFactory::allocateCommand(const string &name) const
{
    if( hasKey(name) )
    {
        const auto& command = factory_.find(name)->second;
        return MakeCommandPtr( command->clone() );
    }
    else return MakeCommandPtr(nullptr);
}


CommandFactory& CommandFactory::Instance()
{
    static CommandFactory instance;
    return instance;
}

void RegisterCoreCommands(UserInterface& ui)
{
    auto& cr = CommandFactory::Instance();
    try
    {
        cr.registerCommand( "swap", MakeCommandPtr<SwapTopOfStack>() );
        cr.registerCommand( "drop", MakeCommandPtr<DropTopOfStack>() );
        cr.registerCommand( "clear", MakeCommandPtr<ClearStack>() );
        cr.registerCommand( "+", MakeCommandPtr<Add>() );
        cr.registerCommand( "-", MakeCommandPtr<Subtract>() );
        // cr.registerCommand("*",
        //     MakeCommandPtr<BinaryCommandAlternative>("Replace first two elements on the stack with their product",
        //     [](double d, double f){ return d * f; })
        // );
        cr.registerCommand( "/", MakeCommandPtr<Divide>() );
        cr.registerCommand( "pow", MakeCommandPtr<Power>() );
        cr.registerCommand( "root", MakeCommandPtr<Root>() );
        cr.registerCommand( "sin", MakeCommandPtr<Sine>() );
        cr.registerCommand( "cos", MakeCommandPtr<Cosine>() );
        cr.registerCommand( "tan", MakeCommandPtr<Tangent>() );
        cr.registerCommand( "arcsin", MakeCommandPtr<Arcsine>() );
        cr.registerCommand( "arccos", MakeCommandPtr<Arccosine>() );
        cr.registerCommand( "arctan", MakeCommandPtr<Arctangent>() );
        cr.registerCommand( "neg", MakeCommandPtr<Negate>() );
        cr.registerCommand( "dup", MakeCommandPtr<Duplicate>() );
    }
    catch(Exception& e)
    {
        ui.postMessage( e.what() );
    }

    return;
}

 }