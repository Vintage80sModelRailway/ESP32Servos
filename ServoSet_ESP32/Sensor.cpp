#include "Sensor.h"

Sensor::Sensor(int InputPin, uint8_t PinMode, int LastKnownValue)
: pin(InputPin)
, _pinMode(PinMode)
, lastKnownValue(LastKnownValue)
{
  
}

bool Sensor::UpdateSensor() {
  int val = digitalRead(pin);
  //if (pin == 14) Serial.println(String(val));
  if (val == lastKnownValue) return false;
  //Serial.println("Pin "+String(pin)+" val "+String(val));
   lastKnownValue = val;
   return true;  
}

void Sensor::SetPinMode() {
  pinMode(pin,_pinMode);
}
