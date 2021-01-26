#include "esp32_webserver.h"

AsyncWebServer server(HTTP_PORT);

config config_network;

const char index_html_handle_root[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<h1>ROSTEK MAIN</h1>
			<br><a href=\wifi><button>Config Wifi</button></a><br>
			<br><a href=\mqtt><button>Config MQTT</button></a><br>
			<br><a href=\update><button>Firmware Update</button></a><br>
			<br><a href=\info><button>Get Info</button></a><br>
		</center>
	</body></html>)rawliteral";

void handleRoot(AsyncWebServerRequest *request){

	request->send_P(200, "text/html", index_html_handle_root);
}


const char index_html_handle_wifi[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<form action="/savewifi">
				<h1>CONFIG WIFI</h1><br>
				<h3>WIFI SSID 1</h3><br>
				<input type="text" name="wifi_ssid_1"><br>
				<h3>WIFI PASS 1</h3><br>
				<input type="text" name="wifi_pass_1"><br>
				<h3>WIFI SSID 2</h3><br>
				<input type="text" name="wifi_ssid_2"><br>
				<h3>WIFI PASS 2</h3><br>
				<input type="text" name="wifi_pass_2"><br>
				<br><input type="submit" value="Save">
			</form><br>
			<br><a href=\main><button>Back to Main</button></a><br>
		</center>
	</body></html>)rawliteral";

void handleWifi(AsyncWebServerRequest *request) {

	request->send_P(200, "text/html", index_html_handle_wifi);
}

const char index_html_handle_mqtt[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<form action="/savemqtt">
				<h1>CONFIG MQTT SERVER</h1><br>
				<h3>MQTT SERVER</h3><br>
				<input type="text" name="mqtt_server"><br>
				<h3>MQTT PORT</h3><br>
				<input type="text" name="mqtt_port"><br>
				<h3>MQTT USER</h3><br>
				<input type="text" name="mqtt_user"><br>
				<h3>MQTT PASS</h3><br>
				<input type="text" name="mqtt_pass"><br>
				<br><input type="submit" value="Save">
			</form><br>
			<br><a href=\main><button>Back to Main</button></a><br>
		</center>
	</body></html>)rawliteral";
void handleMQTT(AsyncWebServerRequest *request) {
	request->send_P(200, "text/html", index_html_handle_mqtt);
}



const char index_html_handle_save_wifi[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<h1>DONE SETUP WIFI</h1><br>
		</center>
	</body></html>)rawliteral";
void handleSaveWifi(AsyncWebServerRequest *request) {
	request->send_P(200, "text/html", index_html_handle_save_wifi);
	if (request->hasParam("wifi_ssid_1")){
		EEPROM.write(EEPROM_IS_REGISTER_WIFI, 1);

		String ssid_1 = request->getParam("wifi_ssid_1")->value();
		ECHOLN("wifi_ssid_1: " + ssid_1);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_SSID_1_START; i <= EEPROM_WIFI_SSID_1_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom ssid_1:");
        // ECHO("Wrote: ");
        for (int i = 0; i < ssid_1.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_SSID_1_START, ssid_1[i]);             
            // ECHO(ssid_1[i]);
        }
		// ECHOLN("");
	}

	if (request->hasParam("wifi_pass_1")){
		String pass_1 = request->getParam("wifi_pass_1")->value();
		ECHOLN("wifi_pass_1: " + pass_1);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_PASS_1_START; i <= EEPROM_WIFI_PASS_1_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom pass_1:");
        // ECHO("Wrote: ");
        for (int i = 0; i < pass_1.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_PASS_1_START, pass_1[i]);             
            // ECHO(pass_1[i]);
        }
		// ECHOLN("");
	}

	if (request->hasParam("wifi_ssid_2")){
		String ssid_2 = request->getParam("wifi_ssid_2")->value();
		ECHOLN("wifi_ssid_2: " + ssid_2);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_SSID_2_START; i <= EEPROM_WIFI_SSID_2_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom ssid_2:");
        // ECHO("Wrote: ");
        for (int i = 0; i < ssid_2.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_SSID_2_START, ssid_2[i]);             
            // ECHO(ssid_2[i]);
        }
		// ECHOLN("");
	}

	if (request->hasParam("wifi_pass_2")){
		String pass_2 = request->getParam("wifi_pass_2")->value();
		ECHOLN("wifi_pass_2: " + pass_2);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_PASS_2_START; i <= EEPROM_WIFI_PASS_2_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom pass_2:");
        // ECHO("Wrote: ");
        for (int i = 0; i < pass_2.length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_PASS_2_START, pass_2[i]);             
            // ECHO(pass_2[i]);
        }
		// ECHOLN("");
	}

	EEPROM.commit();
	ECHOLN("Done writing!");
	config_network.setup_wifi = true;
}

const char index_html_handle_save_mqtt[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<h1>DONE SETUP MQTT SERVER</h1><br>
			<br><a href=\main><button>Back to Main</button></a><br>
		</center>
	</body></html>)rawliteral";
