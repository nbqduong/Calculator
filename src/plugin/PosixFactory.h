//
// Created by duong on 20/09/2024.
//

#ifndef POSIXFACTORY_H
#define POSIXFACTORY_H
#include "PlatformFactory.h"
#include "PosixDynamicLoader.h"

#include <memory>

namespace Cal {
class PosixFactory : public Cal::PlatformFactory {
public:
  PosixFactory() = default;

  std::unique_ptr<class DynamicLoader> createDynamicLoader() override;
};

std::unique_ptr<DynamicLoader> PosixFactory::createDynamicLoader()
{
  return std::make_unique<PosixDynamicLoader>();
}

}
#endif //POSIXFACTORY_H
