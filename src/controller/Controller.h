//
// Created by duong on 17/09/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H



#include <string>
#include <memory>
#include <set>

namespace Cal {

class UserInterface;

class Controller
{
    class ControllerImpl;

public:
    explicit Controller(UserInterface& ui);
    ~Controller();

    void commandEntered(const std::string& command);

private:
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;


    std::unique_ptr<ControllerImpl> pimpl_;
};

}



#endif //CONTROLLER_H
