//
// Created by duong on 20/09/2024.
//

#ifndef STACKPLUGININTERFACE_H
#define STACKPLUGININTERFACE_H
#include <cstddef>

export extern "C" void StackPush(double d, bool suppressChangeEvent);
export extern "C" double StackPop(bool suppressChangeEvent);
export extern "C" size_t StackSize();
export extern "C" double StackFirstElement();
export extern "C" double StackSecondElement();

#endif //STACKPLUGININTERFACE_H
