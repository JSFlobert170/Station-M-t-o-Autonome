#include <Wire.h>

long lastSecond;
byte seconds;
byte minutes;

long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
byte windspdavg[120];

volatile float rainHour[60];
int directionvent = 0;
float vitessevent = 0;
float Pluie = 0;
volatile float dailyrainin = 0;

volatile unsigned long raintime, rainlast, raininterval, rain;

void rainIRQ()
{
  attachInterrupt(0, rainIRQ, FALLING);
  interrupts();
  raintime = millis(); 
  raininterval = raintime - rainlast;

  if (raininterval > 10)
  {
    dailyrainin += 0.28;
    rainHour[minutes] += 0.28;
    rainlast = raintime;
  }
}

void wspeedIRQ()
{
  if (millis() - lastWindIRQ > 10)
  {
    lastWindIRQ = millis();
    windClicks++;
  }
}

const byte WDIR = A0;

float get_wind_speed()
{
  attachInterrupt(1, wspeedIRQ, FALLING);
  interrupts();
  float deltaTime = millis() - lastWindCheck;

  deltaTime /= 1000.0; //Covert to seconds

  float windSpeed = (float)windClicks / deltaTime;

  windClicks = 0;
  lastWindCheck = millis();

  windSpeed *= 2.48;


  return (windSpeed);
}

int get_wind_direction()
{
  unsigned int adc;

  adc = analogRead(WDIR);

  if (adc < 380) return (113);
  if (adc < 393) return (68);
  if (adc < 414) return (90);
  if (adc < 456) return (158);
  if (adc < 508) return (135);
  if (adc < 551) return (203);
  if (adc < 615) return (180);
  if (adc < 680) return (23);
  if (adc < 746) return (45);
  if (adc < 801) return (248);
  if (adc < 833) return (225);
  if (adc < 878) return (338);
  if (adc < 913) return (0);
  if (adc < 940) return (293);
  if (adc < 967) return (315);
  if (adc < 990) return (270);
  return (-1); // error, disconnected?
}

float calcWeather()
{
  //Calc winddir
  directionvent = get_wind_direction();


  Pluie = 0;
  for (int i = 0 ; i < 60 ; i++)
    Pluie += rainHour[i];
  return (Pluie);
}

String printWeather()
{
  String dir="";
  calcWeather();
  if (directionvent >= 22 && directionvent >= 338) {
    dir = "N";
  }
  if (directionvent >= 158 && directionvent <= 202) {
    dir = "S";
  }
  if (directionvent >= 68 && directionvent <= 112) {
    dir = "E";
  }
  if (directionvent >= 248 && directionvent <= 292) {
    dir = "O";
  }
  if (directionvent >= 23 && directionvent <= 67) {
    dir = "NE";
  }
  if (directionvent >= 293 & directionvent <= 337) {
    dir = "NO";
  }

  if (directionvent >= 114 && directionvent <= 157) {
    dir = "SE";
  }

  if (directionvent >= 203 && directionvent <= 247) {
    dir = "SO";
  }
  return (dir);
}
