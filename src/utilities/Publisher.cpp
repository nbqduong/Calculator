//
// Created by duong on 15/09/2024.
//

#include "Publisher.h"

#include "Exception.h"

namespace Cal
{

Publisher::Events::const_iterator Publisher::findCheckedEvent(const string& eventName) const
{
    auto ev = events_.find(eventName);
    if( ev == events_.end() )
    {
        throw Exception{ std::string("Publisher does not support event ") + eventName };
    }

    return ev;
}

Publisher::Events::iterator Publisher::findCheckedEvent(const string &eventName)
{
    auto ev = events_.find(eventName);
    if( ev == events_.end() )
    {
        throw Exception{ std::string("Publisher does not support event ") + eventName };
    }

    return ev;
}

void Publisher::attach(const string& eventName, unique_ptr<Observer> observer)
{
    auto& obsList = findCheckedEvent(eventName)->second;

    if( auto itr =  obsList.find(observer->name()); itr != obsList.end() )
        throw Exception("Observer already attached to publisher");

    obsList.insert( std::pair(observer->name(), std::move(observer)) );

    return;
}

unique_ptr<Observer> Publisher::detach(const string& eventName, const string& observer)
{
    auto& obsList = findCheckedEvent(eventName)->second;

    auto obs = obsList.find(observer);
    if( obs == obsList.end() )
        throw Exception("Cannot detach observer because observer not found");

    auto tmp = std::move(obs->second);
    obsList.erase(obs);

    return tmp;
}


void Publisher::raise(const string& eventName) const
{
    raise(eventName, any{});
}

void Publisher::raise(const string& eventName, const std::any d) const
{
    const auto& obsList = (findCheckedEvent(eventName)->second);

    for(const auto &it : obsList)
        it.second->notify(d);

    return;
}

void Publisher::registerEvent(const string& eventName)
{
    if( auto itr =  events_.find(eventName); itr != events_.end() )
        throw Exception{"Event already registered"};

    events_[eventName] = ObserversList{};

    return;
}

void Publisher::registerEvents(const vector<string>& eventNames)
{
    for(const auto &it : eventNames)
        registerEvent(it);

    return;
}

set<string> Publisher::listEvents() const
{
    set<string> tmp;
    for (const auto &it : events_)
        tmp.insert(it.first);

    return tmp;
}

set<string> Publisher::listEventObservers(const string& eventName) const
{
    const auto& ev = findCheckedEvent(eventName)->second;

    set<string> tmp;

    for (const auto &it : ev)
        tmp.insert(it.first);


    return tmp;
}
}
