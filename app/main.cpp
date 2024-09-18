#include "AppObservers.h"
#include "CommandFactory.h"
#include "Controller.h"
#include "ICommand.h"


#include <filesystem>
#include <fstream>
#include <iostream>

#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <ranges>
#include "MainWindow.h"

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


void setupUi(UserInterface& ui, Controller& ci)
{
    RegisterCoreCommands(ui);

    ui.attach(UserInterface::CommandEntered(), make_unique<CommandIssuedObserver>( ci ) );

    Stack::Instance().attach(Stack::StackChanged(), make_unique<StackUpdatedObserver>( ui ) );
}

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
