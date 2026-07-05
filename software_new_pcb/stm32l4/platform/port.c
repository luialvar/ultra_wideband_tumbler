#include "deca_device_api.h"
#include "deca_interface.h"
#include "main.h"
#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"

#define CS_LOW() HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET)

int32_t writetospi(uint16_t headerLength, const uint8_t *headerBuffer, uint16_t readlength, const uint8_t *readBuffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();
    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
        ;

    CS_LOW();

    if (HAL_SPI_Transmit(&hspi1, (uint8_t *)headerBuffer, headerLength, HAL_MAX_DELAY) != HAL_OK)
    {
        CS_HIGH();
        return 0;
    }

    if (readlength > 0)
    {
        if (HAL_SPI_Transmit(&hspi1, (uint8_t *)readBuffer, readlength, HAL_MAX_DELAY) != HAL_OK)
        {
            CS_HIGH();
            return 0;
        }
    }

    CS_HIGH();
    decamutexoff(stat);
    return 0;
}

int32_t writetospiwithcrc(uint16_t headerLength, const uint8_t *headerBuffer, uint16_t bodyLength,
                          const uint8_t *bodyBuffer, uint8_t crc8)
{
    /*
      For now we can probably leave this as blank
     */
    return 0;
}

int32_t readfromspi(uint16_t headerLength, const uint8_t *headerBuffer, uint16_t readLength, uint8_t *readBuffer)
{
    decaIrqStatus_t stat;
    stat = decamutexon();
    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
        ;

    CS_LOW();

    if (HAL_SPI_Transmit(&hspi1, (uint8_t *)headerBuffer, headerLength, HAL_MAX_DELAY) != HAL_OK)
    {
        CS_HIGH();
        return 0;
    }

    while (readLength-- > 0)
    {
        /* Wait until TXE flag is set to send data */
        while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET)
        {
        }

        hspi1.Instance->DR = 0;

        while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET)
        {
        }

        (*readBuffer++) = hspi1.Instance->DR;
    }

    CS_HIGH();
    decamutexoff(stat);
    return 0;
}

void port_set_dw_ic_spi_slowrate(void)
{
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    HAL_SPI_Init(&hspi1);
}

void port_set_dw_ic_spi_fastrate(void)
{
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    HAL_SPI_Init(&hspi1);
}

void wakeup_device_with_io(void)
{
    HAL_GPIO_WritePin(WAKEUP_GPIO_Port, WAKEUP_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(WAKEUP_GPIO_Port, WAKEUP_Pin, GPIO_PIN_RESET);
    HAL_Delay(2);
}

/**
 * @brief  Checks whether the specified IRQn line is enabled or not.
 * @param  IRQn: specifies the IRQn line to check.
 * @return "0" when IRQn is "not enabled" and !0 otherwise
 */
ITStatus EXTI_GetITEnStatus(IRQn_Type IRQn)
{
    return ((NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] &
             (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) == (uint32_t)RESET)
               ? (RESET)
               : (SET);
}

decaIrqStatus_t decamutexon(void)
{
    decaIrqStatus_t s = EXTI_GetITEnStatus(DWM_IRQ_EXTI_IRQn);
    if (s)
        NVIC_EnableIRQ(DWM_IRQ_EXTI_IRQn);
    return s;
}

void decamutexoff(decaIrqStatus_t s)
{
    if (s)
    {
        NVIC_EnableIRQ(DWM_IRQ_EXTI_IRQn);
    }
    return;
}

void deca_sleep(unsigned int time_ms)
{
    HAL_Delay(time_ms);
}

void deca_usleep(unsigned long time_us)
{
    unsigned int i;

    time_us *= 12;
    for (i = 0; i < time_us; i++)
    {
        __NOP();
    }
}
