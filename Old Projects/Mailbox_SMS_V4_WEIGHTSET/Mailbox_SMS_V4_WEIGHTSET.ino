#include <HX711.h>

#include "arduino_secrets.h"
#include <MKRGSM.h>
GSM gsmAccess;
GSM_SMS sms;
HX711 scale;

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3
#define CLK  2


char PINNUMBER [] = SECRET_PINNUMBER;
String sender = SECRET_YOUR_NUMBER;
char senderNumber[20];

int weight;
String texmail ="";
char checktxt[] = {'N','U','M'};
char owner [12]= "";
char smss[15]= " " ;

String str;

void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;      // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("SMS Messages Receiver");

  // connection state
  bool connected = false;

  // Start GSM connection
  while (!connected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");

Serial.println("HX711 scale");


  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
 
}

void loop()
{
   char c;
  String texmsg = "";
 
  // If there are any SMSs available()
  if (sms.available())
{
    Serial.println("Message received from: ");
    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);
    
   c = (sms.read());
   str=String(c); 
   str.toCharArray(smss,15); 
 
   changeowner();    
}
weightsms();
}
