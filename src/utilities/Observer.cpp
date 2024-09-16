//
// Created by duong on 15/09/2024.
//

#include "Observer.h"

namespace Cal{

Observer::Observer(std::string_view name)
: observerName_{name}
{ }

void Observer::notify(const std::any & data)
{
    notifyImpl(data);
    return;
}

}