//
// Created by duong on 18/09/2024.
//

#ifndef INPUTWIDGETIMPL_H
#define INPUTWIDGETIMPL_H
#include "CommandButton.h"
#include "InputWidget.h"

namespace Cal
{
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




#endif //INPUTWIDGETIMPL_H
