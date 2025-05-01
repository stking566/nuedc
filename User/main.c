#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/24cxx/24Cxx.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/KEY/key.h"
#include "stdio.h"


int main(void)
{
    uint32_t adcx;
    unsigned short ludx;
    uint32_t gl5528;
    float temp;
	int send_address = 0;
	char send_buffer[5] = {0};
	char recv_buffer[5] = {0};
	int i = 0;
	uint8_t key = 0;
	int read_address = 0;
	int j = 5;
	int y = 25;
	int sec = 0;
	int min = 0;
	int hour = 0;
	
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    adc_init();                             /* 初始化ADC */
	key_init();
	at24cxx_init();
    
	
while(1)
{
	        key = key_scan(0);
            if(key == KEY1_PRES)
            {
                delay_ms(50);
                if(key == KEY1_PRES)
                {
					key1_flag ^= 1;
					lcd_clear(WHITE);
					
                }
            }
    if (key1_flag == 1)
    {
		lcd_show_string(30, 50, 200, 16, 24, "STM32", RED);
		lcd_show_string(30, 70, 200, 16, 24, "LUX_SHOW_PAGE", RED);
		lcd_show_string(30, 130, 200, 16, 24, "LUX_NOW =", BLUE); /* 先在固定位置显示小数点 */
        adcx = adc_get_result_average(ADC_ADCX_CHY, 10);        /* 获取通道5的转换值，10次取平均 */
        temp = (float)adcx * (3.3 / 4096);		/* 获取计算后的带小数的实际电压值 */  
        gl5528 = (33000.0/temp)-10000.0;
        ludx = GetLux(gl5528);
		printf("%hd\r\n" , ludx);
		sprintf(send_buffer , "%d" , ludx);
		at24cxx_write(send_address , (uint8_t *)send_buffer , sizeof(send_buffer));
		send_address += sizeof(send_buffer);
        lcd_show_xnum(140, 130, ludx, 4, 24, 0, BLUE); 		/* 显示流明值 */
        LED0_TOGGLE();
        delay_ms(200);
    }
	else if(key1_flag == 0)
	{
		lcd_show_string(30, 50, 200, 16, 24, "STM32", RED);
		lcd_show_string(30, 70, 200, 16, 24, "MEMORY_READ_PAGE", RED);
		lcd_show_string(30, 90, 200, 16, 24, "LUX_HISTORY", BLUE);
		lcd_show_string(150, 120, 200, 16, 24, "LUX", BLUE);
		lcd_show_string(100, 120, 200, 16, 24, "SEC", BLUE);
		lcd_show_string(60, 120, 200, 16, 24, "MIN", BLUE);
		lcd_show_string(0, 120, 200, 16, 24, "HOUR", BLUE);
		while(j--)
		{
			at24cxx_read(read_address,(uint8_t *)recv_buffer,sizeof(recv_buffer));
			lcd_show_string(150, 150+y, 200, 16, 24, recv_buffer, BLUE);
			sec = (send_address - read_address)/25;
			min = (sec /60) % 60;
			hour = (min/60) % 60;
			lcd_show_xnum(80, 150+y, sec, 4, 24, 0, BLUE);
			lcd_show_xnum(50, 150+y, min, 4, 24, 0, BLUE);
			lcd_show_xnum(0, 150+y, hour, 4, 24, 0, BLUE);
			y += 25;
			read_address += sizeof(recv_buffer);
		}
		j = 5;
		y = 25;
		while(key1_flag == 0)
		{
			key = key_scan(0);
            if(key == KEY1_PRES)
            {
                delay_ms(50);
                if(key == KEY1_PRES)
                {
					key1_flag ^= 1;
					lcd_clear(WHITE);
					y = 25;
					read_address = 0;
					
                }
            }
			else if(key == KEY0_PRES)
			{
				delay_ms(50);
				if(key == KEY0_PRES)
				{
					break;
				}
			}
			
		}
		
	}
}
}



















