// #include "rtthread.h"
// #include "dev_sign_api.h"
// #include "mqtt_api.h"

// char DEMO_PRODUCT_KEY[IOTX_PRODUCT_KEY_LEN + 1] = {0};
// char DEMO_DEVICE_NAME[IOTX_DEVICE_NAME_LEN + 1] = {0};
// char DEMO_DEVICE_SECRET[IOTX_DEVICE_SECRET_LEN + 1] = {0};

// void *HAL_Malloc(uint32_t size);
// void HAL_Free(void *ptr);
// void HAL_Printf(const char *fmt, ...);
// int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1]);
// int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1]);
// int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);
// uint64_t HAL_UptimeMs(void);
// int HAL_Snprintf(char *str, const int len, const char *fmt, ...);

// #define EXAMPLE_TRACE(fmt, ...)                        \
//     do                                                 \
//     {                                                  \
//         HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
//         HAL_Printf(fmt, ##__VA_ARGS__);                \
//         HAL_Printf("%s", "\r\n");                      \
//     } while (0)

// static void example_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
// {
//     iotx_mqtt_topic_info_t *topic_info = (iotx_mqtt_topic_info_pt)msg->msg;

//     switch (msg->event_type)
//     {
//     case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
//         /* print topic name and topic message */
//         EXAMPLE_TRACE("Message Arrived:");
//         EXAMPLE_TRACE("Topic  : %.*s", topic_info->topic_len, topic_info->ptopic);
//         EXAMPLE_TRACE("Payload: %.*s", topic_info->payload_len, topic_info->payload);
//         EXAMPLE_TRACE("\n");
//         break;
//     default:
//         break;
//     }
// }

// static int example_subscribe(void *handle)
// {
//     int res = 0;
//     const char *fmt = "/%s/%s/user/get";
//     char *topic = NULL;
//     int topic_len = 0;

//     topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
//     topic = HAL_Malloc(topic_len);
//     if (topic == NULL)
//     {
//         EXAMPLE_TRACE("memory not enough");
//         return -1;
//     }
//     memset(topic, 0, topic_len);
//     HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

//     res = IOT_MQTT_Subscribe(handle, topic, IOTX_MQTT_QOS0, example_message_arrive, NULL);
//     if (res < 0)
//     {
//         EXAMPLE_TRACE("subscribe failed");
//         HAL_Free(topic);
//         return -1;
//     }

//     HAL_Free(topic);
//     return 0;
// }

// static int example_publish(void *handle)
// {
//     int res = 0;
//     const char *fmt = "/sys/%s/%s/thing/event/property/post";
//     char *topic = NULL;
//     int topic_len = 0;
//     char *payload = "{\"message\":\"hello!\"}";

//     topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
//     topic = HAL_Malloc(topic_len);
//     if (topic == NULL)
//     {
//         EXAMPLE_TRACE("memory not enough");
//         return -1;
//     }
//     memset(topic, 0, topic_len);
//     HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

//     res = IOT_MQTT_Publish_Simple(0, topic, IOTX_MQTT_QOS0, payload, strlen(payload));
//     if (res < 0)
//     {
//         EXAMPLE_TRACE("publish failed, res = %d", res);
//         HAL_Free(topic);
//         return -1;
//     }

//     HAL_Free(topic);
//     return 0;
// }

// static void example_event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
// {
//     EXAMPLE_TRACE("msg->event_type : %d", msg->event_type);
// }

// /*
//  *  NOTE: About demo topic of /${productKey}/${deviceName}/user/get
//  *
//  *  The demo device has been configured in IoT console (https://iot.console.aliyun.com)
//  *  so that its /${productKey}/${deviceName}/user/get can both be subscribed and published
//  *
//  *  We design this to completely demonstrate publish & subscribe process, in this way
//  *  MQTT client can receive original packet sent by itself
//  *
//  *  For new devices created by yourself, pub/sub privilege also requires being granted
//  *  to its /${productKey}/${deviceName}/user/get for successfully running whole example
//  */

// void mqtt_example_main(void *parameter)
// {
//     void *pclient = NULL;
//     int res = 0;
//     int loop_cnt = 0;
//     iotx_mqtt_param_t mqtt_params;

//     HAL_GetProductKey(DEMO_PRODUCT_KEY);
//     HAL_GetDeviceName(DEMO_DEVICE_NAME);
//     HAL_GetDeviceSecret(DEMO_DEVICE_SECRET);

//     EXAMPLE_TRACE("mqtt example");

