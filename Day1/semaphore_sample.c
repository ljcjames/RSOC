#include <rtthread.h>

#define THREAD_PRIORITY         25
#define THREAD_TIMESLICE        5

/* 指向信号量的指针 */
static rt_sem_t dynamic_sem = RT_NULL;

static char thread1_stack[1024];
static struct rt_thread thread1;

/* 线程1入口函数 */
static void rt_thread1_entry(void *parameter)
{
    static rt_uint8_t count = 0;

    while(1)
    {
        if(count <= 100)
        {
            count++;  // 计数器递增
        }
        else
        {
            return;  // 计数器大于100时退出线程
        }

        /* count 每计数 10 次，就释放一次信号量 */
        if(0 == (count % 10))
        {
            rt_kprintf("t1 release a dynamic semaphore.\n");
            rt_sem_release(dynamic_sem);  // 释放信号量
        }
    }
}

static char thread2_stack[1024];
static struct rt_thread thread2;

/* 线程2入口函数 */
static void rt_thread2_entry(void *parameter)
{
    static rt_err_t result;
    static rt_uint8_t number = 0;

    while(1)
    {
        /* 永久方式等待信号量，获取到信号量，则执行 number 自加的操作 */
        result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            rt_kprintf("t2 take a dynamic semaphore, failed.\n");
            rt_sem_delete(dynamic_sem);  // 删除信号量
            return;
        }
        else
        {
            number++;  // 信号量获取成功，number 自加
            rt_kprintf("t2 take a dynamic semaphore. number = %d\n", number);
        }
    }
}

/* 信号量示例的初始化 */
int semaphore_sample(void)
{
    /* 创建一个动态信号量，初始值是 0 */
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

    /* 初始化并启动线程1 */
    rt_thread_init(&thread1,
                   "thread1",                       /* 线程名称 */
                   rt_thread1_entry,                /* 线程入口函数 */
                   RT_NULL,                         /* 入口函数参数 */
                   &thread1_stack[0],               /* 线程栈起始地址 */
                   sizeof(thread1_stack),           /* 线程栈大小 */
                   THREAD_PRIORITY, THREAD_TIMESLICE); /* 线程优先级和时间片大小 */
    rt_thread_startup(&thread1);

    /* 初始化并启动线程2 */
    rt_thread_init(&thread2,
                   "thread2",                       /* 线程名称 */
                   rt_thread2_entry,                /* 线程入口函数 */
                   RT_NULL,                         /* 入口函数参数 */
                   &thread2_stack[0],               /* 线程栈起始地址 */
                   sizeof(thread2_stack),           /* 线程栈大小 */
                   THREAD_PRIORITY-1, THREAD_TIMESLICE); /* 线程优先级和时间片大小 */
    rt_thread_startup(&thread2);

    return 0;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(semaphore_sample, semaphore sample);