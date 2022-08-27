
int carteSD() {

  /*Serial.print("currentMillis:");
    Serial.println(currentMillis);
    Serial.print("previousMillisSD:");
    Serial.println(previousMillisSD);
    Serial.print("BLINK_INTERVAL_Enreg:");
    Serial.println(BLINK_INTERVAL_Enreg);
    Serial.println("");*/

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    //Serial.println(RTC());

    Serial.println("ENREGISTREMENT SUR SD DE : ");
    dataFile.println(donnee());
    dataFile.close();

    //Serial.println(dataString);

  }
  else {
    Serial.println("IMPOSSIBLE DE CREER LE FICHIER");
  }
  //delay(2000);
}



int supprimeSD() {
  SD.begin(broche_CS);
  static unsigned long previousMillisSup = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSup >= BLINK_INTERVAL_Supp) {        // Si BLINK_INTERVAL_2 ou plus millisecondes se sont écoulés
    previousMillisSup = currentMillis;
    if (SD.exists("datalog.txt")) {
      SD.remove("datalog.txt");
      Serial.println("Suppression des données");
    }
    //delay(20000);
  }
}
