/*
Design by Ngoc Vi
Ha Noi 01/2021

Code use for both esp32 and esp8266

need add library:
PubSubClient.h: https://github.com/knolleary/pubsubclient.git
AsyncTCP.h: https://github.com/me-no-dev/AsyncTCP.git
ESPAsyncTCP.h: https://github.com/me-no-dev/ESPAsyncTCP.git
ESPAsyncWebServer.h: https://github.com/me-no-dev/ESPAsyncWebServer.git
*/


#ifndef Esp32WebServer_h
#define Esp32WebServer_h

#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
    #include <Update.h>
    #include <HTTPClient.h>
    #include <HTTPUpdate.h>
    #include <AsyncTCP.h>
    #include "soc/soc.h"  //Brownout detector was triggered
    #include "soc/rtc_cntl_reg.h"
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESPAsyncTCP.h>
    #include <ESP8266HTTPClient.h>
    #include <ESP8266httpUpdate.h>
    // #include <ESP8266WebServer.h>
    // #define PROGMEM __attribute__((section( "\".irom.text." __FILE__ "." __STRINGIZE(__LINE__) "."  __STRINGIZE(__COUNTER__) "\"")))
    // #define ICACHE_RODATA_ATTR  __attribute__((section(".irom.text")))
    // #define PROGMEM   ICACHE_RODATA_ATTR
#endif

#include "app_debug.h"
#include "pin_map.h"
#include <EEPROM.h>

#include <ESPAsyncWebServer.h>

#define HTTP_PORT 80

struct config
{
	/* data */
	bool setup_wifi;
	bool setup_mqtt;

};

void handleRoot(AsyncWebServerRequest *request);
void handleWifi(AsyncWebServerRequest *request);
void handleMQTT(AsyncWebServerRequest *request);
void handleSaveWifi(AsyncWebServerRequest *request);
void handleSaveMqtt(AsyncWebServerRequest *request);
void handleUpdate(AsyncWebServerRequest *request);
void handleUpdateUrl(AsyncWebServerRequest *request);
void handleUpdateFile(AsyncWebServerRequest *request);
void handleInfo(AsyncWebServerRequest *request);
void notFound(AsyncWebServerRequest *request);

#endif /* Esp32WebServer_h */
