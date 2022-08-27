
int LCD() {
  etatBouton = digitalRead(bouton11);                              // Rappel : bouton = 11
  if (etatBouton == HIGH)                                          // test si le bouton a un niveau logique HAUT
  {
    //lcd.noDisplay();   //eteind le cristaux liquide
    //lcd.noBacklight();
    //lcd.noBacklight();
    lcd.clear();
    lcd.setRGB(0, 255, 255);
    lcd.setCursor(0, 0);
    lcd.print(RTCdate());
    lcd.setCursor(0, 1);
    lcd.print(RTCheure());
    delay(3000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp());
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("PA: ");
    lcd.print(pressure());
    lcd.print(" hPa");
    delay(3000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(humidity());
    lcd.print(" %");
    lcd.setCursor(0, 1);
    lcd.print("Lum: ");
    lcd.print(lum());
    lcd.print(" Lux");
    delay(3000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Tension: ");
    lcd.print(tension());
    lcd.print(" V");
    delay(3000);
    
    lcd.setRGB(0, 0, 0);
    lcd.clear();
  }
  /*   else  // test si le bouton a un niveau logique différent de HAUT (donc BAS)
     {
       Serial.println("Bouton relaché");
     }*/
}
