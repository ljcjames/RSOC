#include <drv_lcd.h>
#include <rtthread.h>
#include <stdio.h>
#include <malloc.h>

void lcd_black(int x, int y);
void lcd_white(int x, int y);
void snake_address(int x, int y, int r, const rt_uint16_t da);

// typedef int QDataType;

// typedef struct QListNode
// {
//     QDataType data;
//     struct QListNode* next;

// } QueueNode;