//     /* Initialize MQTT parameter */
//     /*
//      * Note:
//      *
//      * If you did NOT set value for members of mqtt_params, SDK will use their default values
//      * If you wish to customize some parameter, just un-comment value assigning expressions below
//      *
//      **/
//     memset(&mqtt_params, 0x0, sizeof(mqtt_params));

//     /**
//      *
//      *  MQTT connect hostname string
//      *
//      *  MQTT server's hostname can be customized here
//      *
//      *  default value is ${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com
//      */
//     /* mqtt_params.host = "something.iot-as-mqtt.cn-shanghai.aliyuncs.com"; */

//     /**
//      *
//      *  MQTT connect port number
//      *
//      *  TCP/TLS port which can be 443 or 1883 or 80 or etc, you can customize it here
//      *
//      *  default value is 1883 in TCP case, and 443 in TLS case
//      */
//     /* mqtt_params.port = 1883; */

//     /**
//      *
//      * MQTT request timeout interval
//      *
//      * MQTT message request timeout for waiting ACK in MQTT Protocol
//      *
//      * default value is 2000ms.
//      */
//     /* mqtt_params.request_timeout_ms = 2000; */

//     /**
//      *
//      * MQTT clean session flag
//      *
//      * If CleanSession is set to 0, the Server MUST resume communications with the Client based on state from
//      * the current Session (as identified by the Client identifier).
//      *
//      * If CleanSession is set to 1, the Client and Server MUST discard any previous Session and Start a new one.
//      *
//      * default value is 0.
//      */
//     /* mqtt_params.clean_session = 0; */

//     /**
//      *
//      * MQTT keepAlive interval
//      *
//      * KeepAlive is the maximum time interval that is permitted to elapse between the point at which
//      * the Client finishes transmitting one Control Packet and the point it starts sending the next.
//      *
//      * default value is 60000.
//      */
//     /* mqtt_params.keepalive_interval_ms = 60000; */

//     /**
//      *
//      * MQTT write buffer size
//      *
//      * Write buffer is allocated to place upstream MQTT messages, MQTT client will be limitted
//      * to send packet no longer than this to Cloud
//      *
//      * default value is 1024.
//      *
//      */
//     /* mqtt_params.write_buf_size = 1024; */

//     /**
//      *
//      * MQTT read buffer size
//      *
//      * Write buffer is allocated to place downstream MQTT messages, MQTT client will be limitted
//      * to recv packet no longer than this from Cloud
//      *
//      * default value is 1024.
//      *
//      */
//     /* mqtt_params.read_buf_size = 1024; */

//     /**
//      *
//      * MQTT event callback function
//      *
//      * Event callback function will be called by SDK when it want to notify user what is happening inside itself
//      *
//      * default value is NULL, which means PUB/SUB event won't be exposed.
//      *
//      */
//     mqtt_params.handle_event.h_fp = example_event_handle;

//     pclient = IOT_MQTT_Construct(&mqtt_params);
//     if (NULL == pclient)
//     {
//         EXAMPLE_TRACE("MQTT construct failed");
//         return;
//     }

//     res = example_subscribe(pclient);
//     if (res < 0)
//     {
//         IOT_MQTT_Destroy(&pclient);
//         return;
//     }

//     while (1)
//     {
//         if (0 == loop_cnt % 20)
//         {
//             example_publish(pclient);
//         }

//         IOT_MQTT_Yield(pclient, 200);

//         loop_cnt += 1;
//     }
// }

// #define THREAD_PRIORITY 25
// #define THREAD_STACK_SIZE 4096
// #define THREAD_TIMESLICE 5

// rt_thread_t MQTT_Thread;

// void MQTT_Creat_Thread(void)
// {
//     // 创建线程
//     MQTT_Thread = rt_thread_create("MQTT_Thread", mqtt_example_main, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
//     // 创建成功就启动
//     if (MQTT_Thread != RT_NULL)
//     {
//         rt_thread_startup(MQTT_Thread);
//     }
//     else
//     {
//         rt_kprintf("MQTT_Thread_Thread Create Fail");
//     }
// }
// // 导出Shell命令
// MSH_CMD_EXPORT(MQTT_Creat_Thread, This Function will creat a MQTT thread.);


/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 * 
 * Again edit by rt-thread group
 * Change Logs:
 * Date          Author          Notes
 * 2019-07-21    MurphyZhao      first edit
 */

