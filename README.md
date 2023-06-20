# ESP32Servos
A sketch for ESP32s on the Arduino IDE to configure and test servos connected over PWM.

Uses detach to switch servos off after moving them - not necessary for this sketch but something I'm intending to incorporate into my main control sketches to reduce chattering and buzzing.

Also contains basic support for microswitch / sensor monitoring. 

Set constant numberOfSensors at the top, this will be used to create an array of sensors.

Instantiate sensors at the bottom

Sensors[0] = Sensor(xx, INPUT_PULLUP);

where xx = the pin that the microswitch is connected to.
