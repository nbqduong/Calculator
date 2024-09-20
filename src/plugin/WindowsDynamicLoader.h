//
// Created by duong on 20/09/2024.
//

#ifndef WINDOWSDYNAMICLOADER_H
#define WINDOWSDYNAMICLOADER_H
#include "DynamicLoader.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>

using std::string;
using std::vector;

namespace Cal {

export class WindowsDynamicLoader : public DynamicLoader
{
public:
  WindowsDynamicLoader();
  ~WindowsDynamicLoader();

  Plugin* allocatePlugin(const string& pluginName) override;
  void deallocatePlugin(Plugin* p) override;

private:
  HINSTANCE handle_;
};

WindowsDynamicLoader::WindowsDynamicLoader()
: DynamicLoader{}
, handle_{nullptr}
{

}

WindowsDynamicLoader::~WindowsDynamicLoader()
{
  if(handle_) FreeLibrary(handle_);
}

Plugin* WindowsDynamicLoader::allocatePlugin(const string& pluginName)
{
  handle_ = LoadLibrary(pluginName.c_str());

  if(!handle_) return nullptr;
  else
  {
    auto alloc = GetProcAddress(handle_, GetPluginAllocationName().c_str());
    if( PluginAllocator allocator{ reinterpret_cast<PluginAllocator>(alloc) } )
    {
      auto p = static_cast<Plugin*>((*allocator)());
      return p;
    }
    else return nullptr;
  }
}

void WindowsDynamicLoader::deallocatePlugin(Plugin* p)
{
  if(!handle_)
    throw Exception("Trying to deallocate a plugin, but shared library is not open.");
  else
  {
    auto dealloc = GetProcAddress(handle_, GetPluginDeallocationName().c_str());
    if( auto deallocator = reinterpret_cast<PluginDeallocator>(dealloc) )
    {
      (*deallocator)(p);
    }
    else throw Exception("Could not load the deallocator function in the plugin");
  }

  return;
}

}
#endif //WINDOWSDYNAMICLOADER_H
