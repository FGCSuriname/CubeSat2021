/*
  ParticleSensor.h - Library for using the Seeed_HM330X particle sensor within the cubesat project.
  Created by Team Suriname, September 28, 2021.
  Released into the public domain.
*/
#include <Seeed_HM330X.h>

#ifndef ParticleSensor_h
#define ParticleSensor_h

class ParticleSensor
{
private:
  Stream *SERIAL_OUTPUT;
  HM330X sensor;
  uint8_t buf[30];
  const char *str[13];
public:
  ParticleSensor() {}

  HM330XErrorCode print_result(const char *str, uint16_t value);

  /*parse buf with 29 uint8_t-data*/
  HM330XErrorCode parse_result(uint8_t *data);
  

  // Parse and print result value as hex
  HM330XErrorCode parse_result_value(uint8_t *data);

  void read_and_print_result();

  bool startSensor();
};

#endif
