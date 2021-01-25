#include "esp32_webserver.h"

WebServer server(HTTP_PORT);
char htmlResponse[3000];

struct config
{
	/* data */
	bool setup_wifi = false;
	bool setup_mqtt = false;

}config_network;

//-----------------------------STATION-----------------------//
// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input2: <input type="text" name="input2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input3: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";



//-----------------------------AP MODE-----------------------//
void handleRoot(){
	snprintf ( htmlResponse, 3000,
		"<!DOCTYPE html>\
		<html lang=\"en\">\
		<head>\
			<meta charset=\"utf-8\">\
			<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
		</head>\
		<body>\
			<center>\
				<h1>ROSTEK MAIN</h1>\
				<br><a href=\"wifi\"><button>Config Wifi</button></a><br>\
				<br><a href=\"mqtt\"><button>Config MQTT</button></a><br>\
				<br><a href=\"update\"><button>Firmware Update</button></a><br>\
				<br><a href=\"info\"><button>Get Info</button></a><br>\
			</center>\
		</body>\
		</html>"); 

	server.send ( 200, "text/html", htmlResponse ); 
}

void handleWifi() {
	snprintf ( htmlResponse, 3000,
		"<!DOCTYPE html>\
		<html lang=\"en\">\
		<head>\
			<meta charset=\"utf-8\">\
			<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
		</head>\
		<body>\
			<center>\
				<h1>CONFIG WIFI</h1>\
				<br><h3>Wifi SSID 1</h3>\
				<br><input type='text' name='wifi_ssid_1' id='wifi_ssid_1' size=15 autofocus>\
				<br><h3>Wifi PASSWORD 1</h3>\
				<br><input type='text' name='wifi_pass_1' id='wifi_pass_1' size=15 autofocus>\
				<br><h3>Wifi SSID 2</h3>\
				<br><input type='text' name='wifi_ssid_2' id='wifi_ssid_2' size=15 autofocus>\
				<br><h3>Wifi PASSWORD 2</h3>\
				<br><input type='text' name='wifi_pass_2' id='wifi_pass_2' size=15 autofocus>\
				<br><button id=\"save_button\">Save</button>\
				<br><a href=\"main\"><button>Back to Main</button></a><br>\
				<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
				<script>\
					var ssid_1;\
					var password_1;\
					var ssid_2;\
					var password_2;\
					$('#save_button').click(function(e){\
					e.preventDefault();\
					ssid_1 = $('#wifi_ssid_1').val();\
					password_1 = $('#wifi_pass_1').val();\
					ssid_2 = $('#wifi_ssid_2').val();\
					password_2 = $('#wifi_pass_2').val();\
					$.get('/savewifi?wifi_ssid_1=' + ssid_1 + '&wifi_pass_1=' + password_1 + '&wifi_ssid_2=' + ssid_2 + '&wifi_pass_2=' + password_2, function(data){\
						console.log(data);\
					});\
					});\      
				</script>\
			</center>\
		</body>\
		</html>"); 

	server.send ( 200, "text/html", htmlResponse ); 
}


void handleMQTT() {
	snprintf ( htmlResponse, 3000,
	"<!DOCTYPE html>\
	<html lang=\"en\">\
		<head>\
		<meta charset=\"utf-8\">\
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
		</head>\
		<body>\
			<center>\
				<h1>CONFIG MQTT</h1>\
				<br><h3>MQTT SERVER</h3>\
				<br><input type='text' name='mqtt_server' id='mqtt_server' size=15 autofocus>\
				<br><h3>MQTT PORT</h3>\
				<br><input type='text' name='mqtt_port' id='mqtt_port' size=15 autofocus>\
				<br><h3>MQTT USER</h3>\
				<br><input type='text' name='mqtt_user' id='mqtt_user' size=15 autofocus>\
				<br><h3>MQTT PASS</h3>\
				<br><input type='text' name='mqtt_pass' id='mqtt_pass' size=15 autofocus>\
				<br><button id=\"save_button\">Save</button>\
				<br><a href=\"main\"><button>Back to Main</button></a><br>\
				<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
				<script>\
				var server;\
				var port;\
				var user;\
				var pass;\
				$('#save_button').click(function(e){\
					e.preventDefault();\
					server = $('#mqtt_server').val();\
					port = $('#mqtt_port').val();\
					user = $('#mqtt_user').val();\        
					pass = $('#mqtt_pass').val();\
					$.get('/savemqtt?server=' + server + '&port=' + port + '&user=' + user + '&pass=' + pass, function(data){\
					console.log(data);\
					});\
				});\      
				</script>\
			</center>\
		</body>\
	</html>"); 

	server.send ( 200, "text/html", htmlResponse );  

}


void handleSaveWifi() {
	ECHOLN("----");
	server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
	if (server.arg("wifi_ssid_1")!= ""){
		// EEPROM.write(EEPROM_IS_REGISTER_WIFI, 1);

		// String ssid_1 = server.arg("wifi_ssid_1");
		ECHOLN("wifi_ssid_1: " + server.arg("wifi_ssid_1"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_SSID_1_START; i <= EEPROM_WIFI_SSID_1_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom ssid_1:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("wifi_ssid_1").length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_SSID_1_START, server.arg("wifi_ssid_1")[i]);             
            ECHO(server.arg("wifi_ssid_1")[i]);
        }
		ECHOLN("");
	}

	if (server.arg("wifi_pass_1")!= ""){
		// String pass_1 = server.arg("wifi_pass_1");
		ECHOLN("wifi_pass_1: " + server.arg("wifi_pass_1"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_PASS_1_START; i <= EEPROM_WIFI_PASS_1_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom pass_1:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("wifi_pass_1").length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_PASS_1_START, server.arg("wifi_pass_1")[i]);             
            ECHO(server.arg("wifi_pass_1")[i]);
        }
		ECHOLN("");
	}

	if (server.arg("wifi_ssid_2")!= ""){
		// String pass_1 = server.arg("wifi_ssid_2");
		ECHOLN("wifi_ssid_2: " + server.arg("wifi_ssid_2"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_SSID_2_START; i <= EEPROM_WIFI_SSID_2_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom ssid_2:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("wifi_ssid_2").length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_SSID_2_START, server.arg("wifi_ssid_2")[i]);             
            ECHO(server.arg("wifi_ssid_2")[i]);
        }
		ECHOLN("");
	}

	if (server.arg("wifi_pass_2")!= ""){
		// String pass_1 = server.arg("wifi_pass_2");
		ECHOLN("wifi_pass_2: " + server.arg("wifi_pass_2"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_WIFI_PASS_2_START; i <= EEPROM_WIFI_PASS_2_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom pass_2:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("wifi_pass_2").length(); ++i){
            EEPROM.write(i+EEPROM_WIFI_PASS_2_START, server.arg("wifi_pass_2")[i]);             
            ECHO(server.arg("wifi_pass_2")[i]);
        }
		ECHOLN("");
	}

	// EEPROM.commit();
	// ECHOLN("Done writing!");
}

void handleSaveMqtt() {
	server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
	if (server.arg("server")!= ""){
		// String server = server.arg("server");
		ECHOLN("server: " + server.arg("server"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_SERVER_START; i <= EEPROM_MQTT_SERVER_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom server:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("server").length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_SERVER_START, server.arg("server")[i]);             
            ECHO(server.arg("server")[i]);
        }
		ECHOLN("");
	}

	if (server.arg("port")!= ""){
		// String port = server.arg("port");
		ECHOLN("port: " + server.arg("port"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_PORT_START; i <= EEPROM_MQTT_PORT_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom port:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("port").length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_PORT_START, server.arg("port")[i]);             
            ECHO(server.arg("port")[i]);
        }
		ECHOLN("");
	}

	if (server.arg("user")!= ""){
		EEPROM.write(EEPROM_IS_REGISTER_MQTT_USER, 1);
		// String user = server.arg("user");
		ECHOLN("user: " + server.arg("user"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_USER_START; i <= EEPROM_MQTT_USER_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom user:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("user").length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_USER_START, server.arg("user")[i]);             
            ECHO(server.arg("user")[i]);
        }
		ECHOLN("");
	}else{
		EEPROM.write(EEPROM_IS_REGISTER_MQTT_USER, 0);
	}

	if (server.arg("pass")!= ""){
		// String pass = server.arg("pass");
		ECHOLN("pass: " + server.arg("pass"));
		ECHOLN("clearing eeprom");
        for (int i = EEPROM_MQTT_PASS_START; i <= EEPROM_MQTT_PASS_END; i++){ 
            EEPROM.write(i, 0); 
        }
		ECHOLN("writing eeprom pass:");
        ECHO("Wrote: ");
        for (int i = 0; i < server.arg("pass").length(); ++i){
            EEPROM.write(i+EEPROM_MQTT_PASS_START, server.arg("pass")[i]);             
            ECHO(server.arg("pass")[i]);
        }
		ECHOLN("");
	}

	EEPROM.commit();
	ECHOLN("Done writing!");
}

void handleUpdate(){
	snprintf ( htmlResponse, 3000,
	"<!DOCTYPE html>\
	<html lang=\"en\">\
		<head>\
		<meta charset=\"utf-8\">\
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
		</head>\
		<body>\
			<center>\
				<h1>FIRMWARE UPDATE</h1>\
				<br><h3>HTTP URL</h3>\
				<br><input type='text' name='update_url' id='update_url' size=15 autofocus>\
				<br><button id=\"button_url\">Update Url</button>\
				<br><h3>UPDATE FROM FILE</h3><br>\
				<form\
				method='POST' action='/update'\
				enctype='multipart/form-data'>\
				<input type='file' name='update'>\
				<input type='submit' value='Update File'>\
				</form>\
				<br><a href=\"main\"><button>Back to Main</button></a><br>\
			</center>\
		</body>\
	</html>"); 


	server.send ( 200, "text/html", htmlResponse );
}



void handleUpdateUrl(){
	WiFiClient client;
	// The line below is optional. It can be used to blink the LED on the board during flashing
	// The LED will be on during download of one buffer of data from the network. The LED will
	// be off during writing that buffer to flash
	// On a good connection the LED should flash regularly. On a bad connection the LED will be
	// on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
	// value is used to put the LED on. If the LED is on with HIGH, that value should be passed
	// ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);



	t_httpUpdate_return ret = httpUpdate.update(client, "http://server/file.bin");
	// Or:
	//t_httpUpdate_return ret = httpUpdate.update(client, "server", 80, "file.bin");

	switch (ret) {
		case HTTP_UPDATE_FAILED:
		Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
		break;

		case HTTP_UPDATE_NO_UPDATES:
		ECHOLN("HTTP_UPDATE_NO_UPDATES");
		break;

		case HTTP_UPDATE_OK:
		ECHOLN("HTTP_UPDATE_OK");
		break;
	}
}

void handleUpdateFile(){
	HTTPUpload& upload = server.upload();
		if (upload.status == UPLOAD_FILE_START) {
		Serial.setDebugOutput(true);
		Serial.printf("Update: %s\n", upload.filename.c_str());
		if (!Update.begin()) { //start with max available size
			Update.printError(Serial);
		}
	} else if (upload.status == UPLOAD_FILE_WRITE) {
		if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
			Update.printError(Serial);
		}
	} else if (upload.status == UPLOAD_FILE_END) {
		if (Update.end(true)) { //true to set the size to the current progress
			Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
		} else {
			Update.printError(Serial);
		}
		Serial.setDebugOutput(false);
	} else {
		Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
	}
}

void handleInfo(){
	snprintf ( htmlResponse, 3000,
	"<!DOCTYPE html>\
	<html lang=\"en\">\
		<head>\
		<meta charset=\"utf-8\">\
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
		</head>\
		<body>\
			<center>\
				<h1>GET INFO</h1>\
				<br><a href=\"main\"><button>Back to Main</button></a><br>\
			</center>\
		</body>\
	</html>"); 

	server.send ( 200, "text/html", htmlResponse );
}
