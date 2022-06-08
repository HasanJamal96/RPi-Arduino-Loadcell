#include "HX711.h"
#define DOUT  4
#define CLK  5

HX711 scale(DOUT, CLK);
float calibration_factor = 2230;
float units;

void setup(){
  Serial.begin(115200);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  Serial.println("Press t or T to apply calibration factor");
  Serial.println("When measured weight is same as known weigth note down the calibration factor");
  scale.set_scale(calibration_factor);
  scale.tare();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
}


void loop(){
  Serial.print("Reading");
  units = scale.get_units(), 5;
  if (units < 0)
   units = 0.00;
  Serial.print("Weight: ");
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  if(Serial.available()){
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  if(Serial.available()){
    char temp = Serial.read();
    if(temp == 't' || temp == 'T')
      scale.tare();
  }
}
