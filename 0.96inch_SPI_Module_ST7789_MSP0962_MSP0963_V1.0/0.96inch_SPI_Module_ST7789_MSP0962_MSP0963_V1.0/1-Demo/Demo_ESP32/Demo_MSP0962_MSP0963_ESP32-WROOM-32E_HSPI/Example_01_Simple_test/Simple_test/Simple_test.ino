//This application does not rely on any libraries and it is for ST7789

//This program is a demo of clearing screen.

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
#include <Arduino.h>
#include <SPI.h>
#include <Print.h>
#include "spi_dev.h"

#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define WHITE 0xFFFF
#define BLACK 0x0000

#define LCD_WIDTH 240
#define LCD_HEIGHT 198

#define WR_RAM_CMD 0x2C
#define RD_RAM_CMD 0x2E
#define SET_X_CMD  0x2A
#define SET_Y_CMD  0x2B
#define MADCTL_CMD 0x36

bool lock_flag = true;

SPIClass spi = SPIClass(SPI_PORT);

void SPI_Start_Write(void)
{
    if(lock_flag)
    {
       lock_flag = false;
       spi.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE));
       LCD_CS_LOW;
       SET_SPI_WRITE_MODE;
    }
}

void SPI_End_Write(void)
{
    if(!lock_flag)
    {
      lock_flag = true;
      LCD_CS_HIGH;
      SET_SPI_READ_MODE;
      spi.endTransaction();
    }
}

void LCD_Write_Reg(uint8_t val)
{
    SPI_Start_Write(); 
    LCD_DC_LOW;
    spi_write_8bit(val);
    SPI_End_Write();
}

void LCD_Write_Data_8Bit(uint8_t val)
{
    SPI_Start_Write();  
    LCD_DC_HIGH;
    spi_write_8bit(val);
    SPI_End_Write();
}

void LCD_Write_Data_16Bit(uint16_t val)
{
    SPI_Start_Write(); 
    LCD_DC_HIGH;
    spi_write_16bit(val);
    SPI_End_Write();
}

void LCD_Set_Windows(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
    LCD_Write_Reg(SET_X_CMD);
    LCD_Write_Data_16Bit(sx);
    LCD_Write_Data_16Bit(ex);
    LCD_Write_Reg(SET_Y_CMD);
    LCD_Write_Data_16Bit(sy);
    LCD_Write_Data_16Bit(ey);
    LCD_Write_Reg(WR_RAM_CMD);
}

void SPI_Init(void)
{
    spi.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, -1);   
}

void Lcd_Init(void)
{
    LCD_RST_HIGH;
    delay(50);
    LCD_RST_LOW;
    delay(100);
    LCD_RST_HIGH;
    delay(50);
 
  //ST7789H2 Init
  LCD_Write_Reg(0x36); 
  LCD_Write_Data_8Bit(0x00);

  LCD_Write_Reg(0x3A); 
  LCD_Write_Data_8Bit(0x05);

  LCD_Write_Reg(0xB2);
  LCD_Write_Data_8Bit(0x0C);
  LCD_Write_Data_8Bit(0x0C);
  LCD_Write_Data_8Bit(0x00);
  LCD_Write_Data_8Bit(0x33);
  LCD_Write_Data_8Bit(0x33);

  LCD_Write_Reg(0xB7); 
  LCD_Write_Data_8Bit(0x35);  

  LCD_Write_Reg(0xBB);
  LCD_Write_Data_8Bit(0x17);

  LCD_Write_Reg(0xC0);
  LCD_Write_Data_8Bit(0x2C);

  LCD_Write_Reg(0xC2);
  LCD_Write_Data_8Bit(0x01);

  LCD_Write_Reg(0xC3);
  LCD_Write_Data_8Bit(0x12);   

  LCD_Write_Reg(0xC4);
  LCD_Write_Data_8Bit(0x20);  

  LCD_Write_Reg(0xC6); 
  LCD_Write_Data_8Bit(0x0F);    

  LCD_Write_Reg(0xD0); 
  LCD_Write_Data_8Bit(0xA4);
  LCD_Write_Data_8Bit(0xA1);

  LCD_Write_Reg(0xE0);
  LCD_Write_Data_8Bit(0xD0);
  LCD_Write_Data_8Bit(0x04);
  LCD_Write_Data_8Bit(0x0D);
  LCD_Write_Data_8Bit(0x11);
  LCD_Write_Data_8Bit(0x13);
  LCD_Write_Data_8Bit(0x2B);
  LCD_Write_Data_8Bit(0x3F);
  LCD_Write_Data_8Bit(0x54);
  LCD_Write_Data_8Bit(0x4C);
  LCD_Write_Data_8Bit(0x18);
  LCD_Write_Data_8Bit(0x0D);
  LCD_Write_Data_8Bit(0x0B);
  LCD_Write_Data_8Bit(0x1F);
  LCD_Write_Data_8Bit(0x23);

  LCD_Write_Reg(0xE1);
  LCD_Write_Data_8Bit(0xD0);
  LCD_Write_Data_8Bit(0x04);
  LCD_Write_Data_8Bit(0x0C);
  LCD_Write_Data_8Bit(0x11);
  LCD_Write_Data_8Bit(0x13);
  LCD_Write_Data_8Bit(0x2C);
  LCD_Write_Data_8Bit(0x3F);
  LCD_Write_Data_8Bit(0x44);
  LCD_Write_Data_8Bit(0x51);
  LCD_Write_Data_8Bit(0x2F);
  LCD_Write_Data_8Bit(0x1F);
  LCD_Write_Data_8Bit(0x1F);
  LCD_Write_Data_8Bit(0x20);
  LCD_Write_Data_8Bit(0x23);

  LCD_Write_Reg(0x21); 

  LCD_Write_Reg(0x11); 
  //Delay (120); 

  LCD_Write_Reg(0x29); 
}

