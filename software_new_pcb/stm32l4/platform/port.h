#ifndef PORT_H
#define PORT_H

#include "main.h"

int32_t writetospi(uint16_t headerLength, const uint8_t *headerBuffer, uint16_t readlength, const uint8_t *readBuffer);
int32_t writetospiwithcrc(uint16_t headerLength, const uint8_t *headerBuffer, uint16_t bodyLength, const uint8_t *bodyBuffer, uint8_t crc8);

int32_t readfromspi(uint16_t headerLength, uint8_t *headerBuffer, uint16_t readLength, uint8_t *readBuffer);

void port_set_dw_ic_spi_slowrate(void);
void port_set_dw_ic_spi_fastrate(void);

void wakeup_device_with_io(void);

void deca_sleep(unsigned int time_ms);
void deca_usleep(unsigned long time_us);

#endif 
