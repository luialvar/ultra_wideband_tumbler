#include "dw3000_config.h"

#include "config_options.h"
#include "deca_device_api.h"
#include "deca_interface.h"
#include "deca_types.h"
#include "port.h"

extern dwt_config_t config_options;
extern dwt_txconfig_t txconfig_options;

extern const struct dwt_driver_s dw3000_driver;
extern const struct dwt_driver_s dw3720_driver;
const struct dwt_driver_s *tmp_ptr[] = {&dw3000_driver, &dw3720_driver};

const struct dwt_spi_s dw3000_spi_fct = {.readfromspi = readfromspi,
                                         .writetospi = writetospi,
                                         .writetospiwithcrc = writetospiwithcrc,
                                         .setslowrate = port_set_dw_ic_spi_slowrate,
                                         .setfastrate = port_set_dw_ic_spi_fastrate};


const struct dwt_probe_s dw3000_probe_interf = {
    .dw = NULL,
    .spi = (void *)&dw3000_spi_fct,
    .wakeup_device_with_io = wakeup_device_with_io,
    .driver_list = (struct dwt_driver_s **)tmp_ptr,
    .dw_driver_num = 2,
};

void dwm300_initialize()
{
    NVIC_EnableIRQ(DWM_IRQ_EXTI_IRQn);

    init_SPI();

    HAL_Delay(2);
    int ret = dwt_probe((struct dwt_probe_s *)&dw3000_probe_interf);
    if (ret == DWT_ERROR)
    {
        while (1)
        {
        };
    }

    uint32_t dev_id;
    dev_id = dwt_readdevid();
    if (dev_id == (uint32_t)DWT_DW3720_PDOA_DEV_ID)
    {
        while (1)
            ;
    }

    while (!dwt_checkidlerc())
    {
    };
    if (dwt_initialise(DWT_READ_OTP_ALL) == DWT_ERROR)
    {
        while (1)
            ;
    }

    if (dwt_configure(&config_options))
    {
        while (1)
            ;
    };

    dwt_configuretxrf(&txconfig_options);
}
