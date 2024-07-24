#include<rtthread.h>

#define THREAD_STACK_SIZE 512
#define THREAD_PRIORITY 25
#define THREAD_TIMESLICE 5

static rt_thread_t tid1;
static rt_thread_t tid1 =RT_NULL;

static void thread1_entry(void *parameter)
{
    int count = 0;

    while(1)
    {
        rt_kprintf("thread1 count:(%d) tick:%lu\n", count++,rt_tick_get());
        rt_thread_delay(500);
    }
}

static char thread2_stack[THREAD_STACK_SIZE*2];
static struct rt_thread thread2;

static void thread2_entry(void *parameter)
{
    int count = 0;

    while(count<10)
    {
        rt_kprintf("thread2 count:(%d) tick:%lu\n", count++,rt_tick_get());
        rt_thread_delay(1000);
    }
    rt_kprintf("thread2 is exiting\n");
}

int tgame(void)
{
    tid1=rt_thread_create("thread1",
    thread1_entry,
    RT_NULL,
    THREAD_STACK_SIZE,
    THREAD_PRIORITY,
    THREAD_TIMESLICE);
    if(tid1!=RT_NULL)
        rt_thread_startup(tid1);
    rt_thread_init(&thread2,"thread2",thread2_entry,RT_NULL,thread2_stack,THREAD_STACK_SIZE,THREAD_PRIORITY-1,THREAD_TIMESLICE);
    rt_thread_startup(&thread2);
    return 0;
}
MSH_CMD_EXPORT(tgame, test thread game);