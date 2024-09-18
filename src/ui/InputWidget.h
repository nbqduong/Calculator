//
// Created by duong on 18/09/2024.
//


#ifndef INPUT_WIDGET_H
#define INPUT_WIDGET_H

#include "CommandButton.h"


#include <QWidget>
#include <memory>
#include <string>

class QGridLayout;
using std::string;

namespace Cal {


class InputWidget : public QWidget
{
    class InputWidgetImpl;
    Q_OBJECT
public:
    explicit InputWidget(QWidget *parent = nullptr);
    ~InputWidget() = default;

    void addCommandButton(const std::string& dispPrimaryCmd, const std::string& primaryCmd,
    const std::string& dispShftCmd, const std::string& shftCmd);

    void setupFinalButtons();

    signals:
        void characterEntered(char c);
        void enterPressed();
        void backspacePressed();
        void plusMinusPressed();
        void commandEntered(std::string, std::string);
        void shiftPressed();
        void procedurePressed();

private:
    std::unique_ptr<InputWidgetImpl> pimpl_;
};

class InputWidget::InputWidgetImpl : public QWidget
{
    Q_OBJECT
public:
    InputWidgetImpl(InputWidget* parent);
    void addCommandButton(const string& dispPrimaryCmd, const string& primaryCmd, const string& dispShftCmd, const string& shftCmd);
    void setupFinalButtons();
    QGridLayout* getLayout() { return layout_; }

    private slots:
        void onEex();
    void onDecimal();
    void onPlusMinus();
    void onZero();
    void onOne();
    void onTwo();
    void onThree();
    void onFour();
    void onFive();
    void onSix();
    void onSeven();
    void onEight();
    void onNine();

private:
    void allocateButtons();
    void setupShortcuts();
    void makeConnections();
    void layoutButtons();

    InputWidget* parent_;
    int nAddedButtons_;
    QGridLayout* layout_;

    CommandButton* eexButton_;
    CommandButton* decimalButton_;
    CommandButton* plusMinusButton_;
    CommandButton* enterButton_;
    CommandButton* backspaceButton_;
    CommandButton* zeroButton_;
    CommandButton* oneButton_;
    CommandButton* twoButton_;
    CommandButton* threeButton_;
    CommandButton* fourButton_;
    CommandButton* fiveButton_;
    CommandButton* sixButton_;
    CommandButton* sevenButton_;
    CommandButton* eightButton_;
    CommandButton* nineButton_;
    CommandButton* plusButton_;
    CommandButton* minusButton_;
    CommandButton* multiplyButton_;
    CommandButton* divideButton_;
    CommandButton* sinButton_;
    CommandButton* cosButton_;
    CommandButton* tanButton_;
    CommandButton* powButton_;
    CommandButton* shiftButton_;
};

}



#endif //INPUTWIDGET_H
