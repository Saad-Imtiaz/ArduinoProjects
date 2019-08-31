String str= "";
char a [10] = "Saad Imtiaz"; 
char b[20]= "";


int period = 300000;
unsigned long time_now = 0;



void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("SMS Messages Sender");

  // connection state
 str = String(a);
  str.toCharArray(b,20); 
  Serial.println("OUTPUT of B from A : ");
  Serial.println(b);
  
}

void loop() {
  
  Serial.print("Enter a mobile number: ");
  char sms[15];  // telephone number to send sms
  readSerial(sms);
 
 
  
  char checktxt[] = {'N','U','M'};
  char owner [12]= "";
  bool numstat = 0;
  Serial.println(sms);

  for (int i = 0; i <= 2; i++)
  {
    if (checktxt[i] == sms[i])
    {
      numstat = 1;
      Serial.println("bool 1");
    }
    if (checktxt[i] != sms[i])
    {
      numstat = 0;
      Serial.println("bool 0");
    }
  }
  if (numstat == 1)
  {
    int q = 4;
    for (int p = 0; p <= 12; p++)
    {
      owner[p] = sms[q];                                          
      q++;
    
    }
  }
Serial.println("NEW NUMBER");
      Serial.println(owner);


Serial.println ("Yes it calls " );
     if(millis() > time_now + period){
        time_now = millis();
        Serial.println("30 Secounds Timer");
     }
  
}

/*
  Read input serial
*/
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
