
## 软件包

wifi join Dong abcd07691234


## 组件
可以独立开发、测试、测试、部署和维护的软件单元
*与软件包关系： 组件如手脚，软件包如工具，都可以选择是否使用*

### 文件系统
用板载的W25Q64来学习
#### 文件系统定义
DFS, Device File System, RTT提供的虚拟文件系统组件
#### 文件系统架构
统一**根目录**用`/`表示，可以挂载目录、文件，允许不同目录下的**同名文件**
![目录与文件图](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-dir.png)
POSIX：一个协议，统一api名称，使代码可以在不同的操作系统中跑
ELM FATFS 文件系统：常用，RomFS系统：只读 （下文继续介绍）
![文件系统框架图](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-layer.png)
#### 文件系统种类
| 类型      | 特点 |
| - | - |
| FatFS      | 小型嵌入式设备，兼容微软，有良好的硬件无关性，RTT最常用，如:elm_fat       |
| RomFS   | 挂载根目录，只读        |
| DevFS | 设备文件系统，开启后设备在`/dev`虚拟成文件，可用read、write接口 |
| UFFS | 图文开发，用于Nand Flash，快、资源消耗少、免费 |
| NFS | 网络文件系统，用于网络连接操作另一台设备 |
#### POSIX接口层
一个协议，统一api名称，使代码可以在不同的操作系统中跑
**4个重要接口**
![POSIX](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-mg.png)
文件描述符：fd(file descriptor),对应一个文件，可能多对一（把我们找到需要的文件）
还有：
``` c
int rename(const char *old, const char *new); //重命名
int stat(const char *file, struct stat *buf); //取得状态
int unlink(const char *pathname); //删除文件
```
#### 目录管理
目录常用api
![目录常用api图](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-dir-mg.png)
#### 文件系统启动流程
| 名称 | 补充 |
| - | - |
| filesystemtable | 记录所用的文件系统 |
| filesystem_operation_table | 记录操作函数如何实现（如open，close……）|
|相关锁 | 如fd的互斥锁等 |

![alt text](image.png)





[更多参考官方文档链接](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/filesystem/filesystem?id=%e6%96%87%e4%bb%b6%e7%ae%a1%e7%90%86)
