#ifndef RostekIot_h
#define RostekIot_h

#include "app_debug.h"
#include <EEPROM.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include "esp32_webserver.h"


#include "soc/soc.h"  //Brownout detector was triggered
#include "soc/rtc_cntl_reg.h"

#define BAUDRATE_DEFAULT 115200
#define EEPROM_MEMORY  512

#define PIN_CONFIG	5

#define EEPROM_IS_REGISTER_WIFI         1
#define EEPROM_WIFI_SSID_1_START        2
#define EEPROM_WIFI_SSID_1_END          32
#define EEPROM_WIFI_PASS_1_START        33
#define EEPROM_WIFI_PASS_1_END          63
#define EEPROM_WIFI_SSID_2_START        64
#define EEPROM_WIFI_SSID_2_END          94
#define EEPROM_WIFI_PASS_2_START        95
#define EEPROM_WIFI_PASS_2_END          125
#define EEPROM_MQTT_SERVER_START        126
#define EEPROM_MQTT_SERVER_END          156
#define EEPROM_MQTT_PORT                157
#define EEPROM_IS_REGISTER_MQTT_USER    158
#define EEPROM_MQTT_USER_START          159
#define EEPROM_MQTT_USER_END            189
#define EEPROM_MQTT_PASS_START          190
#define EEPROM_MQTT_PASS_END            220

#define WL_MAC_ADDR_LENGTH              6
#define SSID_PRE_AP_MODE    "ROSTEK-"



extern WebServer server(HTTP_PORT);

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
}mqtt;


void SetupConfigMode();         //mode AP
void ConnectToWifi();         //mode Station
void ReadEeprom();
bool ScanNetworks();


#endif /* RostekIot_h */
