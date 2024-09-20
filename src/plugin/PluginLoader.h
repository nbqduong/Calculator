//
// Created by duong on 20/09/2024.
//

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "DynamicLoader.h"
#include "UserInterface.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;
using std::unique_ptr;


namespace Cal {
export class PluginDeleter
{
public:
  explicit PluginDeleter(DynamicLoader& d) : loader_{d} {}
  void operator()(Plugin* p) { loader_.deallocatePlugin(p); }

private:
  DynamicLoader& loader_;
};

export class PluginLoader
{
public:
  PluginLoader() = default;
  ~PluginLoader() = default;

  void loadPlugins(UserInterface& ui, const string& pluginFileName);
  const vector<const Plugin*> getPlugins() const;

private:
  PluginLoader(const PluginLoader&) = delete;
  PluginLoader(PluginLoader&&) = delete;
  PluginLoader& operator=(const PluginLoader&) = delete;
  PluginLoader& operator=(PluginLoader&&) = delete;

  void load(UserInterface& ui, const string&);

  vector<unique_ptr<DynamicLoader>> loaders_;
  vector<unique_ptr<Plugin, PluginDeleter>> plugins_;
};
}

#endif //PLUGINLOADER_H
