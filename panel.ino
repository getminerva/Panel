/*
 * Panel
 *
 * Written by Joshua Paul A. Chan
 *
 */

#include <CapacitiveSensor.h>

#define ledPin 3

const int maxLvl = 255;
const int minLvl = 0;
int curLvl = minLvl;


const int threshold = 150;

CapacitiveSensor sensorUno = CapacitiveSensor(4, 2); // 10M R on emitter pin 4, 1k R on rcvr pin 2
CapacitiveSensor sensorDos = CapacitiveSensor(4, 6); // 10M R on emitter pin 4, 1k R on rcvr pin 6
CapacitiveSensor sensorTres = CapacitiveSensor(4, 8); // 10M R on emitter pin 4, 1k R on rcvr pin 8

void setLevel(int lvl) {
    curLvl = lvl;
    if (minLvl > curLvl) {
        curLvl = minLvl;
    }
    else if (maxLvl < curLvl) {
        curLvl = maxLvl;
    }
}

int getLevel() {
    return curLvl;
}

void brighten(int thisMuch) {
    setLevel(getLevel() + thisMuch);
}

void dim(int thisMuch) {
    brighten(-1*thisMuch);
}

void toggle() {
    if (minLvl < curLvl) {
        curLvl = minLvl;
    }
    else {
        curLvl = maxLvl;
    }
}

void setup() {
  // Set pin outs
  pinMode(ledPin, OUTPUT);
  // Establish connections
  // Start serial
  Serial.begin(9600);
}

void loop() {
  long start = millis();
  long total1 = sensorUno.capacitiveSensor(30); // Sensor 1
  long total2 = sensorDos.capacitiveSensor(30); // Sensor 2
  long total3 = sensorTres.capacitiveSensor(30); // Sensor 3

  if (threshold < total2) {
      toggle();
      delay(100);
  }
  if (threshold < total3) {
      brighten(1);
  }
  else if (threshold < total1) {
      dim(1);
  }

  analogWrite(ledPin, curLvl);  // Energize LED
  delay(30);

  Serial.print(millis() - start);
  Serial.print(":\t");

  Serial.print(total1);         //  (-) Print sensor value and space it nicely
  Serial.print("\t");           //
  Serial.print(total2);	        //	(|)
  Serial.print("\t");			//
  Serial.print(total3);         //	(+)
  Serial.print("\t");
  Serial.println(getLevel());

  delay(10);


}