#include "rtthread.h"
#include "dev_sign_api.h"
#include "mqtt_api.h"
#include <board.h>
#include <drv_gpio.h>
#include <stdio.h>
#include <string.h>
#include "aht10.h"

char DEMO_PRODUCT_KEY[IOTX_PRODUCT_KEY_LEN + 1] = {0};
char DEMO_DEVICE_NAME[IOTX_DEVICE_NAME_LEN + 1] = {0};
char DEMO_DEVICE_SECRET[IOTX_DEVICE_SECRET_LEN + 1] = {0};

void *HAL_Malloc(uint32_t size);
void HAL_Free(void *ptr);
void HAL_Printf(const char *fmt, ...);
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1]);
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1]);
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);
uint64_t HAL_UptimeMs(void);
int HAL_Snprintf(char *str, const int len, const char *fmt, ...);

// AHT挂载的总线名字
#define AHT10_I2C_BUS "i2c3"

    // AHT设备指针
    aht10_device_t Dev = RT_NULL;

    // Humi:湿度值,Temp:温度值
    float Humi, Temp;


#define EXAMPLE_TRACE(fmt, ...)  \
    do { \
        HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
        HAL_Printf(fmt, ##__VA_ARGS__); \
        HAL_Printf("%s", "\r\n"); \
    } while(0)

static void example_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    iotx_mqtt_topic_info_t     *topic_info = (iotx_mqtt_topic_info_pt) msg->msg;

    switch (msg->event_type) {
        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
            /* print topic name and topic message */
            EXAMPLE_TRACE("Message Arrived:");
            EXAMPLE_TRACE("Topic  : %.*s", topic_info->topic_len, topic_info->ptopic);
            EXAMPLE_TRACE("Payload: %.*s", topic_info->payload_len, topic_info->payload);
            EXAMPLE_TRACE("\n");
            break;
        default:
            break;
    }
}

static int example_subscribe(void *handle)
{
    int res = 0;
    const char *fmt = "/%s/%s/user/get";
    char *topic = NULL;
    int topic_len = 0;

    topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
    topic = HAL_Malloc(topic_len);
    if (topic == NULL) {
        EXAMPLE_TRACE("memory not enough");
        return -1;
    }
    memset(topic, 0, topic_len);
    HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

    res = IOT_MQTT_Subscribe(handle, topic, IOTX_MQTT_QOS0, example_message_arrive, NULL);
    if (res < 0) {
        EXAMPLE_TRACE("subscribe failed");
        HAL_Free(topic);
        return -1;
    }

    HAL_Free(topic);
    return 0;
}

        char tmp[256];
void tmp_payload(void)
{
     // 读取温湿度值
        Humi = aht10_read_humidity(Dev);
        Temp = aht10_read_temperature(Dev);
        sprintf(tmp, "{\"params\":{\"temperature\":%.2f,\"humidity\":%.2f}}", Temp, Humi);
        rt_kprintf("\n%f %f tmp:%s\n",Humi,Temp,tmp);
        return;
}
static int example_publish(void *handle)
{
    
    
    tmp_payload();
    int             res = 0;
    const char     *fmt = "/sys/%s/%s/thing/event/property/post";
    // /k1lyriw1yGj/${deviceName}/user/get
    char           *topic = NULL;
    int             topic_len = 0;
    char           *payload = tmp;
    // strcpy(payload,tmp_payload());
    rt_kprintf("payload:%s\n",payload);
    topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
    topic = HAL_Malloc(topic_len);
    if (topic == NULL) {
        EXAMPLE_TRACE("memory not enough");
        return -1;
    }
    memset(topic, 0, topic_len);
    HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

    res = IOT_MQTT_Publish_Simple(0, topic, IOTX_MQTT_QOS0, payload, strlen(payload));
    if (res < 0) {
        EXAMPLE_TRACE("publish failed, res = %d", res);
        HAL_Free(topic);
        return -1;
    }

    HAL_Free(topic);
    return 0;
}

static void example_event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    EXAMPLE_TRACE("msg->event_type : %d", msg->event_type);
}

/*
 *  NOTE: About demo topic of /${productKey}/${deviceName}/user/get
 *
 *  The demo device has been configured in IoT console (https://iot.console.aliyun.com)
 *  so that its /${productKey}/${deviceName}/user/get can both be subscribed and published
 *
 *  We design this to completely demonstrate publish & subscribe process, in this way
 *  MQTT client can receive original packet sent by itself
 *
 *  For new devices created by yourself, pub/sub privilege also requires being granted
 *  to its /${productKey}/${deviceName}/user/get for successfully running whole example
 */

