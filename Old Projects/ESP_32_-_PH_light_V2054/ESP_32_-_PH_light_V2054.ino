#include <WiFi.h>
#include <WebServer.h>

//======================================================== PIN CONNECTIONS FOR THE SENSORS =======================================

// These constants won't change. They're used to give names to the pins used:
const int PHanalogInPin = 36;  // Analog input pin that the potentiometer is attached to need a 1.2k & 2.2k ohm
//const int analogOutPin = 26; // Analog output pin that the LED is attached to
const int lightanalogInPin = 39;
const int wateranalogInPin = 34;

int PHsensorValue = 0;
int watersensorValue = 0;
int lightsensorValue = 0;// value read from the pot
//int outputValue = 0;        // value output to the PWM (analog out)
//==================================================================================================================================







/*Put your SSID & Password*/
const char* ssid = "Imtiaz";  // Enter SSID here
const char* password = "Imtiaz832921az";  //Enter Password here

WebServer server(80);             

int PH, WT, LI;
 
void setup() {
  Serial.begin(115200);
  delay(100);
         

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  sensors();

}

void handle_OnConnect() {

  PH = PHsensorValue; // Gets the values of the PHsensorValue;
   
  WT = watersensorValue;// Gets the values of the watersensorValue;
  LI = lightsensorValue;// Gets the values of the lightsensorValue
   server.send(200, "text/html", SendHTML(PH,WT,LI));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
  String SendHTML(float PH1,float WT1,float LI1)
{
  String ptr = "<!DOCTYPE html> <html>\n";
 ptr +="<head><meta http-equiv=”refresh” content=”5″></head>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Sensor Monitoring System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 Sensor Monitoring System</h1>\n";
  
  ptr +="<p>pH Levels: ";
ptr +=(int)PH1;
  ptr +="pH</p>";
  ptr +="<p>Water Level: ";
 ptr +=(int)WT1;
  ptr +="%</p>";
  ptr +="<p>Light Levels: ";
ptr +=(int)LI1;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
