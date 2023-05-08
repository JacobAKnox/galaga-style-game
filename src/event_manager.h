#pragma once

#include <unordered_map>
#include <vector>

#include "event_type.h"
#include "listener.h"

class EventManager {
 public:
  static EventManager& get_instance() {
    static EventManager instance{};
    return instance;
  }

  template <class... EventTypes>
  void add_listener(Listener* listener, EventTypes... type) {
    for (auto& t : {type...}) {
      all_listeners[t].push_back(listener);
    }
  }

  void notify(EventType type) {
    for (auto& listener : all_listeners[type]) {
      listener->on_event(type);
    }
  }

  void remove_listener(Listener* listener) {
    for (auto& [type, listeners] : all_listeners) {
      listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }
  }

 private:
  EventManager() = default;

  std::unordered_map<EventType, std::vector<Listener*>> all_listeners{};
};
