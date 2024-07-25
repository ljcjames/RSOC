//未完成
#include <rtthread.h>
#include <rtdevice.h>

#include <drv_spi.h>
#include <drv_gpio.h>


static int spi_attach(void)
{
    return rt_hw_spi_device_attach("spi2", "spi20", GET_PIN(B,12));
}
// INIT_DEVICE_EXPORT(spi_attach);

static int spi_transfer_one_data(void)
{
    rt_err_t ret =RT_EOK;
    struct rt_spi_device *spi_d20 = (struct rt_spi_device *)rt_device_find("spi20");

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB; 
    cfg.max_hz =1 *1000 *1000;
    rt_spi_configure(spi20,&cfg);

    rt_uint8_t sendBuff = 0xDA;
    rt_uint8_t recvBuff = 0xF1;
    ret =rt_spi_transfer(spi20,&sendBuff,&recvBuff,1);
    rt_kprintf("sret = %d\n",ret);
}
MSH_CMD_EXPORT(spi_transfer_one_data, spi transfer one data);