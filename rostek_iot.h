/*
Design by Ngoc Vi
Ha Noi 01/2021

Code use for both esp32 and esp8266
*/


#ifndef RostekIot_h
#define RostekIot_h
#include <Arduino.h>
#include "app_debug.h"
#include <EEPROM.h>
#include <PubSubClient.h>
#include "esp32_webserver.h"
#include "pin_map.h"






WiFiClient espClient;
PubSubClient client(espClient);

struct wifi {
	bool normal_mode;	//TRUE - Mode Station
                        //FALSE - MODE AP
  	String ssid_1;
  	String pass_1;
  	String ssid_2;
  	String pass_2;
	uint32_t time_click_button;
}wifi;

struct mqtt {
  	String server;
  	int port;
	bool is_register_user;
  	String user;
  	String pass;
	unsigned long lastReconnectAttempt;
}mqtt;





void SetupConfigMode();       //mode AP
bool ConnectToWifi();         //mode Station
void ReadEeprom();
bool ScanNetworks(String ssid, bool debug);
void StartWebServer();
void ConnectToMqttServer();
void callbackMqttBroker(char* topic, byte* payload, unsigned int length);
void ReconnectToMqttServer();
void ButtonConfigClick();

#endif /* RostekIot_h */
