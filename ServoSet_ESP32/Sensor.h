// Sensor.h
#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

class Sensor {
  private:
     
    uint8_t _pinMode;

  public:     
    Sensor(int InputPin = -1, uint8_t PinMode = INPUT, int LastKnownValue = -1);  
    bool UpdateSensor();
    void SetPinMode();
    int lastKnownValue;
    int pin;   
};


#endif
