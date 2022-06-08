#include "HX711.h"

#define driverPUL 7
#define driverDIR 6
int StepDelay = 500;
bool CW = HIGH;
bool CCW = LOW;

uint16_t step_angle = 1.8;


const int DOUT = 4;
const int CLK = 5;

HX711 scale;
float calibration_factor = 2230;
float units;
String payload = "";


void setup(){
  Serial.begin(115200);
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}


void moveStepper(uint16_t angle, bool direct){
  digitalWrite(driverDIR, direct);
  uint8_t counts = int(angle/step_angle);
  for(uint8_t i=0; i<counts; i++){
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(StepDelay);
    digitalWrite(driverPUL, LOW);
	delayMicroseconds(StepDelay);
  }
}

void MeasureWeight(){
  units = scale.get_units(), 5;
  if (units < 0)
    units = 0.00;
}

String waitingForData(){
  delay(1500);
  while(Serial.available() == 0){}
  if(Serial.available() > 0){
    String data = Serial.readStringUntil('\n');
    return data;
  }
}


void loop(){
  payload = waitingForData();
  if(payload == "start"){
    MeasureWeight();
    Serial.println("weight," + String(units));
    payload = waitingForData();
    if(payload == "weigth done"){
      moveStepper(45, CW);
      Serial.println("moved,1/4");
      payload = waitingForData();
      if(payload == "image 1"){
        moveStepper(45, CW);
        Serial.println("moved,2/4");
        payload = waitingForData();
        if(payload == "image 2"){
          moveStepper(45, CW);
          Serial.println("moved,3/4");
          payload = waitingForData();
          if(payload == "image 3"){
            moveStepper(45, CW);
            Serial.println("moved,4/4");
            payload = waitingForData();
            if(payload == "image 4"){
              Serial.println("complete");
            }
            else  Serial.println("failed");
          }
          else  Serial.println("failed");
        }
        else  Serial.println("failed");
      }
      else  Serial.println("failed");
    }
    else  Serial.println("failed");
  }
}
