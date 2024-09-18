//
// Created by duong on 18/09/2024.
//

#include "CommandButton.h"
#include "LookAndFeel.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
#include <QShortcut>
#include <QToolTip>

using std::cout;
using std::endl;

using std::string;

namespace Cal
{
CommandButton::CommandButton(const string& dispPrimaryCmd, const string& primaryCmd,
const string& dispShftCmd, const string& shftCmd, QWidget* parent)
: QWidget{parent}
, primaryCmd_{primaryCmd}
, shftCmd_{shftCmd}
{
    setup(dispPrimaryCmd, dispShftCmd);
}

CommandButton::CommandButton(const string& dispPrimaryCmd, const string& primaryCmd, QWidget* parent)
: QWidget{parent}
, primaryCmd_{primaryCmd}
, shftCmd_{""}
{
    setup(dispPrimaryCmd, "");
}

void CommandButton::registerShortcut(const QKeySequence& sequence)
{
    // Use the shortcut mechanism rather than btn_->setShortcut() to allow
    // multiple different shortcuts for one button (e.g., plus/minus button)
    // shortcuts with both p and m. btn_->setShortcut() releases the current
    // shortcut when the next one is set.

    auto sc = new QShortcut(sequence, btn_);
    connect(sc, SIGNAL(activated()), this, SLOT(onClicked()));
}

void CommandButton::registerToolTip(const string& s)
{
    btn_->setToolTip( QString::fromStdString(s) );
    return;
}

void CommandButton::setButtonTextColor(const string& color)
{
    auto t = string("QPushButton {{ color : "+color+"; }}");
    btn_->setStyleSheet( t.c_str() );

    return;
}

void CommandButton::onClicked()
{
    emit clicked(primaryCmd_, shftCmd_);
}

void CommandButton::setup(const string& dispPrimaryCmd, const string& dispShftCmd)
{
    btn_ = new QPushButton{ QString::fromStdString(dispPrimaryCmd), this};
    btn_->setFont( LookAndFeel::Instance().getButtonFont() );
    btn_->setFixedSize( LookAndFeel::Instance().getMinimumButtonSize() );

    auto label = new QLabel{ QString::fromStdString(dispShftCmd), this };
    label->setFont( LookAndFeel::Instance().getShiftLabelFont() );
    label->setMinimumSize( ( dispShftCmd.empty() ? QSize(0, 0) : LookAndFeel::Instance().getMinimumShiftLabelSize()) );

    auto t = std::string( "QLabel {{ color : "+LookAndFeel::Instance().getShiftColor()+"; }}" );
    label->setStyleSheet( t.c_str() );

    connect(btn_, SIGNAL(clicked()), this, SLOT(onClicked()));

    auto layout = new QVBoxLayout{this};
    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(btn_);
    layout->setContentsMargins( LookAndFeel::Instance().getContentsMargins() );
}
}