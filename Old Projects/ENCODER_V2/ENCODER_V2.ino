//Arduino code for controlling stepper motor from encoder
//video at https://www.youtube.com/watch?v=2dh6TIkN6jE
//reconstructed code from 5+ years ago
//untested in current form

 #define encoder_a 2    //encoder a = arduino pin 2 
 #define encoder_b 3    //encoder b = arduino pin 3 
 #define motor_step 4    //motor step = arduino pin 4 
 #define motor_direction 5    //motor direction = arduino pin 5
const int limitPin = 7;
int var = 0;
int x = 0;
int switches_abc = 0;
int a=2;
int b=2;
int c=2;
int safe = 1;
volatile long motor_position, encoder; 

void setup () 
{ pinMode(9,INPUT); 
pinMode(10,INPUT);
pinMode(11,INPUT);

  
   pinMode(limitPin,INPUT);
    //set up the various outputs 
    pinMode(motor_step, OUTPUT); 
    pinMode(motor_direction, OUTPUT); 
    // then the encoder inputs 
    pinMode(encoder_a, INPUT); 
    pinMode(encoder_b, INPUT); 
    digitalWrite(encoder_a, HIGH); 
    digitalWrite(encoder_b, HIGH);
    // encoder pin on interrupt 0 (pin 2) 
    attachInterrupt(0, encoderPinChangeA, CHANGE); 
    // encoder pin on interrupt 1 (pin 3) 
    attachInterrupt(1, encoderPinChangeB, CHANGE); 
    encoder = 0; 
}

void encoderPinChangeA() 
{
    if (digitalRead(encoder_a) == digitalRead(encoder_b)) 
    {
        encoder--;
    } 
    else
    {
        encoder++;
    } 
} 

void encoderPinChangeB() 
{
    if (digitalRead(encoder_a) != digitalRead(encoder_b)) 
    { 
        encoder--; 
    } 
    else 
    { 
        encoder++; 
    } 
}


void loop() 
{ 
  a=digitalRead(9);
  b=digitalRead(10);
  c=digitalRead(11);

  if (a == 0)
  {
    switches_abc = 1;
  }
  else
 {
  switches_abc = 0;
 }
  if (b == 0)
  {
    switches_abc = 2;
  }
  else
 {
  switches_abc = 0;
 }
  if (c == 0)
  {
    switches_abc = 3;
  }
  else
 {
  switches_abc = 0;
 }


safe = safety();
motor(safe);
 

// make the limit switch no 2 and also all the push buttons that give 1 2 and 3 respectively  for the cases



}
