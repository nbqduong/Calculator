//
// Created by duong on 20/09/2024.
//

#include "PluginLoader.h"

#include "PlatformFactory.h"

namespace Cal {

void PluginLoader::loadPlugins(UserInterface& ui, const string& pluginFileName)
{

  if( ifstream ifs{ pluginFileName.c_str() } )
  {
    std::vector<std::string> lines{std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>()};
    for (const auto& n : lines) {
      load(ui, n);
    }

  }
  else
  {
    ui.postMessage("Could not open plugin file");
  }

  return;
}

const vector<const Plugin*> PluginLoader::getPlugins() const
{
  vector<const Plugin*> v;
  for(auto& i : plugins_)
    v.push_back( i.get() );

  return v;
}

void PluginLoader::load(UserInterface& ui, const string& name)
{
  loaders_.emplace_back( PlatformFactory::Instance().createDynamicLoader() );

  // may be null
  if( auto p = loaders_.back()->allocatePlugin(name) )
    plugins_.emplace_back( p, PluginDeleter( *loaders_.back() ) );
  else
    ui.postMessage( string("Error opening plugin: " + name) );

  return;
}

}