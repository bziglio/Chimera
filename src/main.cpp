#include <Arduino.h>

//Sensors and Modules Libraries
#include <HX711.h> //load cell lib

// microsseconds interval
unsigned long loadInterval = 12500;

/*
Frequency -- microsseconds
      1Hz -- 1000000
      4Hz -- 250000
     10Hz -- 100000
     80Hz -- 12500
   90,9Hz -- 11000
   95,2Hz -- 10500
    100Hz -- 10000
    105Hz -- 9520
    110Hz -- 9090
    120Hz -- 8300
*/

//last time
unsigned long timeLoad;

//pins
//Load Cell
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

//Static test sensors variables
float stLoad;

//raw variables
float rawLoad;

//variable init
HX711 scale;

//Declaração das funções
bool verifyInterval(unsigned long time, unsigned long interval);

int loadRoutine();


void setup() {
  Serial.print(115200);

  //Load cell start
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  //hx711 -- Loadout Cell
  if (verifyInterval(timeLoad, loadInterval)){
    loadRoutine();
  }
}

//checking if the execution interval is within the acceptable range
bool verifyInterval(unsigned long time, unsigned long interval){
  return micros() - time >= interval;
}

int loadRoutine(){
  if (scale.is_ready()) {

    rawLoad = scale.read();
    Serial.print(millis());
    Serial.print("   ");
    Serial.println(rawLoad);

  } else {
    //Serial.println("HX711 not found.");
    Serial.println("Error");
  }

  timeLoad = micros();

  return 0;
}