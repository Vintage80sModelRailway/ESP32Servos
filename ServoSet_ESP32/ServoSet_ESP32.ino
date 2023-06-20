#include <ESP32Servo.h>
#include "Sensor.h"
#define NumberOfSensors 6

Servo myServo;
int servoPin = 0; // address of servo to be calibrated
int pwmChannel = -1;
String readString;
int pos;
int numberOfSensors = 6;
Sensor Sensors[NumberOfSensors];

void setup() {
  Serial.begin(115200);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo.setPeriodHertz(50);    // standard 50 hz servo
  pos = 1500;
  initSensors();

  Serial.println("Set pin with 0p where 0 is pin number");
  //Serial.println("Set PWM channel with 0w where 0 is PWM channel");
  Serial.println("Set PWM value with 0x where 0 is PWM microseconds");
  delay(10);
}

void loop()
{
  while (Serial.available()) {
    char c = Serial.read();
    readString += c;
    delay(2);
  }
  if (readString.length() > 0) {
    //Handle pin set
    if (readString.indexOf('p') > 0) {
      if (myServo.attached()) myServo.detach();
      //servoPin = readString.substring(readString.indexOf('p')).toInt();
      servoPin = readString.toInt();
      //pwmChannel = myServo.attach(servoPin);
      Serial.println("Servo pin changed to " + String(servoPin) + " on channel " + String(pwmChannel));
    }
    if (readString.indexOf('x') > 0)
    {
      int pwmVal = readString.toInt();
      if (!myServo.attached()) pwmChannel = myServo.attach(servoPin);
      myServo.writeMicroseconds(pwmVal);
      delay(200);
      if (myServo.attached()) myServo.detach();
      Serial.println("Servo PWM value set to " + String(pwmVal) + " for pin " + String(servoPin) + " on channel " + String(pwmChannel));
    }
    readString = "";
  }

  CheckSensors();
}

void CheckSensors() {
  for (int i = 0;i<numberOfSensors;i++) {
    if (Sensors[i].UpdateSensor()) {
      Serial.println("Sensor on pin "+String(Sensors[i].pin)+" has changed to "+String(Sensors[i].lastKnownValue));
    }
  }
  
}

void initSensors() {
  Sensors[0] = Sensor(15, INPUT_PULLUP);
  Sensors[1] = Sensor(17, INPUT_PULLUP);
  Sensors[2] = Sensor(5, INPUT_PULLUP);
  Sensors[3] = Sensor(16, INPUT_PULLUP);
  Sensors[4] = Sensor(12, INPUT_PULLUP);
  Sensors[5] = Sensor(14, INPUT_PULLUP);

  for (int i = 0;i<numberOfSensors;i++) {
    Sensors[i].SetPinMode();
  }
}
