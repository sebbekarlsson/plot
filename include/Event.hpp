#ifndef PLOT_EVENT_H
#define PLOT_EVENT_H
#include <functional>


typedef enum {
  MOUSE_WHEEL
} EventType;

typedef struct {
  void* data;
  float x;
  float y;
  float z;
  float dx;
  float dy;
  float dz;

  EventType type;

} Event;

typedef std::function<void(Event event)> event_callback;

typedef struct {
  EventType type;
  event_callback callback;
} EventListener;

#endif