void handleSaveMqtt(AsyncWebServerRequest *request) {
	request->send_P(200, "text/html", index_html_handle_save_mqtt);
	if (request->hasParam("mqtt_server")){
		String server = request->getParam("mqtt_server")->value();
		ECHOLN("server: " + server);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_SERVER_START; i <= EEPROM_MQTT_SERVER_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom server:");
        // ECHO("Wrote: ");
        for (int i = 0; i < server.length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_SERVER_START, server[i]);             
            // ECHO(server[i]);
        }
		// ECHOLN("");
	}

	if (request->hasParam("mqtt_port")){
		String port = request->getParam("mqtt_port")->value();
		ECHOLN("port: " + port);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_PORT_START; i <= EEPROM_MQTT_PORT_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom port:");
        // ECHO("Wrote: ");
        for (int i = 0; i < port.length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_PORT_START, port[i]);             
            // ECHO(port[i]);
        }
		// ECHOLN("");
	}

	if (request->hasParam("mqtt_user")){
		
		String user = request->getParam("mqtt_user")->value();
		ECHOLN("user: " + user);
		if(user != ""){
			EEPROM.write(EEPROM_IS_REGISTER_MQTT_USER, 1);
			// ECHOLN("clearing eeprom");
			for (int i = EEPROM_MQTT_USER_START; i <= EEPROM_MQTT_USER_END; i++){ 
				EEPROM.write(i, 0); 
			}
			// ECHOLN("writing eeprom user:");
			// ECHO("Wrote: ");
			for (int i = 0; i < user.length(); ++i){
				EEPROM.write(i+EEPROM_MQTT_USER_START, user[i]);             
				// ECHO(user[i]);
			}
			// ECHOLN("");
		}else{
			EEPROM.write(EEPROM_IS_REGISTER_MQTT_USER, 0);
		}
		
	}else{
		EEPROM.write(EEPROM_IS_REGISTER_MQTT_USER, 0);
		for (int i = EEPROM_MQTT_USER_START; i <= EEPROM_MQTT_USER_END; i++){ 
			EEPROM.write(i, 0); 
		}
	}

	if (request->hasParam("mqtt_pass")){
		String pass = request->getParam("mqtt_pass")->value();
		ECHOLN("pass: " + pass);
		// ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_PASS_START; i <= EEPROM_MQTT_PASS_END; i++){ 
            EEPROM.write(i, 0); 
        }
		// ECHOLN("writing eeprom pass:");
        // ECHO("Wrote: ");
        for (int i = 0; i < pass.length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_PASS_START, pass[i]);             
            // ECHO(pass[i]);
        }
		// ECHOLN("");
	}

	EEPROM.commit();
	ECHOLN("Done writing!");

	config_network.setup_mqtt = true;
}

const char index_html_handle_update[] PROGMEM = R"=====(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<h1>FIRMWARE UPDATE</h1>
			<form action="/updateurl">
				<h3>HTTP URL</h3><br>
				<input type="text" name="http_url"><br>
				<input type="submit" value="Update Url">
			</form><br>
			<form
				method='POST' action='/updatefile'
				enctype='multipart/form-data'>
				<input type='file' name='update'>
				<input type='submit' value='Update File'>
			</form>
			<br><a href=\main><button>Back to Main</button></a><br>
		</center>
	</body></html>)=====";
void handleUpdate(AsyncWebServerRequest *request){
	

	request->send_P(200, "text/html", index_html_handle_update);
}



void handleUpdateUrl(AsyncWebServerRequest *request){
	WiFiClient client;
	// The line below is optional. It can be used to blink the LED on the board during flashing
	// The LED will be on during download of one buffer of data from the network. The LED will
	// be off during writing that buffer to flash
	// On a good connection the LED should flash regularly. On a bad connection the LED will be
	// on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
	// value is used to put the LED on. If the LED is on with HIGH, that value should be passed
	// ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);



	// t_httpUpdate_return ret = httpUpdate.update(client, "http://server/file.bin");
	// // Or:
	// //t_httpUpdate_return ret = httpUpdate.update(client, "server", 80, "file.bin");

	// switch (ret) {
	// 	case HTTP_UPDATE_FAILED:
	// 	Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
	// 	break;

	// 	case HTTP_UPDATE_NO_UPDATES:
	// 	ECHOLN("HTTP_UPDATE_NO_UPDATES");
	// 	break;

	// 	case HTTP_UPDATE_OK:
	// 	ECHOLN("HTTP_UPDATE_OK");
	// 	break;
	// }
}

void handleUpdateFile(AsyncWebServerRequest *request){
	// HTTPUpload& upload = server.upload();
	// 	if (upload.status == UPLOAD_FILE_START) {
	// 	Serial.setDebugOutput(true);
	// 	Serial.printf("Update: %s\n", upload.filename.c_str());
	// 	if (!Update.begin()) { //start with max available size
	// 		Update.printError(Serial);
	// 	}
	// } else if (upload.status == UPLOAD_FILE_WRITE) {
	// 	if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
	// 		Update.printError(Serial);
	// 	}
	// } else if (upload.status == UPLOAD_FILE_END) {
	// 	if (Update.end(true)) { //true to set the size to the current progress
	// 		Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
	// 	} else {
	// 		Update.printError(Serial);
	// 	}
	// 	Serial.setDebugOutput(false);
	// } else {
	// 	Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
	// }
}

const char index_html_handle_info[] PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
		<title>ESP Input Form</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		</head><body>
		<center>
			<br><a href=\main><button>Back to Main</button></a><br>
		</center>
	</body></html>)rawliteral";
void handleInfo(AsyncWebServerRequest *request){
	request->send_P(200, "text/html", index_html_handle_info);
}


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
