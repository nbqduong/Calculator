//
// Created by duong on 18/09/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "UserInterface.h"


#include <QMainWindow>
#include <string>
#include <string_view>
#include "Stack.h"

namespace Cal {

class CommandButton;

class MainWindow : public QMainWindow, public UserInterface
{
    class MainWindowImpl;
public:
    MainWindow(int argc, char* argv[], QWidget* parent = nullptr);

    void postMessage(std::string_view m) override;
    void stackChanged() override;

    void execute();

    // Add a command button, for example, from a plugin
    // Buttons are added in order from left to right just below the
    // line undo, redo, proc from the bottom up
    // Buttons are reparented to MainWindow
    void addCommandButton(const std::string& dispPrimaryCmd, const std::string& primaryCmd,
        const std::string& dispShftCmd, const std::string& shftCmd);

private:

    MainWindowImpl* pimpl_;
};

}


#endif //MAINWINDOW_H