void Write_color_Block(uint16_t color, uint32_t len)
{
    volatile uint32_t* wr_buf = spi_write_buf;
    uint32_t color32 = ((color << 8 | color >> 8) << 16) | (color << 8 | color >> 8);
    uint8_t num = len%32,i=0;
    if(num)
    {
        while(*spi_cmd & SPI_USR);
        while(i < num)
        {
            *wr_buf++ = color32;
            i += 2; 
        }
        *spi_write_len = num * 16 - 1;
        *spi_cmd = SPI_USR;
        if(len < 32)
        {
            return;
        }
        len -= num;
        for(i /= 2; i < 16; i++)
        {
            *wr_buf++ = color32;
        }
    }
    while(*spi_cmd & SPI_USR);
    if(!num)
    {    
        while(i < 16)
        {
            *wr_buf++ = color32;
            i++; 
        }
    }
    *spi_write_len = 511;
    while(len)
    {
        while(*spi_cmd & SPI_USR);
        *spi_cmd = SPI_USR;
        len -= 32;
    }
    while(*spi_cmd & SPI_USR);
}

void LCD_Clear_Screen(uint16_t sx, uint16_t sy, uint16_t w, uint16_t h, uint16_t color)
{
    if((sx >= LCD_WIDTH) || (sy >= LCD_HEIGHT))
        return;
    if(((sx + w) > LCD_WIDTH) || ((sy + h) > LCD_HEIGHT))
        return;
    if(((w < 1) || (w > LCD_WIDTH)) || ((h < 1) || (h > LCD_HEIGHT)))
        return;
    LCD_Set_Windows(sx, sy, sx + w - 1, sy + h -1);
    LCD_DC_HIGH;
    SPI_Start_Write(); 
    Write_color_Block(color, w*h);
    SPI_End_Write();
}

void Draw_Pixel(unsigned int x, unsigned int y, unsigned int color)
{
  LCD_Set_Windows(x, y, x, y);
  LCD_Write_Data_16Bit(color);
}

//draw a vertical line 
void Draw_Fast_VLine(unsigned int x, unsigned int y, unsigned int h,unsigned int color)
{
    unsigned int m;
    LCD_Set_Windows(x, y, x, y + h -1);
    SPI_Start_Write(); 
    LCD_DC_HIGH;
    for(m=0;m<h;m++)
    {
      spi_write_16bit(color);
    }
    SPI_End_Write();
}

void Draw_Circle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1= 0;
  int y1= radius;

  Draw_Pixel(x, y+radius,color);
  Draw_Pixel(x, y-radius,color);
  Draw_Pixel(x+radius, y,color);
  Draw_Pixel(x-radius, y,color);

  while (x1<y1) 
  {
      if (f >= 0) 
    {
          y1--;
          ddF_y += 2;
          f += ddF_y;
      }
      x1++;
      ddF_x += 2;
      f += ddF_x;
  
    Draw_Pixel(x + x1, y + y1,color);
    Draw_Pixel(x - x1, y + y1,color);
    Draw_Pixel(x + x1, y - y1,color);
    Draw_Pixel(x - x1, y - y1,color);
    Draw_Pixel(x + y1, y + x1,color);
    Draw_Pixel(x - y1, y + x1,color);
    Draw_Pixel(x + y1, y - x1,color);
    Draw_Pixel(x - y1, y - x1,color);
  }
}

//fill a circle
void Fill_Circle(unsigned int x, unsigned int y, unsigned int radius,unsigned int color)
{
  Draw_Fast_VLine(x, y-radius, 2*radius+1, color);
  Fill_Circle_Helper(x, y, radius, 3, 0, color);
}

//fill a semi-circle
void Fill_Circle_Helper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername,unsigned int delta,unsigned int color)
{
  int f     = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x     = 0;
  int y     = r;

  while (x<y) 
  {
      if (f >= 0) 
    {
          y--;
          ddF_y += 2;
          f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;

      if (cornername & 0x1) 
    {
          Draw_Fast_VLine(x0+x, y0-y, 2*y+1+delta, color);
          Draw_Fast_VLine(x0+y, y0-x, 2*x+1+delta, color);
      }
      if (cornername & 0x2) 
    {
          Draw_Fast_VLine(x0-x, y0-y, 2*y+1+delta, color);
          Draw_Fast_VLine(x0-y, y0-x, 2*x+1+delta, color);
      }
    }
}

void setup()
{
  pinMode(LCD_CS, OUTPUT);
  digitalWrite(LCD_CS, HIGH);
  pinMode(LCD_RST, OUTPUT);
  digitalWrite(LCD_RST, HIGH);    
  pinMode(LCD_DC, OUTPUT);
  digitalWrite(LCD_DC, HIGH);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  SPI_Init();
  Lcd_Init();
}

void loop()
{  
   int i=0;
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, RED);delay(500);
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, GREEN);delay(500);
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, BLUE);delay(500);
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, WHITE);delay(500);
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, BLACK);delay(500);
   for(i=0;i<14;i++)
   {
      Fill_Circle(119, 119, 120-i*9,random(65535));
   }
   delay(1500);
   LCD_Clear_Screen(0, 0, LCD_WIDTH, LCD_HEIGHT, BLACK);
  for(i=1;i<14;i++)
  {
    Draw_Circle(119,119,i*9,random(65535));
  }
  delay(1500);
//  LCD_Clear(0xf800);
}
