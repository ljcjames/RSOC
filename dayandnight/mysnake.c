#include <stdio.h>
#include <rtthread.h>
#include <stdbool.h>
#include "my_func.h"
#include "mysnake.h"

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

void snake_entry(void)
{
    int snake_list[SNAKE_MAX][2] = {0};
    int snake_direction[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // 上，下，左，右

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
    int xx = 5;
    while (1)
    {
        rt_thread_mdelay(500);
        snake_address(snake_list[snake_tail][0], snake_list[snake_tail][1], SNAKE_SIZE, WHITE);
        former_head = snake_head;
        snake_head = (snake_head + 1) % (SNAKE_MAX);
        snake_tail = (snake_tail + 1) % (SNAKE_MAX);
        snake_list[snake_head][0] = snake_list[former_head][0] + snake_direction[now_direction][0];
        snake_list[snake_head][1] = snake_list[former_head][1] + snake_direction[now_direction][1];
        snake_address(snake_list[snake_head][0], snake_list[snake_head][1], SNAKE_SIZE, BLACK);
    }
}
