

//======================== Displaying the entered time on the LCD for the timer =======================

void showEnteredTime()
{
  lcd.setCursor(11, 1);
  lcd.print(currentTimeValue[0]);
  lcd.print(currentTimeValue[1]);
  lcd.print(":");
  lcd.print(currentTimeValue[2]);
  lcd.print(currentTimeValue[3]);
}




//============================ Display the Countdown Timer on the LCD ==================================

void showCountdown()
{
  char timest[6]; \
  displayInfoLeft();
  lcd.setCursor(0, 1);
  lcd.print("~");
  sprintf(timest, "%d:%.2d", (timerSeconds / 60), (timerSeconds - ((timerSeconds / 60) * 60)));
  lcd.print(timest);
  lcd.print("   ");
  lcd.setCursor(7, 1);
  lcd.print("Timer Set");

}




//====================================== UI for the Timer ==============================================

void displayCodeEntryScreen()
{
  clearScreen();

  lcd.setCursor(0, 0);
  {
    lcd.setCursor(10, 0);
    lcd.print("|mm:ss:");
    lcd.setCursor(10, 1);
    lcd.print("|00:00");
    lcd.setCursor(0, 1);
    lcd.print("Set Timer |");
  }
}



//================================= Clearing the screen between intervals ==============================

void clearScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
