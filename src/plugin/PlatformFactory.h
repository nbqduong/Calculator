//
// Created by duong on 20/09/2024.
//

#ifndef PLATFORMFACTORY_H
#define PLATFORMFACTORY_H
#include <memory>

namespace Cal {

export class PlatformFactory
{
public:
  static PlatformFactory& Instance();
  virtual ~PlatformFactory();

  virtual std::unique_ptr<class DynamicLoader> createDynamicLoader() = 0;

protected:
  PlatformFactory();

private:
  PlatformFactory(const PlatformFactory&) = delete;
  PlatformFactory& operator=(const PlatformFactory&) = delete;
  PlatformFactory(PlatformFactory&&) = delete;
  PlatformFactory& operator=(PlatformFactory&&) = delete;
};

}
#endif //PLATFORMFACTORY_H
