
// GPS
//==================== Sélecteur d'UART

//===== Si carte MEGA
#if defined(__AVR_ATmega2560__)
#include <TinyGPS++.h>
String typeDeCarte = "[MEGA] ou [Arduino Mega or Mega 2560]";
#define SERIAL1 Serial1 // = prise [UART1]
#endif
//===== Fin MEGA


//==================== Pour toutes les cartes
#define SERIAL_GPS SERIAL1
TinyGPSPlus gps;

//===== Petite macro pour simplifier
#define TINYGPS_GET_DATA(serial,debug,listeningDuration)\
  uint16_t dataOk = 0;\
  unsigned long start = millis();\
  do\
  {\
    while (serial.available())\
      dataOk += gps.encode(serial.read());\
  } while (millis() - start < listeningDuration);
// Fin macro


String GPS() {
  TINYGPS_GET_DATA(Serial1, 0, 500);   // Serial(soft,hard), debug(0,1), timeOut(ms)

  String position1 = "";
  position1 += gps.location.lat();
  position1 += ";";
  position1 += gps.location.lng();
  return position1;
}
