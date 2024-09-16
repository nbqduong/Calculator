//
// Created by duong on 15/09/2024.
//

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Observer.h"


#include <algorithm>
#include <any>
#include <memory>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;
using std::set;
using std::unique_ptr;
using std::shared_ptr;
using std::any;
using std::unordered_map;


namespace Cal
{
class Publisher;
}


class Cal::Publisher {
  using ObserversList = unordered_map<string, unique_ptr<Observer>>;
  using Events = unordered_map<string, ObserversList>;

public:
   Publisher() = default;

   void attach(const string& eventName, unique_ptr<Observer> observer);
   unique_ptr<Observer> detach(const string& eventName, const string& observerName);

   set<string> listEvents() const;
   set<string> listEventObservers(const string& eventName) const;

protected:
   void raise(const string& eventName) const;
   void raise(const string& eventName, any data) const;

   void registerEvent(const string& eventName);
   void registerEvents(const vector<string>& eventNames);

private:
  Events::const_iterator findCheckedEvent(const string& eventName) const;
  Events::iterator findCheckedEvent(const string& eventName);

  Events events_;

};



#endif //PUBLISHER_H
