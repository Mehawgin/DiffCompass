// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of how to display scroll

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                   CS    DC     RES     SDA    SCL    BLK    VCC     GND    
//ESP32-WROOM-32E:   15    2      27      13     14     21   5V/3.3V   GND 

//Remember to set the pins to suit your display module!

/***********************************************************************************
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
#include "font.h"

TFT_eSPI my_lcd = TFT_eSPI(); 

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

const char *aspect_name[] = {"PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"};
const char *color_name[] = { "BLUE", "GREEN", "RED", "WHITE" ,"CYAN","MAGENTA"};
uint16_t color_mask[] = { 0x001F, 0x07E0, 0xF800, 0xFFFF,0x07FF,0xF81F};

    
void show_16font(uint16_t x, uint16_t y,uint16_t fc, uint16_t bc,const char *str,uint8_t mode)
{
    uint16_t i,j,k,c_num,color=0;
    c_num = sizeof(tfont16)/sizeof(typFNT_GB16);
    for(k=0;k<c_num;k++)
    {         //pgm_read_byte
         if((pgm_read_byte(&tfont16[k].Index[0])==*str) && (pgm_read_byte(&tfont16[k].Index[1])==*(str+1)))
         {
            my_lcd.setAddrWindow(x, y, 16, 16);
            for(j=0;j<32;j++)
            {
               for(i = 0;i<8;i++)  
               {
                  if(mode) //叠加模式
                  {
                    if(pgm_read_byte(&tfont16[k].Msk[j])&(0x80>>i))
                    {
                        my_lcd.drawPixel(x+((j*8+i)%16),y+((j*8+i)/16),fc);
                     }
                    // x++;
                    // if((x-x0)==16)
                    // {
                   //     x = x0;
                   //     y++;   
                   //  }
     
                  }
                  else   //非叠加模式
                  {
                    if(pgm_read_byte(&tfont16[k].Msk[j])&(0x80>>i))
                    {
                         color = fc;
                     }
                     else
                     {
                        color = bc;
                     }
                     my_lcd.pushColors(&color, 1, true);
                  }
               }
            } 
      }
    } 
          
}

void show_24font(uint16_t x, uint16_t y,uint16_t fc, uint16_t bc,const char *str,uint8_t mode)
{
    uint16_t i,j,k,c_num,color;
    c_num = sizeof(tfont24)/sizeof(typFNT_GB24);
    for(k=0;k<c_num;k++)
    {
         if((pgm_read_byte(&tfont24[k].Index[0])==*str) && (pgm_read_byte(&tfont24[k].Index[1])==*(str+1)))
         {
            my_lcd.setAddrWindow(x, y, 24, 24);
            for(j=0;j<72;j++)
            {
               for(i = 0;i<8;i++)  
               {
                  if(mode) //叠加模式
                  {
                    if(pgm_read_byte(&tfont24[k].Msk[j])&(0x80>>i))
                    {
                        my_lcd.drawPixel(x+((j*8+i)%24),y+((j*8+i)/24),fc);
                     }
                  //   x++;
                  //   if((x-x0)==32)
                  //   {
                  //      x = x0;
                  //      y++;   
                  //   }
                  }
                  else   //非叠加模式
                  {
                    if(pgm_read_byte(&tfont24[k].Msk[j])&(0x80>>i))
                    {
                         color = fc;
                     }
                     else
                     {
                        color = bc;
                     }
                     my_lcd.pushColors(&color, 1, true);
                  }
               }
            } 
      }
    }
}

void show_32font(uint16_t x, uint16_t y,uint16_t fc, uint16_t bc,const char *str,uint8_t mode)
{
    uint16_t i,j,k,c_num,color;
    c_num = sizeof(tfont32)/sizeof(typFNT_GB32);
    for(k=0;k<c_num;k++)
    {
         if((pgm_read_byte(&tfont32[k].Index[0])==*str) && (pgm_read_byte(&tfont32[k].Index[1])==*(str+1)))
         {
             my_lcd.setAddrWindow(x, y, 32, 32);
            for(j=0;j<128;j++)
            {
               for(i = 0;i<8;i++)  
               {
                  if(mode) //叠加模式
                  {
                    if(pgm_read_byte(&tfont32[k].Msk[j])&(0x80>>i))
                    {
                        my_lcd.drawPixel(x+((j*8+i)%32),y+((j*8+i)/32),fc);
                     }
                   //  x++;
                  //   if((x-x0)==32)
                   //  {
                  //      x = x0;
                  //      y++;   
                   //  }
                  }
                  else   //非叠加模式
                  {
                    if(pgm_read_byte(&tfont32[k].Msk[j])&(0x80>>i))
                    {
                         color = fc;
                     }
                     else
                     {
                        color = bc;
                     }
                     my_lcd.pushColors(&color, 1, true);
                  }
               }
            } 
        }
    }
}

void show_chinese(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, const char *str,uint16_t csize,uint8_t mode)
{    
    if(x>(my_lcd.width()-csize)||y>(my_lcd.height()-csize))
      { 
        return;
      }              
    while(*str!='\0')
    { 
       if(csize==32)
       {
          show_32font(x, y,fc, bc,str,mode);
       }
      else if(csize==24)
      {
          show_24font(x, y,fc, bc,str,mode);
      }
      else
      {
          show_16font(x, y,fc, bc,str,mode);
      } 
      str+=3; 
      x+=csize;              
    }   
}

void show_pic(void)
{
    int i;
    uint16_t color;
    my_lcd.setAddrWindow(my_lcd.width()-60, 60, 40, 40); 
    //my_lcd.pushColors((uint8_t *)penguin_pic, 1600);
    for(i=0;i<1600;i++)
    {
      color = penguin_pic[2*i+1]<<8|penguin_pic[2*i];
      my_lcd.pushColor(color);
    }
 }

void windowScroll(int16_t x, int16_t y, int16_t wid, int16_t ht, int16_t dx, int16_t dy, uint16_t *buf)
{
    if (dx)
    { 
      for (int16_t row = 0; row < ht; row++) 
      {
           my_lcd.readRect(x, y + row, wid, 1, buf);
           my_lcd.setAddrWindow(x, y + row, wid, 1); 
           my_lcd.pushColors(buf + dx, wid - dx, true);
           my_lcd.pushColors(buf + 0, dx, true);
        }
    }
    if (dy) 
    {
      for (int16_t col = 0; col < wid; col++) 
      {

           my_lcd.readRect(x + col, y, 1, ht, buf);
           my_lcd.setAddrWindow(x + col, y, 1, ht); 
           my_lcd.pushColors(buf + dy, ht - dy, true);
           my_lcd.pushColors(buf + 0, dy, true);
      }
    }
}

void show_chinese_test(void)
{
     my_lcd.setRotation(1);
     show_chinese(15, 84,RED,BLACK,"欢迎您",16,1);
     show_chinese(15, 108,RED,BLACK,"欢迎您",24,1);
     show_chinese(15, 140,RED,BLACK,"欢迎您",32,1);
     delay(2000);
     my_lcd.fillScreen(BLACK);
     show_chinese(15, 84,RED,WHITE,"欢迎您",16,0);
     show_chinese(15, 108,RED,WHITE,"欢迎您",24,0);
     show_chinese(15, 140,RED,WHITE,"欢迎您",32,0);
}

void color_test()
{
  int n,i;
  int cnum = sizeof(color_mask)/sizeof(uint16_t);
  for(i=0;i<cnum;i++)
  {
    for(n=0;n<30;n++)
    {
      my_lcd.fillRect(n*my_lcd.width()/30,(my_lcd.height()/cnum)*i,(n+1)*my_lcd.width()/30,(my_lcd.height()/cnum)*(i+1),my_lcd.color565(n*8, n*8, n*8)&color_mask[i]);
     }
     my_lcd.setTextColor(color_mask[i]);
     my_lcd.drawString(color_name[i], 70, ((my_lcd.height()/cnum)-16)/2+(my_lcd.height()/cnum)*i,2);
  }
  delay(1000);
}

void text_test(void)
{
    my_lcd.setTextColor(RED);
    my_lcd.drawString("Hello World!", 50, 40,1);
   
    my_lcd.setTextColor(YELLOW);
    my_lcd.drawFloat(01234.56789, 5, 50, 48,2);
    
    my_lcd.setTextColor(BLUE);
    my_lcd.drawString("ABC123", 50, 64,4);

    my_lcd.setTextColor(GREEN);
    my_lcd.drawString("apmp", 50, 78,6);
    my_lcd.drawString("By utilizing breath",50,122,2);
    my_lcd.drawString("we soften our experiences.",50,138,1);
}

void setup()
{
  my_lcd.init();
  my_lcd.fillScreen(BLACK);
 // show_chinese_test();
 // show_pic();
}

void loop() 
{
    uint16_t rotation,n;
    my_lcd.setRotation(0);
//    uint16_t scrollbuf[my_lcd.height()]; 
    show_chinese_test();
    delay(500);
    for(rotation = 0;rotation<4;rotation++)
    {
        my_lcd.setRotation(rotation);
        my_lcd.fillScreen(BLACK);
        //text
        color_test();
        my_lcd.fillScreen(BLACK);
        delay(1000);        
        text_test();    
        delay(1000);
        for(n=0;n<32;n++)
        {
          my_lcd.fillRect(n*my_lcd.width()/32,88,(n+1)*my_lcd.width()/32,28,my_lcd.color565(n*8, n*8, n*8)&color_mask[rotation]);
        }
        my_lcd.setTextColor(color_mask[rotation+1]);
        my_lcd.drawString("COLOR TESTING", 50,95,2);
        my_lcd.setTextColor(WHITE);
        my_lcd.drawString(aspect_name[rotation], 50,146,2);
      
        show_pic();
        my_lcd.setTextColor(YELLOW);
        my_lcd.drawString("VERTICAL SCROLL", 50,162,2); 

         my_lcd.setTextColor(YELLOW);
         my_lcd.drawString("SOFTWARE SCROLL", 50,178,2); 
        // for (int16_t i = my_lcd.width(), dx = 4, dy = 0; i > 0; i -= dx)
        //{
         //    windowScroll(0, 216, my_lcd.width(), 16, dx, dy, scrollbuf);
       // }
         delay(1000);
     }
     
    my_lcd.invertDisplay(false);
    delay(3000);
    my_lcd.invertDisplay(true);
    my_lcd.fillScreen(BLACK);
}
