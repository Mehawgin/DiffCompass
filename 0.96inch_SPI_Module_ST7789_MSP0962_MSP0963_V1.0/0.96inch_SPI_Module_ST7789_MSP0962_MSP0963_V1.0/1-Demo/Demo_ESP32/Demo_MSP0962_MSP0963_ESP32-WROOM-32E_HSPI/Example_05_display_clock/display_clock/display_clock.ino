// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of showing a clock.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                   CS    DC     RES     SDA    SCL    BLK    VCC     GND    
//ESP32-WROOM-32E:   15    2      27      13     14     21   5V/3.3V   GND 

//Remember to set the pins to suit your display module!
/********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI my_lcd = TFT_eSPI(); 

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY 0x5AEB

unsigned char ctoi(char *ch);
unsigned long total_time=0;
unsigned char hours=ctoi((char *)__TIME__), mins=ctoi((char *)__TIME__+3), secs=ctoi((char *)__TIME__+6),flag=1;
unsigned int hours_x=119,hours_y=119,mins_x=119,mins_y=119,secs_x=119,secs_y=119;

unsigned char ctoi(char *ch)
{
  unsigned char tmp;
  if(*ch >= '0'&& *ch <= '9')
  {
    tmp = *ch - '0';  
  }
  else
  {
    return 0;  
  }  
  return 10*tmp+(*ch++ - '0');
}

void setup() 
{
    int i=0;
    unsigned int x0,y0,x1,y1;
    my_lcd.init();
    my_lcd.setTextColor(GREEN);   
    my_lcd.fillScreen(GREY);
    my_lcd.fillCircle(119, 119, 117,GREEN);
    my_lcd.fillCircle(119, 119, 107,BLACK);
    for(i=0;i<360;i+=30)
    {
        x0 = cos((i-90)*0.0174532925)*114+120;
        y0 = sin((i-90)*0.0174532925)*114+120;
        x1 = cos((i-90)*0.0174532925)*98+120;
        y1 = sin((i-90)*0.0174532925)*98+120;
        my_lcd.drawLine(x0, y0, x1, y1,GREEN);
    }
    for(i=0;i<360;i+=6)
    {
        x0 = cos((i-90)*0.0174532925)*102+120;
        y0 = sin((i-90)*0.0174532925)*102+120;
        my_lcd.drawPixel(x0,y0,WHITE);
        if(i==0 || i==180) 
          my_lcd.fillCircle(x0, y0, 2,BLUE);
        if(i==90 || i==270) 
          my_lcd.fillCircle(x0, y0, 2,BLUE);
    }
    my_lcd.fillCircle(119, 120, 4,BLUE);
    total_time = millis()+1000;
}

void loop() 
{  
  if(total_time<millis())
  {
      total_time+=1000;
      secs++;
      if(secs>=60)
      {
        secs=0;
        mins++;
        if(mins>59)
        {
           mins=0;
           hours++;
           if(hours>23)
           {
              hours=0; 
           }
        }  
      }
      if((secs==0)||flag)
      {
         flag=0;
          my_lcd.drawLine(hours_x, hours_y, 119, 120,BLACK);
         hours_x = cos((hours*30+(mins*6+(secs*6)*0.01666667)*0.0833333-90)*0.0174532925)*62+120;
         hours_y = sin((hours*30+(mins*6+(secs*6)*0.01666667)*0.0833333-90)*0.0174532925)*62+120;
         my_lcd.drawLine(mins_x, mins_y, 119, 120,BLACK);
         mins_x = cos((mins*6+(secs*6)*0.01666667-90)*0.0174532925)*84+119;
         mins_y = sin((mins*6+(secs*6)*0.01666667-90)*0.0174532925)*84+120;
      }
       my_lcd.drawLine(secs_x, secs_y, 119, 120,BLACK);
       secs_x = cos((secs*6-90)*0.0174532925)*90+120;
       secs_y = sin((secs*6-90)*0.0174532925)*90+120;
       my_lcd.drawLine(secs_x, secs_y, 119, 120,RED);
       my_lcd.drawLine(hours_x, hours_y, 119, 120,YELLOW);
       my_lcd.drawLine(mins_x, mins_y, 119, 120,WHITE);
       my_lcd.drawLine(secs_x, secs_y, 119, 120,RED);
       my_lcd.fillCircle(119, 120, 4,RED);
  }
  my_lcd.drawString(__DATE__, my_lcd.width()/2-44,160,2);
}
