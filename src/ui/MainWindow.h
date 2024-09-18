//
// Created by duong on 18/09/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "Display.h"
#include "GuiModel.h"
#include "InputWidget.h"
#include "UserInterface.h"


#include "Stack.h"
#include <QMainWindow>
#include <string>
#include <string_view>


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


class MainWindow::MainWindowImpl : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindowImpl(MainWindow* parent);
    void showMessage(string_view m);
    void stackChanged();
    void setupFinalButtons();
    void addCommandButton(const string& dispPrimaryCmd, const string& primaryCmd, const string& dispShftCmd, const string& shftCmd);

    public slots:
        void onCommandEntered(std::string cmd);
    void onShowMessage(std::string m);

    private slots:


private:
    void connectInputToModel();
    void doLayout();

    MainWindow& parent_;
    int nLinesStack_;
    Display* display_;
    InputWidget* inputWidget_;
    GuiModel* guiModel_;
};

}


#endif //MAINWINDOW_H
