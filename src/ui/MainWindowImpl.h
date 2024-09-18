//
// Created by duong on 18/09/2024.
//

#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
#include "MainWindow.h"


namespace Cal{
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


#endif //MAINWINDOWIMPL_H
