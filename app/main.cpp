#include "AppObservers.h"
#include "CommandFactory.h"
#include "Controller.h"
#include "ICommand.h"


#include <filesystem>
#include <fstream>
#include <iostream>

#include "MainWindow.h"
#include "Plugin.h"
#include "PluginLoader.h"
#include <QApplication>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fmt/core.h>
using namespace Cal;

using std::set;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::ostream;
using std::istream;

void registerCommand(UserInterface& ui, const string& label, CommandPtr c)
{
    try
    {
        CommandFactory::Instance().registerCommand(label, std::move(c));
    }
    catch(Exception& e)
    {
        ui.postMessage( e.what() );
    }

    return;
}

set<string> setupPlugins(UserInterface& ui, PluginLoader& loader)
{
    // for now, I don't want to allow the plugin file to be a command
    // line option, so I simply code the name of the searched plugin file
    auto pluginFile = "plugins.pdp";
    loader.loadPlugins(ui, pluginFile);
    auto plugins = loader.getPlugins();

    set<string> injectedCommands;
    for(auto p : plugins)
    {
        if(auto apiVersion = p->apiVersion(); apiVersion.major != 1 || apiVersion.minor != 0)
        {
            ui.postMessage("Plugin API version is incompatible. Need v. 1.0.");
            continue;
        }

        auto descriptor = p->getPluginDescriptor();
        for (size_t i = 0; i < descriptor.nCommands; ++i)
        {
            registerCommand(ui, descriptor.commandNames[i], MakeCommandPtr(descriptor.commands[i]->clone()) );
            injectedCommands.insert(descriptor.commandNames[i]);
        }

        // if gui, setup buttons
        if( auto gui = dynamic_cast<MainWindow*>(&ui) )
        {
            auto allCommands = CommandFactory::Instance().getAllCommandNames();
            if(auto buttonDescriptor = p->getPluginButtonDescriptor() )
            {
                for (size_t i = 0; i < buttonDescriptor->nButtons; ++i)
                {
                    if (auto b = *buttonDescriptor; allCommands.find(b.primaryCmd[i]) == allCommands.end())
                    {
                        auto t = fmt::format("{} {}", "Error adding button", b.dispPrimaryCmd[i]);
                        ui.postMessage(t);
                    }
                    else if (allCommands.find(b.shftCmd[i]) == allCommands.end())
                    {
                        auto t = fmt::format("{} {}", "Error adding button ", b.dispShftCmd[i]);
                        ui.postMessage(t);
                    }
                    else
                    {
                        gui->addCommandButton(b.dispPrimaryCmd[i], b.primaryCmd[i], b.dispShftCmd[i], b.shftCmd[i]);
                    }
                }
            }
        }
    }

    return injectedCommands;
}

void setupUi(UserInterface& ui, Controller& ci)
{
    RegisterCoreCommands(ui);

    ui.attach(UserInterface::CommandEntered(), make_unique<CommandIssuedObserver>( ci ) );

    Stack::Instance().attach(Stack::StackChanged(), make_unique<StackUpdatedObserver>( ui ) );
}

void runGui(int argc, char* argv[])
try
{
    QApplication app{argc, argv};

    MainWindow gui{argc, argv};


    Controller ci{gui};

    setupUi(gui, ci);

    gui.execute();

    app.exec();


    return;
}
catch(Exception& e)
{
    cerr << "GUI terminated with exception:\n"
         << e.what() << endl;
}




int main(int argc, char **argv)
{
    runGui(argc, argv);

    return 0;
}
