//This application does not rely on any libraries and it is for GC9A01

//This program is a demo of clearing screen to display black,white,red,green,blue.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                  CS  A0/DC  RESET  SDA  SCK  LED    VCC     GND    
//Arduino Mega2560  A2   A3     A4    51   52   A0     5V      GND

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
#include <SPI.h>

#define LED   A0    
#define CS    A2        
#define RS    A3       
#define RESET A4

void Lcd_Writ_Bus(unsigned char d)
{
  SPI.transfer(d);
}

void Lcd_Write_Com(unsigned char VH)  
{   
  *(portOutputRegister(digitalPinToPort(RS))) &=  ~digitalPinToBitMask(RS);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS)))|=  digitalPinToBitMask(RS);//LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data(x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data(y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c); 							 
}

void SPI_Init(void)
{
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2); // 4 MHz (half speed)
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);  
}

void Lcd_Init(void)
{
  digitalWrite(RESET,HIGH);
  delay(5); 
  digitalWrite(RESET,LOW);
  delay(15);
  digitalWrite(RESET,HIGH);
  delay(15);
  
//GC9A01 Init
  digitalWrite(CS,LOW);  //CS
  
  Lcd_Write_Com(0xEF);
  Lcd_Write_Com(0xEB);
  Lcd_Write_Data(0x14); 
  
  Lcd_Write_Com(0xFE);      
  Lcd_Write_Com(0xEF); 

  Lcd_Write_Com(0xEB); 
  Lcd_Write_Data(0x14); 

  Lcd_Write_Com(0x84);     
  Lcd_Write_Data(0x40); 

  Lcd_Write_Com(0x85);     
  Lcd_Write_Data(0xFF); 

  Lcd_Write_Com(0x86);     
  Lcd_Write_Data(0xFF); 

  Lcd_Write_Com(0x87);     
  Lcd_Write_Data(0xFF);

  Lcd_Write_Com(0x88);     
  Lcd_Write_Data(0x0A);

  Lcd_Write_Com(0x89);     
  Lcd_Write_Data(0x21); 

  Lcd_Write_Com(0x8A);     
  Lcd_Write_Data(0x00); 

  Lcd_Write_Com(0x8B);     
  Lcd_Write_Data(0x80); 

  Lcd_Write_Com(0x8C);     
  Lcd_Write_Data(0x01); 

  Lcd_Write_Com(0x8D);     
  Lcd_Write_Data(0x01); 

  Lcd_Write_Com(0x8E);     
  Lcd_Write_Data(0xFF); 

  Lcd_Write_Com(0x8F);     
  Lcd_Write_Data(0xFF); 


  Lcd_Write_Com(0xB6);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x20);

  Lcd_Write_Com(0x36);
  Lcd_Write_Data(0x08);
  
  Lcd_Write_Com(0x3A);     
  Lcd_Write_Data(0x05); 


  Lcd_Write_Com(0x90);     
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x08); 

  Lcd_Write_Com(0xBD);     
  Lcd_Write_Data(0x06);
  
  Lcd_Write_Com(0xBC);     
  Lcd_Write_Data(0x00);  

  Lcd_Write_Com(0xFF);     
  Lcd_Write_Data(0x60);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0x04);

  Lcd_Write_Com(0xC3);     
  Lcd_Write_Data(0x13);
  Lcd_Write_Com(0xC4);     
  Lcd_Write_Data(0x13);

  Lcd_Write_Com(0xC9);     
  Lcd_Write_Data(0x22);

  Lcd_Write_Com(0xBE);     
  Lcd_Write_Data(0x11); 

  Lcd_Write_Com(0xE1);     
  Lcd_Write_Data(0x10);
  Lcd_Write_Data(0x0E);

  Lcd_Write_Com(0xDF);     
  Lcd_Write_Data(0x21);
  Lcd_Write_Data(0x0c);
  Lcd_Write_Data(0x02);

  Lcd_Write_Com(0xF0);   
  Lcd_Write_Data(0x45);
  Lcd_Write_Data(0x09);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x26);
  Lcd_Write_Data(0x2A);

  Lcd_Write_Com(0xF1);    
  Lcd_Write_Data(0x43);
  Lcd_Write_Data(0x70);
  Lcd_Write_Data(0x72);
  Lcd_Write_Data(0x36);
  Lcd_Write_Data(0x37);  
  Lcd_Write_Data(0x6F);


  Lcd_Write_Com(0xF2);   
  Lcd_Write_Data(0x45);
  Lcd_Write_Data(0x09);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x26);
  Lcd_Write_Data(0x2A);

  Lcd_Write_Com(0xF3);   
  Lcd_Write_Data(0x43);
  Lcd_Write_Data(0x70);
  Lcd_Write_Data(0x72);
  Lcd_Write_Data(0x36);
  Lcd_Write_Data(0x37); 
  Lcd_Write_Data(0x6F);

  Lcd_Write_Com(0xED); 
  Lcd_Write_Data(0x1B); 
  Lcd_Write_Data(0x0B); 

  Lcd_Write_Com(0xAE);     
  Lcd_Write_Data(0x77);
  
  Lcd_Write_Com(0xCD);     
  Lcd_Write_Data(0x63);    


  Lcd_Write_Com(0x70);     
  Lcd_Write_Data(0x07);
  Lcd_Write_Data(0x07);
  Lcd_Write_Data(0x04);
  Lcd_Write_Data(0x0E); 
  Lcd_Write_Data(0x0F); 
  Lcd_Write_Data(0x09);
  Lcd_Write_Data(0x07);
  Lcd_Write_Data(0x08);
  Lcd_Write_Data(0x03);

  Lcd_Write_Com(0xE8);     
  Lcd_Write_Data(0x34);

  Lcd_Write_Com(0x62);     
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x0D);
  Lcd_Write_Data(0x71);
  Lcd_Write_Data(0xED);
  Lcd_Write_Data(0x70); 
  Lcd_Write_Data(0x70);
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x0F);
  Lcd_Write_Data(0x71);
  Lcd_Write_Data(0xEF);
  Lcd_Write_Data(0x70); 
  Lcd_Write_Data(0x70);

  Lcd_Write_Com(0x63);     
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x11);
  Lcd_Write_Data(0x71);
  Lcd_Write_Data(0xF1);
  Lcd_Write_Data(0x70); 
  Lcd_Write_Data(0x70);
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x13);
  Lcd_Write_Data(0x71);
  Lcd_Write_Data(0xF3);
  Lcd_Write_Data(0x70); 
  Lcd_Write_Data(0x70);

  Lcd_Write_Com(0x64);     
  Lcd_Write_Data(0x28);
  Lcd_Write_Data(0x29);
  Lcd_Write_Data(0xF1);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0xF1);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x07);

  Lcd_Write_Com(0x66);     
  Lcd_Write_Data(0x3C);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0xCD);
  Lcd_Write_Data(0x67);
  Lcd_Write_Data(0x45);
  Lcd_Write_Data(0x45);
  Lcd_Write_Data(0x10);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);

  Lcd_Write_Com(0x67);     
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x3C);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0x54);
  Lcd_Write_Data(0x10);
  Lcd_Write_Data(0x32);
  Lcd_Write_Data(0x98);

  Lcd_Write_Com(0x74);     
  Lcd_Write_Data(0x10);  
  Lcd_Write_Data(0x85);  
  Lcd_Write_Data(0x80);
  Lcd_Write_Data(0x00); 
  Lcd_Write_Data(0x00); 
  Lcd_Write_Data(0x4E);
  Lcd_Write_Data(0x00);          
  
  Lcd_Write_Com(0x98);     
  Lcd_Write_Data(0x3e);
  Lcd_Write_Data(0x07);

  Lcd_Write_Com(0x35); 
  Lcd_Write_Com(0x21);

  Lcd_Write_Com(0x11);
  delay(120);
  Lcd_Write_Com(0x29);
  delay(20);
    digitalWrite(CS,HIGH);
}

