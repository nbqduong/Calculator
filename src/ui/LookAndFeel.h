//
// Created by duong on 18/09/2024.
//

#ifndef LOOKANDFEEL_H
#define LOOKANDFEEL_H



#include <memory>
#include <string>

class QFont;
class QSize;
class QPalette;
class QMargins;

namespace Cal {

// This is a singleton class that defines the metrics to be used by all
// of the display. An example of such a metric would be a font family or
// button size.

class LookAndFeel
{
    class LookAndFeelImpl;
public:
    static const LookAndFeel& Instance();

    // get the font that should be used by the display
    const QFont& getDisplayFont() const;

    // get the font that should be used by the buttons
    const QFont& getButtonFont() const;

    // get the font that should be used by the shift labels for the buttons
    const QFont& getShiftLabelFont() const;

    // get the minimum size of the buttons
    const QSize& getMinimumButtonSize() const;

    // get the minimum size of the shift label
    const QSize& getMinimumShiftLabelSize() const;

    // get the font that should be used for the status bar
    const QFont& getStatusBarFont() const;

    // get the palette for the status bar to enable color change of status bar text
    const QPalette& getStatusBarPalette() const;

    // get contents margins for layouts affecting button spacing
    const QMargins& getContentsMargins() const;

    // get the color of the shift label
    const std::string& getShiftColor() const;

    // get display background color
    std::string getDisplayBackgroundColor() const;

    // get display border style
    std::string getDisplayBorderStyle() const;

    // get display border radius
    std::string getDisplayBorderRadius() const;

private:
    LookAndFeel();
    ~LookAndFeel() = default;
    LookAndFeel(const LookAndFeel&) = delete;
    LookAndFeel& operator=(const LookAndFeel&) = delete;
    LookAndFeel(LookAndFeel&&) = delete;
    LookAndFeel& operator=(LookAndFeel&&) = delete;

    std::unique_ptr<LookAndFeelImpl> pimpl_;
};

}



#endif //LOOKANDFEEL_H
