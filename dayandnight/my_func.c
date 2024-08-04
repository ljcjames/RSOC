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
void snake_address(int x, int y,int r,const rt_uint16_t da)
{
    lcd_fill(x*r, y*r, x*r+r-1, y*r+r-1,da);
    lcd_write_half_word(da);
}
// bt 命令行
int color_cmd(int argc, char **argv)
{
    snake_address(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),BLACK);
    return 1;
}
MSH_CMD_EXPORT_ALIAS(color_cmd, snk, bt 命令行);