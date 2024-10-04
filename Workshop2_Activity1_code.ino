#include "Arduino_BHY2.h"
Sensor temp(SENSOR_ID_TEMP);
Sensor pressure(SENSOR_ID_BARO);
Sensor gas(SENSOR_ID_GAS);

void setup() { 
  Serial.begin(115200);
  BHY2.begin();
  temp.begin();
  pressure.begin();
  gas.begin();
}

void loop() {
  // If prompted, collect some data
  if (Serial.available()) {
    // Read the string from the computer to find number of readings to take
    String numberofReadingsString = Serial.readStringUntil('\n');
    int numberofReadings = numberofReadingsString.toInt();

    // Make a note of the time at which data taking starts
    unsigned long startTime = millis();
    float dataT = 0;      // Initialise the time stamp variable

    for (int n = 0; n < numberofReadings; n++) {  
      BHY2.update();    // Update the sensor readings 

      // Collect the data
      dataT = millis() - startTime;
      float dataTemp = temp.value();
      float dataP = pressure.value();
      float dataG = gas.value();

      // Write the data to the serial port
      Serial.print(dataT);
      Serial.print(',');
      Serial.print(dataTemp);
      Serial.print(',');
      Serial.print(dataP);
      Serial.print(',');
      Serial.print(dataG);
      Serial.print('\n');
    } // ends for loop()
  } // ends if(Serial.available()) 
} // end loop()

