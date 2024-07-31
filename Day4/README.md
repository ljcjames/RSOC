# 设备驱动
##  I/O设备框架概念
### SPI驱动和设备驱动分离，提供统一的API：
• 更换 MCU 只需要改变对应的对接驱动
• 重新驱动设备，只需要重新编写设备驱动相关的代码
• 同一 API 接口，学习成本低
• 分离后设备驱动可以入库，供公司其他项目使用，减少碎片化开发，防止反复造轮子
• 代码框架会变复杂，但是从上面的优点来看是值得的
![spi驱动与设备驱动分离示意图](image-3.png)
### I/O框架
I/O设备：显示屏、串口通信、flash、SD卡、以太网接口……
接口：open,close...
![I/O框架图](image-4.png)
### 派生设备种类
![alt text](image.png)
``` c 
RT_Device_Class_Char             /* 字符设备       */
RT_Device_Class_Block            /* 块设备         */
RT_Device_Class_NetIf            /* 网络接口设备    */
RT_Device_Class_MTD              /* 内存设备       */
RT_Device_Class_RTC              /* RTC 设备        */
RT_Device_Class_Sound            /* 声音设备        */
RT_Device_Class_Graphic          /* 图形设备        */
RT_Device_Class_I2CBUS           /* I2C 总线设备     */
RT_Device_Class_USBDevice        /* USB device 设备  */
RT_Device_Class_USBHost          /* USB host 设备   */
RT_Device_Class_SPIBUS           /* SPI 总线设备     */
RT_Device_Class_SPIDevice        /* SPI 设备        */
RT_Device_Class_SDIO             /* SDIO 设备       */
RT_Device_Class_Miscellaneous    /* 杂类设备        */

```
### 字符设备、块设备
#### 字符设备
顺序读取：键盘、串口
#### 块设备
随机读取：硬盘、SD卡、NAND FLASH
### 为什么分类设备
一类的控制相同
### 例子
RT_D

## 
### 创建销毁设备
### 注册销毁
### flags
分行？
### 实验1：注册

### 访问
### 查找、初始化
### 打开、关闭
### 打开标志位
### 控制设备
### 读写设备
### 回调
### 调用关系图

IO设备管理层
PIN设备驱动框架层
PIN设备驱动层

## GPIO
引脚：电源、时钟、控制、I/O
GPIO,功能复用I/O
可编程控制中断
![alt text](image-1.png)
rt_pin_mode()
rt_pin_write()
rt_pin_read()

![alt text](image-2.png)

### 外部中断

## I2C总线
