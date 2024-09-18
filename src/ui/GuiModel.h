//
// Created by duong on 18/09/2024.
//

#ifndef GUIMODEL_H
#define GUIMODEL_H

#include <QObject>
#include <memory>
#include <vector>
#include <string>
#include <QDoubleValidator>

namespace Cal {

class GuiModel : public QObject
{
  class GuiModelImpl;
  Q_OBJECT
public:
  enum class ShiftState { Unshifted, Shifted };

  struct State
  {
    State();

    std::vector<double> curStack;
    std::string curInput;
    ShiftState shiftState;
    QValidator::State curInputValidity;
  };

  explicit GuiModel(QObject* parent = nullptr);
  ~GuiModel();

  void stackChanged(const std::vector<double>& v);

  const State& getState() const;

  // exposed externally for testing only
  bool inputEmpty() const;
  void clearInput();

  public slots:
      // called to toggle the calculator's shift state
      void onShift();

      // call this slot when a new character of input is available
      void onCharacterEntered(char c);

      // call this slot when enter is pressed. Does nothing if input is invalid else enters number on stack
      // and clears input
      void onEnter();

      // call this slot to backspace during input entry
      void onBackspace();

      // call this slot when plus/minus is entered
      void onPlusMinus();

      // called when commands are entered
      void onCommandEntered(std::string primaryCmd, std::string secondaryCmd);

  signals:
      void modelChanged();
      void commandEntered(std::string s);
      void errorDetected(std::string s);

private:
  std::unique_ptr<GuiModelImpl> pimpl_;
};

}


#endif //GUIMODEL_H
