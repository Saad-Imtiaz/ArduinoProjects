void mail()
{

weight = (scale.get_units(), 1);
Serial.print("Weight : ");
Serial.print(weight);
Serial.print("Grams.");
Serial.println();

if (weight > limit)
{
limit = weight;
texmail= "You got mail, Grams: " + String(weight);
sms.beginSMS(OWNER);  
sms.print(texmail);
sms.endSMS();
Serial.println("Mail Notification Sent");
timer();

}

else if (weight == limit)
{}

else if (weight < limit)
{ limit = 0; }
}




  
