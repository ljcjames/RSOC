#include <rtthread.h>
#include <rtdevice.h>

#define LOG_TAG "drv.test"
#define LOG_LVL LOG_LVL_DBG
#include <ulog.h>

static int dev_test_app(void)
[
    rt_device_t test_dev = rt_device_find("test_dev");
    if(test_dev == RT_NULL)
    {
        LOG_E("Cannot find test_dev");
        return -RT_ERROR;
    }

    rt_device_open(test_dev, RT_DEVICE_OFLAG_RDWR);
    rt_device_close(test_dev);
]