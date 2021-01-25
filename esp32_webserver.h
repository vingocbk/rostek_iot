#ifndef Esp32WebServer_h
#define Esp32WebServer_h


#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include "app_debug.h"
#include "pin_map.h"
#include <EEPROM.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define HTTP_PORT 80



void handleRoot();
void handleWifi();
void handleMQTT();
void handleSaveWifi();
void handleSaveMqtt();
void handleUpdate();
void handleUpdateUrl();
void handleUpdateFile();
void handleInfo();


#endif /* Esp32WebServer_h */
