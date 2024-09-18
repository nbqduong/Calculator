//
// Created by duong on 18/09/2024.
//

#ifndef DISPLAY_H
#define DISPLAY_H


#include <QWidget>
#include <vector>
#include <QValidator>
#include <string>
#include <string_view>

namespace Cal {

class GuiModel;

// This class is the calculator's display. It shows a number of lines of the stack
// as determined by the constructor and shows the input as it is entered

class Display : public QWidget
{
    class DisplayImpl;
    Q_OBJECT
public:
    // nLinesStack is the number of vertical lines of the stack to be displayed
    // minCharWide is the minimum number of characters wide for the display (defaults to min size)
    explicit Display(const GuiModel& g, QWidget* parent = nullptr, int nLinesStack = 6, int minCharWide = 25);

    // this is for testing purposes to be able to get the current display
    std::string getText() const;

    // show message in the status bar
    void showMessage(std::string_view m);

    public slots:
        // call this slot when the underlying model changes
        void onModelChanged();

private:
    DisplayImpl* pimpl_;

};

}


#endif //DISPLAY_H
