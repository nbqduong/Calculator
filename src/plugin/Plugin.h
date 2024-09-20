//
// Created by duong on 20/09/2024.
//

#ifndef PLUGIN_H
#define PLUGIN_H
#include "Command.h"

namespace Cal {

// Plugins are responsible for deleting the memory in the descriptors
class Plugin
{
public:
  Plugin() = default;
  virtual ~Plugin() = default;

  struct PluginDescriptor
  {
    int nCommands;
    char** commandNames;
    Command** commands;
  };

  virtual const PluginDescriptor& getPluginDescriptor() const = 0;

  struct PluginButtonDescriptor
  {
    int nButtons;
    char** dispPrimaryCmd;
    char** primaryCmd;
    char** dispShftCmd;
    char** shftCmd;
  };

  // pointer instead of reference so that nullptr can be returned if buttons are not provided
  virtual const PluginButtonDescriptor* getPluginButtonDescriptor() const = 0;

  struct ApiVersion
  {
    int major;
    int minor;
  };

  virtual ApiVersion apiVersion() const = 0;

private:
  Plugin(const Plugin&) = delete;
  Plugin& operator=(const Plugin&) = delete;
  Plugin(Plugin&&) = delete;
  Plugin& operator=(Plugin&&) = delete;
};

}
#endif //PLUGIN_H
