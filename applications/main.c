#include <rtthread.h>
#include<board.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif // !RT_USING_NANO

#define GPIO_LED_B GET_PIN(F,11)
#define GPIO_LED_B GET_PIN(F,11)

int main(void) 
{
    
     return 0;
}

// #define WIFI_CS GET_PIN(F,10)
// void WIFICS_PULL_DOWN(void)
// {
//     rt_pin_mode(WIFI_CS, PIN_MODE_OUTPUT);
//     rt_pin_write(WIFI_CS, PIN_LOW);
// }
// INIT_BOARD_EXPORT(WIFI_CS_PULL_DOWN);


