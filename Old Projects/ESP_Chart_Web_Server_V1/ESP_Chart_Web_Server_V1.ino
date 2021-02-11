

//======================================================== PIN CONNECTIONS FOR THE SENSORS =======================================

// These constants won't change. They're used to give names to the pins used:
const int PHanalogInPin = 36;  // Analog input pin that the potentiometer is attached to need a 1.2k & 2.2k ohm
//const int analogOutPin = 26; // Analog output pin that the LED is attached to
const int lightanalogInPin = 39;
const int wateranalogInPin = 34;

 int PHsensorValue ;
 int watersensorValue ;
 int lightsensorValue ;
// value read from the pot
//int outputValue = 0;        // value output to the PWM (analog out)
//==================================================================================================================================

// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif


// Replace with your network credentials
const char* ssid = "Imtiaz";
const char* password = "Imtiaz832921az";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//=================================== pH Value =====================================
String readxaxis() {
  // Read the Ph Value
  float x;
  x = PHsensorValue;
  
  if (isnan(x)) {    
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(x);
    return String(x);
  }
}
//==================================  Water ======================================
String readyaxis() {
  float y ;
  y = watersensorValue;
  if (isnan(y)) {
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(y);
    return String(y);
  }
}
//================================ Light ========================================
String readzaxis() {
  float z;
  z = lightsensorValue;
  if (isnan(z)) {
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(z);
    return String(z);
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/X", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readxaxis().c_str());
  });
  server.on("/Y", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readyaxis().c_str());
  });
  server.on("/Z", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readzaxis().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  sensors();
}
