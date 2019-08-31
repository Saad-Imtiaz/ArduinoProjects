void changeowner()
{ 

  bool numstat = 0;
Serial.println(smss);

  for (int i = 0; i <= 2; i++)
  {
    if (checktxt[i] == smss[i])
    {
      numstat = 1;
      Serial.println("bool 1");
    }
    if (checktxt[i] != smss[i])
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
      owner [p] = smss [q];                                          
      q++;
    
    }
  }
Serial.println("NEW OWNER IS :");
      Serial.println(owner);
//===========> Now Sending the Confimation SMS to the OWNWER
 sms.beginSMS(owner);       
 sms.print("You are the new owner of the Smart Mail Box");
 Serial.println("You are the new owner of the Smart Mail Box");
 sms.endSMS();
 sms.flush();     
}







  
