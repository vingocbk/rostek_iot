#ifndef PINMAP_h
#define PINMAP_h

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
#define EEPROM_MQTT_PORT_START          157
#define EEPROM_MQTT_PORT_END            165
#define EEPROM_IS_REGISTER_MQTT_USER    166
#define EEPROM_MQTT_USER_START          167
#define EEPROM_MQTT_USER_END            197
#define EEPROM_MQTT_PASS_START          198
#define EEPROM_MQTT_PASS_END            228

#define WL_MAC_ADDR_LENGTH              6
#define SSID_PRE_AP_MODE    "ROSTEK-"
#define MQTT_RECONNECT_TIME_WAIT		2000


#endif /* PINMAP_h */