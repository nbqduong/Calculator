//
// Created by duong on 18/09/2024.
//

#include "Display.h"
#include "GuiModel.h"
#include "LookAndFeel.h"
#include <QColor>
#include <QLabel>
#include <QPalette>
#include <QResizeEvent>
#include <QStatusBar>
#include <QVBoxLayout>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>

using std::string;
using std::vector;
using std::string;
using std::string_view;

namespace Cal {

class Display::DisplayImpl : public QWidget
{
public:
    explicit DisplayImpl(const GuiModel&, int nLinesStack, int nCharWide, QVBoxLayout* layout, Display* parent);
    string getText() const;
    void showMessage(string_view m);
    void onModelChanged();

private:
    void setupSize();
    void resizeEvent(QResizeEvent*) override;
    string createLine(int lineNumber, double value, int stackSize);

    const GuiModel& guiModel_;
    QLabel* label_;
    int nLinesStack_;
    int nCharWide_;
    QStatusBar* statusBar_;
    unsigned int statusBarTimeout;
    QLabel* shiftIndicator_;
};

Display::DisplayImpl::DisplayImpl(const GuiModel& g, int nLinesStack, int nCharWide, QVBoxLayout* layout, Display* parent)
: QWidget{parent}
, guiModel_{g}
, nLinesStack_{nLinesStack}
, nCharWide_{nCharWide}
, statusBarTimeout{3000}
{
    statusBar_ = new QStatusBar{this};
    statusBar_->setFont( LookAndFeel::Instance().getStatusBarFont() );
    statusBar_->setSizeGripEnabled(false);
    statusBar_->setPalette( LookAndFeel::Instance().getStatusBarPalette() );
    shiftIndicator_ = new QLabel{"Shift", this};
    statusBar_->addPermanentWidget(shiftIndicator_);
    shiftIndicator_->hide();

    label_ = new QLabel{this};

    auto t = std::string( "QLabel {{ background-color : " +LookAndFeel::Instance().getDisplayBackgroundColor()+
                          "; border : "+LookAndFeel::Instance().getDisplayBorderStyle()+
                          "; border-radius : "+LookAndFeel::Instance().getDisplayBorderRadius()+
                          ";}}");

    label_->setStyleSheet( t.c_str() );

    layout->addWidget(statusBar_);
    layout->addWidget(label_);

    label_->setFont( LookAndFeel::Instance().getDisplayFont() );

    setupSize();

    onModelChanged();
}

string Display::DisplayImpl::getText() const
{
    return label_->text().toStdString();
}

void Display::DisplayImpl::showMessage(string_view m)
{
    statusBar_->showMessage( QString::fromStdString(string{m}), statusBarTimeout);
    return;
}

void Display::DisplayImpl::setupSize()
{
    QFontMetrics fm{LookAndFeel::Instance().getDisplayFont()};
    label_->setFixedHeight( nLinesStack_ * fm.height() + 2);
    label_->setMinimumWidth( (nCharWide_ + 2) * fm.maxWidth() );

    return;
}

void Display::DisplayImpl::resizeEvent(QResizeEvent* event)
{
    QFontMetrics fm{LookAndFeel::Instance().getDisplayFont()};
    int w{ event->size().width() };
    nCharWide_ = w / fm.maxWidth() - 2;

    onModelChanged();

    return;
}

string Display::DisplayImpl::createLine(int lineNumber, double sv, int stackSize)
{
    assert(stackSize < 10); // if not, then the line padding will be wrong

    std::ostringstream oss;
    oss << std::setprecision(12) << sv;
    string value = lineNumber < stackSize ? oss.str() : "";

    std::ostringstream oss1;
    oss1 << (lineNumber + 1) << ":"
        << std::setw(nCharWide_ - 2) << std::right << value;

    return oss1.str();
}

void Display::DisplayImpl::onModelChanged()
{
    const GuiModel::State& state = guiModel_.getState();
    if(state.shiftState == GuiModel::ShiftState::Shifted)
    {
        shiftIndicator_->show();
    }
    else shiftIndicator_->hide();

    string display;
    auto bi = std::back_inserter(display);

    auto hasInput = state.curInput.size() != 0;
    auto start =  nLinesStack_ - ( hasInput ? 1 : 0 );

    for (auto i = start - 1; i >= 0; --i)
    {
        bool valueExists = i < static_cast<int>( state.curStack.size() );
        fmt::format_to(bi, "{}{}", createLine( i, (valueExists ? state.curStack[i] : 0 /*dummy value*/), state.curStack.size() ),
            (i != 0 ? "\n" : "") );
    }

    if(hasInput) fmt::format_to(bi, "\n{}", state.curInput);

    label_->setText( QString::fromStdString( display ) );
}

Display::Display(const GuiModel& g, QWidget *parent, int nLinesStack, int nCharWide)
: QWidget{parent}
{
    auto layout = new QVBoxLayout{this};
    pimpl_ = new DisplayImpl{g, nLinesStack, nCharWide, layout, this};
    layout->setContentsMargins( LookAndFeel::Instance().getContentsMargins() );
    layout->addWidget(pimpl_);
}

std::string Display::getText() const
{
    return pimpl_->getText();
}

void Display::showMessage(std::string_view m)
{
    pimpl_->showMessage(m);

    return;
}

void Display::onModelChanged()
{
    pimpl_->onModelChanged();
}


}
