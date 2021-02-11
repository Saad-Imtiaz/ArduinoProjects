int safety()
{
if ( digitalRead(limitPin) == HIGH)
{
        Serial.println("Every thing Stop.");
return 0; //Motor stops// 

}
else 
{ Serial.println("Everything is good.");
  }
return 1;

  
}
