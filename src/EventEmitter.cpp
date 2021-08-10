#include <EventEmiter.hpp>

void EventEmiter::add_eventlistener(EventType type, event_callback callback)
{
  listeners.push_back({ type, callback });
}

void EventEmiter::emit_event(Event event)
{
  for (std::vector<EventListener>::iterator it = listeners.begin(); it != listeners.end(); it++) {
    EventListener listener = *it;

    if (listener.type == event.type) {
      listener.callback(event);
    }
  }
}
