#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>
#include <drv_lcd.h>

void lcd_black(int x, int y)
{
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(BLACK);
}

void lcd_white(int x, int y)
{
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(WHITE);
}
void snake_address(int x, int y, int r, const rt_uint16_t da)
{
    for (int i = x * r; i < x * r + r; i++)
    {
        for (int j = y * r; j < y * r + r; j++)
        {
            lcd_address_set(i, j, i, j);
            lcd_write_half_word(da);
        }
    }
}
// bt 命令行
int color_cmd(int argc, char **argv)
{
    snake_address(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), BLACK);
    return 1;
}
MSH_CMD_EXPORT_ALIAS(color_cmd, snk, bt 命令行);