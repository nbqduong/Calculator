//
// Created by duong on 20/09/2024.
//

#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "PlatformFactory.h"
#include "WindowsDynamicLoader.h"

#include <memory>


namespace Cal {
export class WindowsFactory : public Cal::PlatformFactory
{
public:
  WindowsFactory() = default;

  std::unique_ptr<class DynamicLoader> createDynamicLoader() override;
};

std::unique_ptr<DynamicLoader> WindowsFactory::createDynamicLoader()
{
  return std::make_unique<WindowsDynamicLoader>();
}

}



#endif //WINDOWFACTORY_H
