#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "deca_device_api.h"
#include "port.h"
#define TX_DELAY_MS 500
#define FRAME_LEN_MAX 127

void waitforsysstatus(uint32_t *lo_result, uint32_t *hi_result, uint32_t lo_mask, uint32_t hi_mask);
void send_msg_polling(uint8_t *msg);
void recieve_msg_polling(uint8_t *msg);

#endif
