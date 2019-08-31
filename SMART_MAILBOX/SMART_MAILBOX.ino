
#include <MKRGSM.h>
#include <HX711.h>

const char PINNUMBER[] = "";
const char OWNER[10] = "";

GSM gsmAccess;
GSM_SMS sms;
HX711 scale;

#define calibration_factor +385.20 
#define DOUT  3
#define CLK  2

//============= Variables ==============

int weight = 0;
int limit = 20;
String texmail = "";




void setup() 

{
  
  Serial.begin(9600);

  Serial.println("SMS Messages Sender");
  
//========== Start GSM shield ===========

  bool connected = false;
  while (!connected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) 
    {
      connected = true;
    } 
    else 
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");
  
//============ Weight Sensor ===========
   scale.begin(DOUT, CLK);
   scale.set_scale(calibration_factor);
   scale.tare();
   
}

void loop() 
{
mail();


}
