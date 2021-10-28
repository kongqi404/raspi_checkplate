
#include<show_screen.h>
#include<wiringPi.h>
#include<ssd1306_i2c.h>
#include<cstring>
#define MAXLINE 8192
char ts_cond[MAXLINE];
void init_led()
{
    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_display(); //Adafruit logo is visible
    set_ts_condition(0);
    show_ts_condition();
}
void end_screen()
{
    ssd1306_dim(1);
	ssd1306_startscrollright(00,0xFF);
	delay(1000);

	ssd1306_clearDisplay();
	ssd1306_fillRect(10,10, 50, 20, WHITE);
	ssd1306_fillRect(80, 10, 130, 50, WHITE);
	ssd1306_display();
}
void show_ts_condition()
{
    ssd1306_clearDisplay();
    ssd1306_drawString(ts_cond);
    ssd1306_display();
    
}

int show_plate(char *plate_str)
{
    ssd1306_clearDisplay();
    ssd1306_drawString(plate_str);
    ssd1306_display();
    delay(5000);
    show_ts_condition();
    return 1;
}

int show_car_info(char *car_info)
{
    ssd1306_clearDisplay();
    ssd1306_drawString(car_info);
    ssd1306_display();
    delay(5000);
    show_ts_condition();
    return 1;
}

void set_ts_condition(int ts_condition)
{
    switch(ts_condition)
    {
    case -1:
        strcpy(ts_cond,"always close");
        break;
    case 0:
        strcpy(ts_cond ,"normal");
        break;
    case 1:
        strcpy(ts_cond ,"always open");
        break;
    }
    
}