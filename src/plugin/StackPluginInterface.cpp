//
// Created by duong on 20/09/2024.
//

#include "StackPluginInterface.h"

#include "Stack.h"
#include <vector>


using std::vector;

extern "C" void StackPush(double d, bool suppressChangeEvent)
{
  Cal::Stack::Instance().push(d, suppressChangeEvent);

  return;
}

extern "C" double StackPop(bool suppressChangeEvent)
{
  return Cal::Stack::Instance().pop(suppressChangeEvent);
}

extern "C" size_t StackSize()
{
  return Cal::Stack::Instance().size();
}

extern "C" double StackFirstElement()
{
  vector<double> v = Cal::Stack::Instance().getElements(1);
  return v[0];
}

extern "C" double StackSecondElement()
{
  vector<double> v = Cal::Stack::Instance().getElements(2);
  return v[1];
}