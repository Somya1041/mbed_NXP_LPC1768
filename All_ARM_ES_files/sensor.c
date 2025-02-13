#include "sensor.h"

void sensor_init(void) {
    LPC_GPIO2->FIODIR &= ~(1 << 10); // Set P2.10 as input (sensor pin)
}

uint8_t is_vehicle_detected(void) {
    return !(LPC_GPIO2->FIOPIN & (1 << 10)); // Active low sensor
}
