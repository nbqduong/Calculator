//
// Created by duong on 18/09/2024.
//


#ifndef INPUT_WIDGET_H
#define INPUT_WIDGET_H



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
}



#endif //INPUTWIDGET_H
