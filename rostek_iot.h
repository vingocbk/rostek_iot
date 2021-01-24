#ifndef RostekIot_h
#define RostekIot_h

#include "app_debug.h"
#include <EEPROM.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "esp32_webserver.h"
#include "pin_map.h"

#include "soc/soc.h"  //Brownout detector was triggered
#include "soc/rtc_cntl_reg.h"




WiFiClient espClient;
PubSubClient client(espClient);

struct wifi {
	bool normal_mode;	//TRUE - Mode Station
                        //FALSE - MODE AP
  	String ssid_1;
  	String pass_1;
  	String ssid_2;
  	String pass_2;
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
bool ScanNetworks();
void StartWebServer();
void ConnectToMqttServer();
void callbackMqttBroker(char* topic, byte* payload, unsigned int length);
void ReconnectToMqttServer();

#endif /* RostekIot_h */
