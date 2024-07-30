#include <rtthread.h>
#include<board.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif // !RT_USING_NANO

#define GPIO_LED_B GET_PIN(F,11)
#define GPIO_LED_R GET_PIN(F,12)

int main(void) 
{
    rt_pin_mode(GPIO_LED_B, PIN_MODE_OUTPUT);
    while(1)
    {
        rt_pin_write(GPIO_LED_B, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(GPIO_LED_B, PIN_LOW);
        rt_thread_mdelay(500);
    }
    return 0;
}

#define WIFI_CS GET_PIN(F,10)
void WIFI_CS_PULL_DOWN(void)
{
    rt_pin_mode(WIFI_CS, PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_CS, PIN_LOW);
}
INIT_BOARD_EXPORT(WIFI_CS_PULL_DOWN);


