/*
 * Copyright (c) 2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-06     Supperthomas first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif /* RT_USING_NANO */

#define GPIO_LED_B    GET_PIN(F, 11)
#define GPIO_LED_R    GET_PIN(F, 12)

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       1024
#define THREAD_TIMESLICE        5

#define PIN_KEY0  GET_PIN(C,0)

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;

static void key_name_entry(void *parameter);
static void led_name_entry(void *parameter);
static rt_sem_t dynamic_sem = RT_NULL;

int main(void)
{
    rt_pin_mode(GPIO_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);

    dynamic_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_PRIO);
    if (dynamic_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. dynamic semaphore value = 0.\n");
    }

    tid1 = rt_thread_create("key_thread",
                            key_name_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }

    tid2 = rt_thread_create("led_thread",
                            led_name_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
    {
        rt_thread_startup(tid2);
    }

    // while (1)
    // {
    //     rt_pin_write(GPIO_LED_R, PIN_HIGH);
    //     rt_thread_mdelay(500);
    //     rt_pin_write(GPIO_LED_R, PIN_LOW);
    //     rt_thread_mdelay(500);
    // }
}
static void key_name_entry(void *parameter)
{
    rt_uint32_t count=0;
    while (1)
    {
        if(rt_pin_read(PIN_KEY0) == PIN_LOW)
        {
            rt_thread_mdelay(100);
            if(rt_pin_read(PIN_KEY0) == PIN_LOW)
            {
                rt_kprintf("key0 is pressed (%d) ", count++);
                    // rt_sem_release(dynamic_sem);
            }
            else
            {
                rt_sem_release(dynamic_sem);
            }
        }
        else
        {
            rt_sem_release(dynamic_sem);
        }
        rt_thread_mdelay(10);
    }
    
}

static void led_name_entry(void *parameter)
{
    rt_uint32_t count=0;
    rt_uint32_t result=0;
    while (1)
    {
        rt_pin_write(GPIO_LED_R, PIN_HIGH);
        result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {            
            // rt_kprintf("LED LOW\n");
            rt_pin_write(GPIO_LED_R, PIN_LOW);
        }
        
        rt_thread_mdelay(10);
    }
}
// #include <rtthread.h>
// #include "hello.h"

// int main(void) 
// {
//     while(1)
//     {
//         Print_Hello_World();
//         rt_thread_mdelay(500);
//     }

//     return 0;
// }

