void sensors(){

// read the analog in value:
  PHsensorValue = analogRead(PHanalogInPin);
  lightsensorValue = analogRead(lightanalogInPin);
  watersensorValue = analogRead(wateranalogInPin);
  // map it to the range of the analog out:
  // outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  // analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.println("PH sensor = " + String(PHsensorValue));
  Serial.println("Light sensor = " + String(lightsensorValue));
  Serial.println("watersensorValue = " + String(watersensorValue));
  delay (2000);

  // Serial.print("\t output = ");
  // Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:



  
}
