/* Copyright (c) Intel. All rights reserved.
Licensed under the MIT license. See LICENSE file in the project root for full license information.
*/

/*
  Grove Temperature and Humidity sensor
  Example using the Grove Temperature and Humidity sensor UPM library. Takes a temperature and humidity reading every three seconds, before displaying them via serial communication.
  https://github.com/intel-iot-devkit/up-squared-grove-IoT-dev-kit-arduino-create/tree/master/examples/GroveTemperatureAndHumidity
*/

// upm - Version: Latest

#include <th02.hpp>
#include "upm_utilities.h"


//Prototype function
float ModTemp(char, float);

void setup() {
  //Begin serial terminal
  //If you are using the UP^2 board via serial port (COM, tty, etc) exchange the DebugSerial method with Serial in all instances
  DebugSerial.begin(9600);
  
}

void loop() {
  //Create sensor
  upm::TH02 sensor;
  
  //Create variables to hold the temperature and humidity
  float temperature = 0.0;
  float humidity = 0.0;
  
  //Create buffer
  char buff[10];
  
  //Create variable to hold the temperature modifier
  char tempModifier = 'F'; //Modifier allows conversion to Fahrenheit or Kelvin, Base is Celsius
  
  //Create a string to hold our message
  String outputMessage = "";
  
  //Get temperature
  temperature = sensor.getTemperature();
  
  //Get humidity
  humidity = sensor.getHumidity();
  //Perform math to change temperature unit
  temperature = ModTemp(tempModifier, temperature);
  
  //Build output message for temperature
  outputMessage += (String(temperature) + " degrees " + tempModifier + "\n");
  //Build output message for humidity
  outputMessage += (String(humidity) + " percent relative humidity\n");
  //Build shiny break bar
  outputMessage += "---------------------------------------\n\n";
  
  //Print information
  DebugSerial.println(outputMessage);

  //Sleep 3 seconds between readings
  delay(3000);
}

float ModTemp(char modifier, float modifiedTemp){
  if (modifier == 'F'){ //Perform math to change Celsius to Fahrenheit
    modifiedTemp = ((modifiedTemp * 1.8) + 32);
  }
  else if (modifier == 'K'){ //Perform math to change Celsius to Kelvin
    modifiedTemp += 273.15;
  }
  return modifiedTemp;
}