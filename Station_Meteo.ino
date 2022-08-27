#include <Wire.h>
#include "SparkFunMPL3115A2.h"
#include "SparkFun_Si7021_Breakout_Library.h"

MPL3115A2 myPressure;

int light = A1;
int power = A3;
int GND = A2;
Weather sensor;

#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};

// PROGRAMME DE TEST SD
#include <SPI.h>
#include <SD.h>
int broche_CS = 9;

#include <LiquidCrystal_I2C.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int bouton11 = 11;
int etatBouton;

void setup() {

  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(115200);
  Wire.begin();
  ////////////////////////////////////////////////////////////
  pinMode(power, OUTPUT);
  pinMode(GND, OUTPUT);
  pinMode(light, INPUT);

  digitalWrite(power, HIGH);
  digitalWrite(GND, LOW);
  sensor.begin();
  /////////////////////////////////////////////////////////////
  SD.begin(broche_CS);
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 0);

  pinMode(bouton11, INPUT);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  DateTime((__DATE__), (__TIME__));
  //DateTime(2021, 06, 8, 10, 44, 0);
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    DateTime(F(__DATE__), F(__TIME__));       //rtc.adjust(DateTime(2021, 03, 25, 9, 40, 0));
  }/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("Date, Heure, Temperature, Luminosite, Pression, Humidite, vitesse du vent, Latitude, Longitude, Direction du vent, Pluie, tension ");
  carteSD();
  Serial2.println(donnee());
  Serial.println(donnee());
}
//3600000
const unsigned long BLINK_INTERVAL_Enreg = 10000;
const unsigned long BLINK_INTERVAL_Supp = 50000;

static unsigned long previousMillisSD = 0;

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSD >= BLINK_INTERVAL_Enreg) {        // Si BLINK_INTERVAL_2 ou plus millisecondes se sont écoulés
    previousMillisSD = currentMillis;                                    // Garde en mémoire la valeur actuelle de millis()
    carteSD();
    Serial.println(donnee());
  }
  Serial2.println(donnee());
  

  LCD();
  supprimeSD();
}
