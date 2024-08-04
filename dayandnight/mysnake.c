#include <stdio.h>
#include <rtthread.h>
#include <stdbool.h>
#include "my_func.h"
#include "mysnake.h"
#include <time.h>

#define LCD_MAX 240
#define SNAKE_SIZE 20
#define SNAKE_MAX LCD_MAX / SNAKE_SIZE

// bool snake_table[SNAKE_MAX][SNAKE_MAX] = {0};
// struct My_snake
// {
//     int x;
//     int y;
// }snake_list[SNAKE_MAX*SNAKE_MAX] = {0};
// /* rt_event_t 是指向事件结构体的指针类型  */
// typedef struct My_snake* my_snake_t;

void snake_entry(void *parameter)
{
    time_t t;
    /* 初始化随机数发生器 */
    srand((unsigned)time(&t));
    int snake_list[SNAKE_MAX][2] = {0};
    int snake_direction[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}; // 上，左，下，右
    char snake_dirshow[4][7] = {"upup", "left", "down", "rigt"};
    int snake_head = 2, snake_tail = 0, former_head; // 蛇头，蛇尾
    int now_direction = 3;                           // 当前方向
    snake_list[1][0] = SNAKE_MAX / 2;
    snake_list[1][1] = SNAKE_MAX / 2;
    snake_list[0][0] = snake_list[1][0] - 1;
    snake_list[0][1] = snake_list[1][1];
    snake_list[2][0] = snake_list[1][0] + 1;
    snake_list[2][1] = snake_list[1][1];
    // snake_table[snake_list[0][0]][snake_list[0][1]] = 1;
    // snake_table[snake_list[1][0]][snake_list[1][1]] = 1;
    // snake_table[snake_list[2][0]][snake_list[2][1]] = 1;
    snake_address(snake_list[0][0], snake_list[0][1], SNAKE_SIZE, BLACK);
    snake_address(snake_list[1][0], snake_list[1][1], SNAKE_SIZE, BLACK);
    snake_address(snake_list[2][0], snake_list[2][1], SNAKE_SIZE, BLACK);
    int new_direction = 0;
    while (1)
    {

        new_direction = rand() % 3;
        now_direction = (now_direction+3+new_direction)%4;//防止反向,走回头路
        lcd_show_string(20, 20, 16,snake_dirshow[now_direction]);
        rt_thread_mdelay(1000);
        snake_address(snake_list[snake_tail][0], snake_list[snake_tail][1], SNAKE_SIZE, WHITE);
        former_head = snake_head;
        snake_head = (snake_head + 1) % (SNAKE_MAX);
        snake_tail = (snake_tail + 1) % (SNAKE_MAX);
        snake_list[snake_head][0] = (snake_list[former_head][0] + snake_direction[now_direction][0]) % (SNAKE_MAX);
        snake_list[snake_head][1] = (snake_list[former_head][1] + snake_direction[now_direction][1]) % (SNAKE_MAX);
        snake_address(snake_list[snake_head][0], snake_list[snake_head][1], SNAKE_SIZE, BLACK);
    }
}
