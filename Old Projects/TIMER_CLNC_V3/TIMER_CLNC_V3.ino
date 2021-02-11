
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


char currentTimeValue[4];
int currentState = 1;
int timerSeconds = 0;
int lpcnt = 0;

//=========================SPEAKER SETUP=========================================

#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
#define  R     0
#define  r1     0
#define  c1     1898    // 261 Hz 
#define  d1     1690    // 294 Hz 
#define  e1     1500    // 329 Hz 
#define  f1     1420    // 349 Hz 
#define  g1     1265    // 392 Hz 
#define  x1     1194    // 440 Hz 
#define  a1     1126    // 493 Hz 
#define  z1     1063    // 523 Hz 
#define  b1     1001
#define  C1     947    // 493 Hz 
#define  y1     893    // 523 Hz 
#define  D1     843
#define  w1     795    // 493 Hz 
#define  E1     749    // 523 Hz 
#define  F1     710
#define  q1     668    // 493 Hz 
#define  G1     630    // 523 Hz 
#define  i1     594

// ===============Set up speaker on a PWM pin (digital 9, 10 or 11)=============
int speakerOut = 11;
// Do we want debugging on serial out? 1 for yes, 0 for no
int DEBUG = 1;


// ====================== MELODY and TIMING  ===================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)

int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.


//======================= Set overall tempo ====================================
long tempo = 10000;


//===================== Set length of pause between notes ======================
int pause = 500;


//===================== Loop variable to increase Rest length===================
//[BLETCHEROUS HACK; See NOTES]
int rest_count = 100;


//===================== Initialize core variables ==============================
int tone_ = 0;
int beat = 0;
long duration  = 0;


//====================== Melody for the Tone ===================================
int Zmelody[] = {b1, y1, w1, F1, C1, D1, E1, q1, y1, w1, F1, G1, D1, E1, q1, i1, r1, r1, a1, z1, b1, C1};
int Zbeats[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 6};
int ZMAX_COUNT = sizeof(Zmelody) / 2;


//========================== GPS Stuff =========================================
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
unsigned long last = 0UL;


//================= Defining the buttons for the keypad ========================
const byte rows = 4;
const byte cols = 4;


//======================== Initializing the LCD ================================
#define I2C_ADDR          0x27        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C lcd(0x27, 16, 2);


//===================Setting up ROWS ADN COLS for the KEYPAD====================
char keys[rows][cols] = {

  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
byte rowPins[rows] = {5, 6, 7, 8};
byte colPins[cols] = {9, 10, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);



//====================================================================================================
//====================================================================================================
//================================ MAIN SETUP RUNS OUNCE OFCOURSE ====================================
//====================================================================================================
//====================================================================================================

void setup()
{
 
 //============================= GPS Start Pin ==============================
  digitalWrite(4, HIGH); 

  lcd.begin(16, 2);
  pinMode(speakerOut, OUTPUT);//sound part
  pinMode (4, OUTPUT);//GPS HIGH = ON GPS LOW = OFF
  //lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);

//============================== WELCOME MESSAGE ==============================
  lcd.setBacklight(HIGH);
  lcd.print("I LOVE MY");
  lcd.setCursor(5, 1);
  lcd.print("HALEY BIRD!");

  
//=========== Set up a counter to pull from melody[] and beats[] =============
{
    for (int i = 0; i < MAX_COUNT; i++)
    {
      tone_ = melody[i];
      beat = beats[i];

      duration = beat * tempo; // Set up timing

      playTone();
      // A pause between notes...
      delayMicroseconds(pause);
    }

  }
  digitalWrite(speakerOut, LOW);


  //======== Setting up initial screen display for timer to 00:00 ============

  currentTimeValue[0] = '0';
  currentTimeValue[1] = '0';
  currentTimeValue[2] = '0';
  currentTimeValue[3] = '0';
  showEnteredTime();
  ss.begin(GPSBaud);
  displayCodeEntryScreen();

}




//====================================================================================================
//====================================================================================================
//================================ MAIN LOOP RUNS ALL THE TIME =======================================
//====================================================================================================
//====================================================================================================

void loop()
{

  
//============================= GPS Start Pin ==============================
  digitalWrite(4, HIGH); 


//=== Conditon for the GPS if the GPS is connected and availibe the time will show only then ====
 
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      displayInfoLeft();
    }

//====================================================================================================
//=================================== MIAN TIMER CODE ================================================
//====================================================================================================
  int l;
  char tempVal[3];
  char key = keypad.getKey();

  //key pressed and state is 1
  if (int(key) != 0 and currentState == 1) {

    switch (key) {
      case '*':
        relayStatus(false);
        currentTimeValue[0] = '0';
        currentTimeValue[1] = '0';
        currentTimeValue[2] = '0';
        currentTimeValue[3] = '0';
        showEnteredTime();
        currentState = 1;

        lpcnt = 0;
        timerSeconds = 0;
        break;

      case '#':
        tempVal[0] = currentTimeValue[0];
        tempVal[1] = currentTimeValue[1];
        tempVal[2] = 0;

        timerSeconds = atol(tempVal) * 60;

        tempVal[0] = currentTimeValue[2];
        tempVal[1] = currentTimeValue[3];
        tempVal[2] = 0;

        timerSeconds = timerSeconds + atol(tempVal);
        currentState = 2;
        break;

      default:
        currentTimeValue[0] = currentTimeValue[1];
        currentTimeValue[1] = currentTimeValue[2];
        currentTimeValue[2] = currentTimeValue[3];
        currentTimeValue[3] = key;
        showEnteredTime();
        break;
    }
  }

  if (currentState == 2) {
    if (int(key) != 0) {
      if (key == '*') {
        relayStatus(true);
        clearScreen();
        displayCodeEntryScreen();
        currentTimeValue[0] = '0';
        currentTimeValue[1] = '0';
        currentTimeValue[2] = '0';
        currentTimeValue[3] = '0';
        showEnteredTime();
        currentState = 1;
        lpcnt = 0;
        timerSeconds = 0;

      }
    } else {

      if (lpcnt > 9) {
        lpcnt = 0;
        --timerSeconds;
        showCountdown();

        if (timerSeconds <= 0) {
          lcd.setCursor(0, 0);
          lcd.print("Times Up!");
          currentState = 1;
          relayStatus(false);
          delay(2000);
          displayCodeEntryScreen();
          showEnteredTime();
        } else {
          relayStatus(true);
        }
      }

      ++lpcnt;
      delay(100);
    }
  }
}
