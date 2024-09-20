//
// Created by duong on 20/09/2024.
//

#include "PlatformFactory.h"

#include <memory>


#ifdef POSIX
#include "PosixFactory.h"
#else
#include "WindowFactory.h"
#endif


namespace Cal {

PlatformFactory::PlatformFactory()
{
}

PlatformFactory& PlatformFactory::Instance()
{
#ifdef POSIX
  static PosixFactory instance;
#else
  static WindowsFactory instance;
#endif

  return instance;
}

PlatformFactory::~PlatformFactory()
{
}

}