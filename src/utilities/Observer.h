//
// Created by duong on 15/09/2024.
//

#ifndef OBSERVER_H
#define OBSERVER_H
#include <any>
#include <string_view>
#include <string>


namespace Cal
{
    class Observer;
}

class Cal::Observer {
public:
    explicit Observer(std::string_view name);
    virtual ~Observer() = default;

    void notify(const std::any & data);

    const std::string & name() const { return observerName_; }

private:
    virtual void notifyImpl(const std::any &data) = 0;

    std::string observerName_;
};



#endif //OBSERVER_H
