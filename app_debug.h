#ifndef APP_DEBUG_h
#define APP_DEBUG_h

#define DEBUG

#ifdef DEBUG
#define ECHO(m) Serial.print(m)
#define ECHOLN(m) Serial.println(m)
#define FREE_HEAP() ({ECHOLN(String("FREE_HEAP: ") + String(ESP.getFreeHeap()));})
#else
#define ECHO(m)
#define ECHOLN(m)
#define FREE_HEAP()
#endif

#endif /* APP_DEBUG_h */
