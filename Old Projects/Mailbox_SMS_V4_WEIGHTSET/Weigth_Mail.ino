/*
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/
void weightsms() {
  int cw;
  int limit = 0;
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  weight=(scale.get_units(),1);
  Serial.print("Kgs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();

if (weight > limit)
{
limit = weight;
texmail= "You just recived some new mail,mail weight : " + String(weight);
sms.beginSMS(senderNumber);  
sms.print(texmail);
sms.endSMS();
sms.flush();
sms.beginSMS(owner);  
sms.print(texmail);
sms.endSMS();
}
if (weight == limit)
{}
if (weight < limit)
{ limit = weight;
  }

}
