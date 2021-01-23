#include "rostek_iot.h"




void SetupConfigMode(){
	ECHOLN("Open AP....");
	WiFi.softAPdisconnect();
	WiFi.disconnect();
	server.close();
	delay(500);
	WiFi.mode(WIFI_AP_STA);


	uint8_t mac[WL_MAC_ADDR_LENGTH];
	WiFi.softAPmacAddress(mac);
	String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
	macID.toUpperCase();
	String SSID_AP_MODE = SSID_PRE_AP_MODE + macID;
	WiFi.softAP(SSID_AP_MODE.c_str());
	IPAddress APIP(192, 168, 4, 1);
	IPAddress gateway(192, 168, 4, 1);
	IPAddress subnet(255, 255, 255, 0);
	WiFi.softAPConfig(APIP, gateway, subnet);
	ECHOLN(SSID_AP_MODE);

	IPAddress myIP = WiFi.softAPIP();
	ECHO("IP address: ");
	ECHOLN(myIP);
}

void ReadEeprom(){
	//read wifi
	wifi.ssid_1 = "";
	for (int i = EEPROM_WIFI_SSID_1_START; i < EEPROM_WIFI_SSID_1_END; ++i){
		wifi.ssid_1 += char(EEPROM.read(i));
	}
	ECHO("SSID_1: ");
	ECHOLN(wifi.ssid_1);
	wifi.pass_1 = "";
	for (int i = EEPROM_WIFI_PASS_1_START; i < EEPROM_WIFI_PASS_1_END; ++i){
		wifi.pass_1 += char(EEPROM.read(i));
	}
	ECHO("PASS_1: ");
	ECHOLN(wifi.pass_1);
	wifi.ssid_2 = "";
	for (int i = EEPROM_WIFI_SSID_2_START; i < EEPROM_WIFI_SSID_2_END; ++i){
		wifi.ssid_2 += char(EEPROM.read(i));
	}
	ECHO("SSID_2: ");
	ECHOLN(wifi.ssid_2);
	wifi.pass_2 = "";
	for (int i = EEPROM_WIFI_PASS_2_START; i < EEPROM_WIFI_PASS_2_END; ++i){
		wifi.pass_2 += char(EEPROM.read(i));
	}
	ECHO("PASS_2: ");
	ECHOLN(wifi.pass_2);

	//read mqtt
	mqtt.server = "";
	for (int i = EEPROM_MQTT_SERVER_START; i < EEPROM_MQTT_SERVER_END; ++i){
		mqtt.server += char(EEPROM.read(i));
	}
	ECHO("MQTT SERVER: ");
	ECHOLN(mqtt.server);

	mqtt.port = char(EEPROM.read(EEPROM_MQTT_PORT));
	ECHO("MQTT PORT: ");
	ECHOLN(mqtt.server);

	if(char(EEPROM.read(EEPROM_IS_REGISTER_MQTT_USER) == 1)){
		mqtt.is_register_user = true;
		mqtt.user = "";
		for (int i = EEPROM_MQTT_USER_START; i < EEPROM_MQTT_USER_END; ++i){
			mqtt.server += char(EEPROM.read(i));
		}
		ECHO("MQTT USER: ");
		ECHOLN(mqtt.server);

		mqtt.pass = "";
		for (int i = EEPROM_MQTT_PASS_START; i < EEPROM_MQTT_PASS_END; ++i){
			mqtt.pass += char(EEPROM.read(i));
		}
		ECHO("MQTT PASS: ");
		ECHOLN(mqtt.pass);
	}
	else{
		mqtt.is_register_user = false;
		ECHOLN("MQTT no User and no Pass!");
	}
}

void ConnectToWifi(){
	WiFi.softAPdisconnect();
    WiFi.disconnect();
    server.close();
    WiFi.mode(WIFI_STA);        //bat che do station
	if(ScanNetworks(wifi.ssid_1)){
		WiFi.begin(wifi.ssid_1.c_str(), wifi.pass_1.c_str());
	}
	else if(ScanNetworks(wifi.ssid_2)){
		WiFi.begin(wifi.ssid_2.c_str(), wifi.pass_2.c_str());
	}
    
    
    int c = 0;
    ECHOLN("Waiting for Wifi to connect");
    while (c < 40) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("\rWifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());
            // digitalWrite(ledTestWifi, HIGH);
            // ConnecttoMqttServer();
            // return true;
        }
        if(!digitalRead(PIN_CONFIG)){
            break;
        }
        delay(500);
        ECHO(".");
        c++;
    }
    ECHOLN("");
    ECHOLN("Connect timed out");
    // return false;
}

bool ScanNetworks(String ssid) {
	int numberOfNetworks = WiFi.scanNetworks();

	ECHO("Number of networks found: ");
	ECHOLN(numberOfNetworks);

	for (int i = 0; i < numberOfNetworks; i++) {

		ECHO("Network name: ");
		ECHOLN(WiFi.SSID(i));

		ECHO("Signal strength: ");
		ECHOLN(WiFi.RSSI(i));

		// ECHO("MAC address: ");
		// ECHOLN(WiFi.BSSIDstr(i));

		// ECHO("Encryption type: ");
		// String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
		// ECHOLN(encryptionTypeDescription);
		// ECHOLN("-----------------------");

		if(WiFi.SSID(i) == ssid){
			return true;
		}
	}
	return false;
}





void setup() {
	// put your setup code here, to run once:
	WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
	Serial.begin(BAUDRATE_DEFAULT);
	EEPROM.begin(EEPROM_MEMORY);

	pinMode(PIN_CONFIG, INPUT);
	
	if(EEPROM.read(EEPROM_IS_REGISTER_WIFI) != 1){
		wifi.normal_mode = false;
		SetupConfigMode();
		StartWebServer();
	}
	else{
		wifi.normal_mode = true;
		ReadEeprom();
		ConnectToWifi();
		StartWebServer();
	}

}

void loop() {
	// put your main code here, to run repeatedly:

}
