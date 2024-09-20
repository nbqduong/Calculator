//
// Created by duong on 20/09/2024.
//

#ifndef DYNAMICLOADER_H
#define DYNAMICLOADER_H
#include <string>

using std::string;

namespace Cal {

class DynamicLoader
{
public:
  virtual ~DynamicLoader() = default;

  // derived class must provide an OS specific way of loading a shared library,
  // dynamically binding to the AllocPlugin function in the plugin, allocating the
  // plugin, and closing the plugin
  virtual class Plugin* allocatePlugin(const string& pluginName) = 0;
  virtual void deallocatePlugin(class Plugin*) = 0;

  // Get the plugin allocation name for derived classes
  static string GetPluginAllocationName() { return "AllocPlugin"; }
  static string GetPluginDeallocationName() { return "DeallocPlugin"; }
};

}

// function pointer for the interface to allocate a plugin
export extern "C" { typedef void* (*PluginAllocator)(void); }

// function pointer for the interface to deallocate a plugin
export extern "C" { typedef void (*PluginDeallocator)(void*); }
#endif //DYNAMICLOADER_H
