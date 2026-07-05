#include "communication.h"
#include "deca_device_api.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void waitforsysstatus(uint32_t *lo_result, uint32_t *hi_result, uint32_t lo_mask, uint32_t hi_mask)
{
    uint32_t lo_result_tmp = 0;
    uint32_t hi_result_tmp = 0;

    if (lo_mask)
    {
        while (!((lo_result_tmp = dwt_readsysstatuslo()) & (lo_mask)))
        {
            if (hi_mask)
            {
                if ((hi_result_tmp = dwt_readsysstatushi()) & hi_mask)
                {
                    break;
                }
            }
        }
    }
    else if (hi_mask)
    {
        while (!((hi_result_tmp = dwt_readsysstatushi()) & (hi_mask)))
        {
        };
    }

    if (lo_result != NULL)
    {
        *lo_result = lo_result_tmp;
    }

    if (hi_result != NULL)
    {
        *hi_result = hi_result_tmp;
    }
}

void send_msg_polling(uint8_t *msg)
{
    int frame_length = sizeof(msg) + FCS_LEN;
    dwt_writetxdata(frame_length - FCS_LEN, msg, 0);
    dwt_writetxfctrl(frame_length, 0, 0);
    dwt_starttx(DWT_START_TX_IMMEDIATE);
    waitforsysstatus(NULL, NULL, DWT_INT_TXFRS_BIT_MASK, 0);
    dwt_writesysstatuslo(DWT_INT_TXFRS_BIT_MASK);

    deca_sleep(TX_DELAY_MS);
}

void recieve_msg_polling(uint8_t *msg)
{
    bool done = false;
    uint32_t status_reg;
    uint16_t frame_len;

    while (!done)
    {
        memset(&msg, 0, sizeof(msg));
        dwt_rxenable(DWT_START_RX_IMMEDIATE);

        waitforsysstatus(&status_reg, NULL, (DWT_INT_RXFCG_BIT_MASK | SYS_STATUS_ALL_RX_ERR), 0);

        if (status_reg & DWT_INT_RXFCG_BIT_MASK)
        {
            frame_len = dwt_getframelength(0);
            if (frame_len <= FRAME_LEN_MAX)
            {
                dwt_readrxdata(msg, frame_len - FCS_LEN, 0);
            }

            dwt_writesysstatuslo(DWT_INT_RXFCG_BIT_MASK);

            done = true;
        }
        else
        {
            dwt_writesysstatuslo(SYS_STATUS_ALL_RX_ERR);
        }
    }
    return;
}
