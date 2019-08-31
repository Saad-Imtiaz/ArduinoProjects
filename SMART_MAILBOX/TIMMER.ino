int period = 30000;
unsigned long time_now = 0;
 

void timer()
{
    if(millis() > time_now + period){
        time_now = millis();
        Serial.println("30 Secounds Timer");
    }
   
}
