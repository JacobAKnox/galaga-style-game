#pragma once

#include "event_type.h"

class Listener {
 public:
  virtual void on_event(EventType type) = 0;
  virtual ~Listener() = default;
};
