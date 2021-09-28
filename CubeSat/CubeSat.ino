#include <ParticleSensor.h>
#include <Arduino.h>
class CubeSat{
  
}


ParticleSensor particleSensor;


/*30s*/
void setup() {
Serial.begin(115200);
Serial.println("test");
if (particleSensor.startSensor()) {
        Serial.println("HM330X init failed!!!");
        while (1);
    }
particleSensor.setSerial(&Serial);
}

void loop() {
 particleSensor.read_and_print_result();
//Serial.println("test");
}
