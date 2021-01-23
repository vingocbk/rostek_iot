#include "esp32_webserver.h"

WebServer server(HTTP_PORT);
char htmlResponse[3000];


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
				<br><h3>Wifi SSID</h3>\
				<br><input type='text' name='wifi_ssid' id='wifi_ssid' size=15 autofocus>\
				<br><h3>Wifi PASSWORD</h3>\
				<br><input type='text' name='wifi_pass' id='wifi_pass' size=15 autofocus>\
				<br><button id=\"save_button\">Save</button>\
				<br><a href=\"main\"><button>Back to Main</button></a><br>\
				<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
				<script>\
					var ssid;\
					var password;\
					$('#save_button').click(function(e){\
					e.preventDefault();\
					ssid = $('#wifi_ssid').val();\
					password = $('#wifi_pass').val();\
					$.get('/savewifi?wifi_ssid=' + ssid + '&wifi_pass=' + password, function(data){\
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
	server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
	if (server.arg("wifi_ssid")!= ""){
		ECHOLN("wifi_ssid: " + server.arg("wifi_ssid"));
	}

	if (server.arg("wifi_pass")!= ""){
		ECHOLN("wifi_pass: " + server.arg("wifi_pass"));
	}
}

void handleSaveMqtt() {
	server.send(200, "application/json; charset=utf-8", "{\"status\":\"success\"}");
	if (server.arg("server")!= ""){
		ECHOLN("mqtt_server: " + server.arg("server"));
	}

	if (server.arg("port")!= ""){
		ECHOLN("mqtt_port: " + server.arg("port"));
	}

	if (server.arg("user")!= ""){
		ECHOLN("mqtt_user: " + server.arg("user"));
	}

	if (server.arg("pass")!= ""){
		ECHOLN("mqtt_pass: " + server.arg("pass"));
	}
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

void StartWebServer(){
	
}
