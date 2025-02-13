#ifndef SENSOR_H
#define SENSOR_H

#include <LPC17xx.h>
#include <stdint.h>

void sensor_init(void);
uint8_t is_vehicle_detected(void);

#endif // SENSOR_H