void Draw_Pixel(unsigned int x, unsigned int y, unsigned int color)
{
    digitalWrite(CS,LOW);
  Address_set(x, y, x, y);
  Lcd_Write_Data(color>>8);
  Lcd_Write_Data(color);
  digitalWrite(CS,HIGH);
}

void Fill_Rect(unsigned int sx, unsigned int sy, unsigned int w, unsigned int h,unsigned int color)
{
    unsigned int i,m;
   unsigned int ex = w+sx-1;
    unsigned int ey = h+sy-1;
  digitalWrite(CS,LOW);
  Address_set(sx,sy,ex,ey);
  for(i=0;i<w;i++)
    for(m=0;m<h;m++)
    {
      Lcd_Write_Data(color>>8);
      Lcd_Write_Data(color);
    }
  digitalWrite(CS,HIGH);    
}

//draw a vertical line 
void Draw_Fast_VLine(unsigned int x, unsigned int y, unsigned int h,unsigned int color)
{
  Fill_Rect(x, y, 1, h, color);
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

void LCD_Clear(unsigned int j)                   
{	
  unsigned int i,m;
  digitalWrite(CS,LOW);
  Address_set(0,0,239,239);
  for(i=0;i<240;i++)
    for(m=0;m<240;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data(j);
    }
  digitalWrite(CS,HIGH);   
}

void setup()
{
  SPI_Init();
  pinMode(A0,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A2,OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A2, HIGH);

  Lcd_Init();
}

void loop()
{  
  int i=0;
   LCD_Clear(0xf800);delay(500);
   LCD_Clear(0x07E0);delay(500);
   LCD_Clear(0x001F);delay(500);
   LCD_Clear(0xFFFF);delay(500);
   LCD_Clear(0x0); delay(500);
   for(i=0;i<14;i++)
   {
      Fill_Circle(119, 119, 120-i*9,random(65535));
   }
   delay(1500);
   LCD_Clear(0x0);
  for(i=1;i<14;i++)
  {
    Draw_Circle(119,119,i*9,random(65535));
  }
  delay(1500);
//  LCD_Clear(0xf800);
}