static void mqtt_example_main(void *parameter)
{
    void                   *pclient = NULL;
    int                     res = 0;
    int                     loop_cnt = 0;
    iotx_mqtt_param_t       mqtt_params;

    HAL_GetProductKey(DEMO_PRODUCT_KEY);
    HAL_GetDeviceName(DEMO_DEVICE_NAME);
    HAL_GetDeviceSecret(DEMO_DEVICE_SECRET);

    EXAMPLE_TRACE("mqtt example");

    /* Initialize MQTT parameter */
    /*
     * Note:
     *
     * If you did NOT set value for members of mqtt_params, SDK will use their default values
     * If you wish to customize some parameter, just un-comment value assigning expressions below
     *
     **/
    memset(&mqtt_params, 0x0, sizeof(mqtt_params));

    /**
     *
     *  MQTT connect hostname string
     *
     *  MQTT server's hostname can be customized here
     *
     *  default value is ${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com
     */
    /* mqtt_params.host = "something.iot-as-mqtt.cn-shanghai.aliyuncs.com"; */

    /**
     *
     *  MQTT connect port number
     *
     *  TCP/TLS port which can be 443 or 1883 or 80 or etc, you can customize it here
     *
     *  default value is 1883 in TCP case, and 443 in TLS case
     */
    /* mqtt_params.port = 1883; */

    /**
     *
     * MQTT request timeout interval
     *
     * MQTT message request timeout for waiting ACK in MQTT Protocol
     *
     * default value is 2000ms.
     */
    /* mqtt_params.request_timeout_ms = 2000; */

    /**
     *
     * MQTT clean session flag
     *
     * If CleanSession is set to 0, the Server MUST resume communications with the Client based on state from
     * the current Session (as identified by the Client identifier).
     *
     * If CleanSession is set to 1, the Client and Server MUST discard any previous Session and Start a new one.
     *
     * default value is 0.
     */
    /* mqtt_params.clean_session = 0; */

    /**
     *
     * MQTT keepAlive interval
     *
     * KeepAlive is the maximum time interval that is permitted to elapse between the point at which
     * the Client finishes transmitting one Control Packet and the point it starts sending the next.
     *
     * default value is 60000.
     */
    /* mqtt_params.keepalive_interval_ms = 60000; */

    /**
     *
     * MQTT write buffer size
     *
     * Write buffer is allocated to place upstream MQTT messages, MQTT client will be limitted
     * to send packet no longer than this to Cloud
     *
     * default value is 1024.
     *
     */
    /* mqtt_params.write_buf_size = 1024; */

    /**
     *
     * MQTT read buffer size
     *
     * Write buffer is allocated to place downstream MQTT messages, MQTT client will be limitted
     * to recv packet no longer than this from Cloud
     *
     * default value is 1024.
     *
     */
    /* mqtt_params.read_buf_size = 1024; */

    /**
     *
     * MQTT event callback function
     *
     * Event callback function will be called by SDK when it want to notify user what is happening inside itself
     *
     * default value is NULL, which means PUB/SUB event won't be exposed.
     *
     */
    mqtt_params.handle_event.h_fp = example_event_handle;

    pclient = IOT_MQTT_Construct(&mqtt_params);
    if (NULL == pclient) {
        EXAMPLE_TRACE("MQTT construct failed");
        return ;
    }

    res = example_subscribe(pclient);
    if (res < 0) {
        IOT_MQTT_Destroy(&pclient);
        return ;
    }

    while (1) {
        if (0 == loop_cnt % 20) {
            example_publish(pclient);
        }

        IOT_MQTT_Yield(pclient, 200);

        loop_cnt += 1;
    }

    return ;
}


#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 4096
#define THREAD_TIMESLICE 5

rt_thread_t MQTT_Thread = RT_NULL;

void MQTT_Creat_Thread(void)
{

    // 初始化设备
    Dev = aht10_init(AHT10_I2C_BUS);
    if (Dev == RT_NULL)
    {
        rt_kprintf("AHT10_init Fail");
        return;
    }

    MQTT_Thread = rt_thread_create("MTQQ_Thread", mqtt_example_main, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if (MQTT_Thread != RT_NULL)
    {
        rt_thread_startup(MQTT_Thread);
    }
    else
    {
        rt_kprintf("MQTT Thread Create Failed!\n");
    }
    
}
MSH_CMD_EXPORT(MQTT_Creat_Thread, create a MQTT_Thread);