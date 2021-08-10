#ifndef PLOT_EVENT_EMITER_H
#define PLOT_EVENT_EMITER_H
#include <Event.hpp>
#include <vector>
class EventEmiter {
  public:
    void add_eventlistener(EventType type, event_callback callback);
    void emit_event(Event event);

  private:
    std::vector<EventListener> listeners;
};
#endif
