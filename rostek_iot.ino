#include "rostek_iot.h"

extern AsyncWebServer server;
extern struct config config_network;
// extern web_setup_wifi;
// extern web_setup_mqtt;

void SetupConfigMode(){
	ECHOLN("Open AP....");
	WiFi.softAPdisconnect();
	WiFi.disconnect();
	delay(500);
	WiFi.mode(WIFI_AP);

	// ECHOLN("Open AP....");
	uint8_t mac[WL_MAC_ADDR_LENGTH];
	WiFi.softAPmacAddress(mac);
	String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
	macID.toUpperCase();
	String SSID_AP_MODE = SSID_PRE_AP_MODE + macID;
	// String SSID_AP_MODE = SSID_PRE_AP_MODE;
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

	String port_mqtt = "";
	for (int i = EEPROM_MQTT_PORT_START; i < EEPROM_MQTT_PORT_END; ++i){
		port_mqtt += char(EEPROM.read(i));
	}
	mqtt.port = port_mqtt.toInt();
	ECHO("MQTT PORT: ");
	ECHOLN(mqtt.port);

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

bool ConnectToWifi(){
	WiFi.softAPdisconnect();
    WiFi.disconnect();
//    server.close();
    WiFi.mode(WIFI_STA);        //bat che do station
	// if(ScanNetworks(wifi.ssid_1, true)){
	// 	WiFi.begin(wifi.ssid_1.c_str(), wifi.pass_1.c_str());
	// }
	// else if(ScanNetworks(wifi.ssid_2, false)){
	// 	WiFi.begin(wifi.ssid_2.c_str(), wifi.pass_2.c_str());
	// }
    // else{
	// 	ECHOLN("NO WIFI CAN CONNECT!");
	// 	delay(5000);
	// 	return false;
	// }
    
	WiFi.begin(wifi.ssid_1.c_str(), wifi.pass_1.c_str());
    int c = 0;
    ECHOLN("Waiting for Wifi to connect: " + wifi.ssid_1);
    while (c < 20) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("Wifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());
            // digitalWrite(ledTestWifi, HIGH);
            // ConnecttoMqttServer();
            return true;
        }
        if(!digitalRead(PIN_CONFIG)){
            break;
        }
        delay(500);
        ECHO(".");
        c++;
    }
    ECHOLN("");

	WiFi.begin(wifi.ssid_2.c_str(), wifi.pass_2.c_str());
    c = 0;
    ECHOLN("Waiting for Wifi to connect: " + wifi.ssid_2);
    while (c < 20) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("Wifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());
            // digitalWrite(ledTestWifi, HIGH);
            // ConnecttoMqttServer();
            return true;
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
    return false;
}

bool ScanNetworks(String ssid, bool debug){
	int numberOfNetworks = WiFi.scanNetworks();
	if(debug){
		ECHO("Number of networks found: ");
		ECHOLN(numberOfNetworks);
	}
	

	for (int i = 0; i < numberOfNetworks; i++) {

	if(debug){
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
		}
		String c = WiFi.SSID(i);
		ssid.trim();
		c.trim();
		if(ssid == c){
			return true;
		}

		// ECHO(ssid+c+ssid+c);
	}
	return false;
}

void StartWebServer(){
	server.on("/", HTTP_GET, handleRoot);
	server.on("/main", HTTP_GET, handleRoot);
	server.on("/wifi", HTTP_GET, handleWifi);
	server.on("/mqtt", HTTP_GET, handleMQTT);
	server.on("/update", HTTP_GET, handleUpdate);
	// server.on("/updateurl", HTTP_GET, handleUpdateUrl);
	// server.on("/updatefile", HTTP_POST,[]() {
	// 	server.sendHeader("Connection", "close");
	// 	server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
	// 	ESP.restart();
	// }, handleUpdateFile);
	server.on("/savewifi", HTTP_GET, handleSaveWifi);
	server.on("/savemqtt", HTTP_GET, handleSaveMqtt);
	server.on("/info", HTTP_GET, handleInfo);
	server.onNotFound(notFound);
	server.begin();
	Serial.println( "HTTP server started" );
}


void ConnectToMqttServer(){
	// client.setServer(mqtt_server, MQTT_PORT);
	client.setServer(mqtt.server.c_str(), mqtt.port);
    client.setCallback(callbackMqttBroker);
    ReconnectToMqttServer();
}

void callbackMqttBroker(char* topic, byte* payload, unsigned int length){
	//data receive from Mqtt server
	String Topic = String(topic);
    ECHO("TOPIC: ");
    ECHOLN(Topic);

    String data;
    for (int i = 0; i < length; i++) {
        data += char(payload[i]);
    }
    ECHO("DATA: ");
    ECHOLN(data);
}

void ReconnectToMqttServer(){
	String clientId = String(random(0xffffff), HEX);
	const char* willTopic = "ROSTEK/LWT";
    uint8_t willQos = 0;
    boolean willRetain = false;
	String willMessage = "{\"data\" : \"disconnect\"}";
	if(EEPROM.read(EEPROM_IS_REGISTER_MQTT_USER) == 1){
		if (client.connect(clientId.c_str(), mqtt.user.c_str(), mqtt.pass.c_str(), willTopic, willQos, willRetain, willMessage.c_str())) {
			ECHO("connected have user with id: ");
        	ECHOLN(clientId);
			client.subscribe("Rostek/iot");
        	ECHOLN("Done Subscribe Channel: Rostek/iot");
		}
	}
	else{
		if (client.connect(clientId.c_str(), willTopic, willQos, willRetain, willMessage.c_str())) {
			ECHO("connected no user with id: ");
        	ECHOLN(clientId);
			client.subscribe("Rostek/iot");
        	ECHOLN("Done Subscribe Channel: Rostek/iot");
		}
	}
	if(!client.connected()){
        ECHO("failed, rc=");
        ECHO(client.state());
        ECHOLN(" try again in 5 seconds");
    }
}


void ButtonConfigClick(){
	if(digitalRead(PIN_CONFIG) == HIGH){
        wifi.time_click_button = millis();
    }
	if(digitalRead(PIN_CONFIG) == LOW && (wifi.time_click_button + TIME_OUT_TO_CONFIG_MODE) <= millis()){
		// for (int i = 0; i <= EEPROM_MEMORY; i++){ 
        //     EEPROM.write(i, 0); 
        // }
		// EEPROM.commit();
		// ECHOLN("Reset EEPROM!");
		// delay(2000);
		wifi.normal_mode = false;
		SetupConfigMode();
		StartWebServer();
	}
}


void setup() {
	// put your setup code here, to run once:
	#ifdef ESP32
		WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
	#endif
	Serial.begin(BAUDRATE_DEFAULT);
	EEPROM.begin(EEPROM_MEMORY);
	delay(10);
	pinMode(PIN_CONFIG, INPUT);

	config_network.setup_wifi = false;
	config_network.setup_mqtt = false;
	
	if(EEPROM.read(EEPROM_IS_REGISTER_WIFI) != 1){
		wifi.normal_mode = false;
		ReadEeprom();
		SetupConfigMode();
		StartWebServer();
	}
	else{
		wifi.normal_mode = true;
		ReadEeprom();
		if(ConnectToWifi()){
			StartWebServer();
			ConnectToMqttServer();
		}
		
	}

}

void loop() {
	// put your main code here, to run repeatedly:
	if(wifi.normal_mode && WiFi.status() == WL_CONNECTED){
		if (!client.connected()) {
			unsigned long nowReconnectAttempt = millis();
			if (abs(nowReconnectAttempt - mqtt.lastReconnectAttempt) > MQTT_RECONNECT_TIME_WAIT) {
                mqtt.lastReconnectAttempt = nowReconnectAttempt;
                ReconnectToMqttServer();
            }
		}else{
			client.loop();
		}
	}

	if(wifi.normal_mode && WiFi.status() != WL_CONNECTED){
		if(ConnectToWifi()){
			StartWebServer();
			ConnectToMqttServer();
		}
	}

	ButtonConfigClick();

	//mode setup
	if(config_network.setup_wifi){
		ECHOLN("Setup Wifi");
		wifi.normal_mode = true;
		config_network.setup_wifi = false;
		ReadEeprom();
		if(ConnectToWifi()){
			StartWebServer();
			ConnectToMqttServer();
		}
	}
	if(config_network.setup_mqtt){
		ECHOLN("Setup Mqtt");
		config_network.setup_mqtt = false;
		ReadEeprom();
		ConnectToMqttServer();
	}
}
