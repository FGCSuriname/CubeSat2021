#include "Arduino.h"
#include "ParticleSensor.h"
#include <Seeed_HM330X.h>

class ParticleSensor{

private:
  Stream *SERIAL_OUTPUT ;
  HM330X sensor;
  uint8_t buf[30];
  const char* str[13] = {"sensor num: ", 
                      "PM1.0 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM2.5 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM10 concentration(CF=1,Standard particulate matter,unit:ug/m3): ",
                      "PM1.0 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM2.5 concentration(Atmospheric environment,unit:ug/m3): ",
                      "PM10 concentration(Atmospheric environment,unit:ug/m3): ",
                      };
public:
  ParticleSensor(){}
  
  HM330XErrorCode ParticleSensor::print_result(const char* str, uint16_t value) {
      if (NULL == str) {
          return ERROR_PARAM;
      }
      SERIAL_OUTPUT->print(str);
      SERIAL_OUTPUT->println(value);
      return NO_ERROR;
  }

  /*parse buf with 29 uint8_t-data*/
  HM330XErrorCode ParticleSensor::parse_result(uint8_t* data) {
      uint16_t value = 0;
      if (NULL == data) {
          return ERROR_PARAM;
      }
      for (int i = 1; i < 8; i++) {
          value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
          print_result(str[i - 1], value);

      }

      return NO_ERROR;
  }

  // Parse and print result value as hex
  HM330XErrorCode ParticleSensor::parse_result_value(uint8_t* data) {
      if (NULL == data) {
          return ERROR_PARAM;
      }
      for (int i = 0; i < 28; i++) {
          SERIAL_OUTPUT->print(data[i], HEX);
          SERIAL_OUTPUT->print("  ");
          if ((0 == (i) % 5) || (0 == i)) {
              SERIAL_OUTPUT->println("");
          }
      }
      uint8_t sum = 0;
      for (int i = 0; i < 28; i++) {
          sum += data[i];
      }
      if (sum != data[28]) {
          SERIAL_OUTPUT->println("wrong checkSum!!!!");
      }
      SERIAL_OUTPUT->println("");
      return NO_ERROR;
  }

  void ParticleSensor::read_and_print_result(){
          if (sensor.read_sensor_value(buf, 29)) {
          SERIAL_OUTPUT->println("HM330X read result failed!!!");
      }
      parse_result_value(buf);
      parse_result(buf);
      SERIAL_OUTPUT->println("");
    }
    void setSerial(Stream *streamObject)
    {
      SERIAL_OUTPUT=streamObject;
    }
    bool startSensor(){
      return (sensor.init()==true);
    }
    
};
