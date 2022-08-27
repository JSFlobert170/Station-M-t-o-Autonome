const byte liretension = A9;

/* Coefficient diviseur du pont de résistance */
const float COEFF_PONT_DIVISEUR_VIN = 1.0731707317;


/** Mesure la référence interne à 1.1 volts */
unsigned int analogReadReference(void) {
  
  /* Elimine toutes charges résiduelles */
#if defined(__AVR_ATmega2560__)
  ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5F;
#endif
  delayMicroseconds(5);
  
  /* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
#if defined(__AVR_ATmega2560__)
  ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5E;
#endif
  delayMicroseconds(200);

  /* Active le convertisseur analogique -> numérique */
  ADCSRA |= (1 << ADEN);
  
  /* Lance une conversion analogique -> numérique */
  ADCSRA |= (1 << ADSC);
  
  /* Attend la fin de la conversion */
  while(ADCSRA & (1 << ADSC));
  
  /* Récupère le résultat de la conversion */
  return ADCL | (ADCH << 8);
}

/* Fonction loop() */
float tension() {
  
  /* Mesure la tension en VIN et la référence interne à 1.1 volts */
  unsigned int raw_vin = analogRead(liretension);
   //  float raw_vin = 8;

  unsigned int raw_ref = analogReadReference();
  
  /* Calcul de la tension réel avec un produit en croix */
  float real_vin = ((raw_vin * 0.3) / raw_ref) * COEFF_PONT_DIVISEUR_VIN;
 // float real_vin = (raw_vin*600)/300;

  
 
  /* Affichage */
// Serial.println(real_vin, 3);

  float tensionLue = map(raw_vin, 0, 1023, 0, 500);
  float tension = (tensionLue / 100.0) * COEFF_PONT_DIVISEUR_VIN +0.80;

  //  Serial.println(tension);

  //delay(1000);
  //tension=8.4;
  return tension;
}
