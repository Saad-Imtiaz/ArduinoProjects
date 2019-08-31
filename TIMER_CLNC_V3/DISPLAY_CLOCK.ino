
int timeoffset = 2;
int moffset = 30;
byte Hour ;
byte Minute;

//=========================== Displaying the Clock from the GPS ======================

void displayInfoLeft()
{
  lcd.setCursor(0, 0);
  { 
    
//================================== TIME ZONE OFFSET ================================
    Minute = gps.time.minute() - 30 ;
    Hour = gps.time.hour() - 2 ;
    // byte Second = gps.time.second();
if (Minute < 0)
 {
  Minute = Minute +60;
  Hour = Hour + 1;
 }
//================================ FIX FOR THE MINUTES ===============================


//============================ DISPLAYING CLOCK ON THE LCD ==========================

//======= HOUR =========

    if (gps.time.hour() < 10) lcd.print(F("0"));
    //lcd.print(gps.time.hour()- timeoffset);
   lcd.print(Hour);
    lcd.print(F(":"));
    
//======= MINUTES ======  
  
    if (gps.time.minute() < 10) lcd.print(F("0"));
  //  lcd.print(gps.time.minute()-moffset);
  lcd.print(Minute);
     

    
    
//======= SECOUNDS ===== 

    lcd.print(F(":"));
    if (gps.time.second() < 10) lcd.print(F("0"));
    lcd.print(gps.time.second());
  }
}
