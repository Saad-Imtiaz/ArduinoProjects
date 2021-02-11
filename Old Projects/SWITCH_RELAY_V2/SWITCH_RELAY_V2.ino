int d=2;   // to store on or off value
void setup()
{pinMode(2,INPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
}
void loop()
{
d=digitalRead(2);
if(d==0)
{
 for (int counter = 1 ; counter <= 10; counter = counter +1)
digitalWrite(3,HIGH);
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(6,HIGH);
     delay (550);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
      
     delay (550);
  }
  
else
{
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
}
}
