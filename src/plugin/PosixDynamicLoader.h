//
// Created by duong on 20/09/2024.
//

#ifndef POSIXDYNAMICLOADER_H
#define POSIXDYNAMICLOADER_H
#include "DynamicLoader.h"
#include "Exception.h"

#include <dlfcn.h>
#include <iostream>



using std::cout;
using std::endl;

namespace Cal {

export class PosixDynamicLoader : public DynamicLoader
{
public:
  PosixDynamicLoader();
  ~PosixDynamicLoader();

  Plugin* allocatePlugin(const std::string& pluginName) override;
  void deallocatePlugin(Plugin* p) override;

private:
  void* handle_;
};

PosixDynamicLoader::PosixDynamicLoader()
: DynamicLoader{}
, handle_{nullptr}
{
}

PosixDynamicLoader::~PosixDynamicLoader()
{
  if(handle_) dlclose(handle_);
}

Plugin* PosixDynamicLoader::allocatePlugin(const std::string& pluginName)
{
  handle_ = dlopen(pluginName.c_str(), RTLD_LAZY);

  if(!handle_) return nullptr;
  else
  {
    auto alloc = dlsym(handle_, GetPluginAllocationName().c_str());
    if( PluginAllocator allocator{ reinterpret_cast<PluginAllocator>(alloc) } )
    {
      auto p = static_cast<Plugin*>((*allocator)());
      return p;
    }
    else return nullptr;
  }

  return nullptr;
}

void PosixDynamicLoader::deallocatePlugin(Plugin* p)
{
  if(!handle_)
    throw Exception("Trying to deallocate a plugin, but shared library is not open.");
  else
  {
    auto dealloc = dlsym(handle_, GetPluginDeallocationName().c_str());
    if( auto deallocator = reinterpret_cast<PluginDeallocator>(dealloc) )
    {
      (*deallocator)(p);
    }
    else throw Exception("Could not load the deallocator function in the plugin");
  }

  return;
}

}
#endif //POSIXDYNAMICLOADER_H
