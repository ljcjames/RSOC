/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-5-10      ShiHao       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_common.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <drv_lcd.h>
#include <rttlogo.h>

/* 配置 LED 灯引脚 */
#define PIN_LED_B GET_PIN(F, 11) // PF11 :  LED_B        --> LED
#define PIN_LED_R GET_PIN(F, 12) // PF12 :  LED_R        --> LED
#define LCD_MAX 240

int roundxy[4][2] = {
    {0, 0},
    {0, LCD_MAX},
    {LCD_MAX, 0},
    {LCD_MAX, LCD_MAX},
};
int xymove[4][2] = {
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
};

extern void wlan_autoconnect_init(void);

void lcd_black(int x, int y)
{
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(BLACK);
}
void xy_round(int x, int y, int x2, int y2, int r,int ii)
{
    rt_kprintf("x:%d,y:%d,x2:%d,y2:%d,r:%d\n", x, y, x2, y2, r);
    for (int i = x; i != x2; i+=xymove[ii][0])
    {
        for (int j = y; j != y2; j+=xymove[ii][1])
        {
            int newi = x2 - i;
            int newj = y2 - j;
            rt_kprintf("(%d,%d,%d)",(newi * newi + newj * newj), newi, newj);
            if ((newi * newi + newj * newj) > (r * r))
            {
                // rt_kprintf("x:%d,y:%d\n", i, j);
                lcd_black(i, j);
            }
        }
    }
}
void my_round(int r)
{
    for (int i = 0; i < 4; i++)
    {
        xy_round(roundxy[i][0], roundxy[i][1], roundxy[i][0] + r * xymove[i][0], roundxy[i][1] + r * xymove[i][1], r,i);
    }
}
void xy_sink()
{
    for (int i = 0; i < 240; i++)
    {
        for (int j = 0; j <= 240; j++)
        {
            lcd_black(j, 240 - i);
            rt_thread_mdelay(1);
        }
        // rt_kprintf("(%d,...) Blacked\n", i);
    }
}
int main(void)
{
    char str[] = "wifi join Dong abcd07691234";
    my_round(20);

    rt_wlan_config_autoreconnect(RT_TRUE);
    rt_wlan_connect("Dong", "abcd07691234");
    system(str);

    /* init Wi-Fi auto connect feature */
    // wlan_autoconnect_init();
    /* enable auto reconnect on WLAN device */

    // lcd_clear(WHITE);

    // /* show RT-Thread logo */
    // lcd_show_image(0, 0, 240, 69, image_rttlogo);

    // /* set the background color and foreground color */
    // lcd_set_color(WHITE, BLACK);

    // /* show some string on lcd */
    // lcd_show_string(10, 69, 16, "Hello, RT-Thread!");
    // lcd_show_string(10, 69 + 16, 24, "RT-Thread");
    // lcd_show_string(10, 69 + 16 + 24, 32, "RT-Thread");

    // /* draw a line on lcd */
    // lcd_draw_line(0, 69 + 16 + 24 + 32, 240, 69 + 16 + 24 + 32);

    // /* draw a concentric circles */
    // lcd_draw_point(120, 194);
    // for (int i = 0; i < 46; i += 4)
    // {
    //     lcd_draw_circle(120, 194, i);
    // }
    return 0;
}
// #include <rtthread.h>
// #include <board.h>
// #include "init.h"
// #include <drv_gpio.h>
// #ifndef RT_USING_NANO
// #include <rtdevice.h>
// #endif // !RT_USING_NANO

// #define GPIO_LED_B GET_PIN(F,11)
// #define GPIO_LED_R GET_PIN(F,12)

// int main(void)
// {
//     main_init();
//     // rt_pin_mode(GPIO_LED_B, PIN_MODE_OUTPUT);
//     // while(1)
//     // {
//     //     rt_pin_write(GPIO_LED_B, PIN_HIGH);
//     //     rt_thread_mdelay(500);
//     //     rt_pin_write(GPIO_LED_B, PIN_LOW);
//     //     rt_thread_mdelay(500);
//     // }
//     return 0;
// }

// static int onboard_sdcard_mount(void)
// {
//     if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == RT_EOK)
//     {
//         LOG_I("SD card mount to '/sdcard'");
//     }
//     else
//     {
//         LOG_E("SD card mount to '/sdcard' failed!");
//     }

//     return RT_EOK;
// }

// #define WIFI_CS GET_PIN(F, 10)
// void WIFI_CS_PULL_DOWM(void)
// {
//     rt_pin_mode(WIFI_CS, PIN_MODE_OUTPUT);
//     rt_pin_write(WIFI_CS, PIN_LOW);
// }
// INIT_BOARD_EXPORT(WIFI_CS_PULL_DOWM);
