// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of how to display picture and 
//how to use rotate function to display string.

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
#include "pic.h"
//#include "monster.h"
//#include "Stone.h"
//#include "Masa.h"
//#include "Ming.h"

//#include "ashin_nod.h"

TFT_eSPI mylcd = TFT_eSPI(); 

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MONSTER   0xD9C4
#define ASHIN     0xE374
#define STONE     0x1D47
#define MASA      0xF667
#define MING      0x2D3C


//clear screen
void fill_screen_test()
{
  mylcd.fillScreen(BLACK);delay(500);  
  mylcd.fillScreen(RED);delay(500); 
  mylcd.fillScreen(GREEN);delay(500); 
  mylcd.fillScreen(BLUE);delay(500); 
  mylcd.fillScreen(BLACK);delay(500); 
}

/********************************************************************************/
/********************************************************************************/
/*************************************阿信***************************************/
/********************************************************************************/
/********************************************************************************/
void pic_display()
{

  mylcd.setSwapBytes(true);
  mylcd.pushImage(0, 0, 240, 198, HAO001);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO002);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO003);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO004);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO005);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO006);
  delay(50);
  mylcd.pushImage(0, 0, 240, 198, HAO007);
  delay(50);

}

//display some strings
void text_test()
{
  mylcd.fillScreen(BLACK);  
  mylcd.setTextColor(WHITE);
  mylcd.drawString("         ::::::::::'.d$N.^''...:::db.^':::::::::::", 0,40,1);
  mylcd.drawString("        .::::::::: *#':::::::::'z$$$$$bo.'''::::::", 0,48,1);
  mylcd.drawString("        :::::::''..-:::::::: 'u$$$$$$$$$$$$bu ':::", 0,56,1);
  mylcd.drawString("       ::::::'.::::::::::'.ud$$$$$$$$$$$$$$$$$  :'", 0,64,1);
  mylcd.drawString("       ::::: ::::::::'.ud$$$$$$$$$$$$$$$$&eeuJ> :", 0,72,1);
  mylcd.drawString("     . '::::::::::: xd$$$$R'Lued$$$$$$$$$$$$$$>.:", 0,80,1);
  mylcd.drawString("   ::::.::::::::::. 9$$$$Fz$$$$$$$$$$$$$$$$F'' .:", 0,88,1);
  mylcd.drawString("  ::::::::::::::::::''$$$$u$$$F' ''$$$$$$$$.ut  '::", 0,96,1);
  mylcd.drawString("  :::::::::::::::::::''$$$$$FsKxL. 9$$$$$$$edNeo :::", 0,104,1);
  mylcd.drawString("  :::::::::::::::::::'$$$$$FsKxL. 9$$$$$$$edNeo :::", 0,112,1);
  mylcd.drawString("   ':::::::::::::::::: 4$$$$$b$euud$$$$$$$$$$$$$  : %%%", 0,120,1);
  mylcd.drawString("%: '::: :::::::::::::: $$$$$$$$$$$$$$$$$$?$$$$$>  %%%%", 0,128,1);
  mylcd.drawString("%%%     ::::::::::::: .$$$$$$$$$$$$$$$$I$u$$$$$> %%%%", 0,136,1);
  mylcd.drawString("%%%%%:  ::::::::::::' d$$$$$$$$$$$$$$$R?????'7$$F %%%%", 0,144,1);
  mylcd.drawString(" %%%%%%  ::::::::::'.$$$$$$$$$$$$$b.-m$$* d$$F %%%", 0,152,1);
  mylcd.drawString("   %%%%%.  :::::::: t$$$$$$$$$$$$$$$bu..o$$$'.%%", 0,160,1);
  mylcd.drawString("   '%%%%%%%.   :::: '$$$$$$$$$$$$$$$$$$$$$F':%%", 0,168,1);
  mylcd.drawString("   's.'%%%%%%%%%::.  $$$$$$$$o.''???$$R?F.:%%%", 0,176,1);
  mylcd.drawString("     '$eu  %%%%%%%% '$$$$$$$$$$$$er /%%%%%%%", 0,184,1);
  mylcd.drawString("       '?$$eu.  %%% t$$$$$$$$$$$$$! %%%%%%%%", 0,192,1);
  /*
  mylcd.drawString("Hello World!", 50,200,1);
  mylcd.drawString("Hello World!", 50,208,1);
  mylcd.drawString("Hello World!", 50,216,1);
*/
  /*
  mylcd.setTextColor(YELLOW);
  mylcd.drawFloat(1234.56, 3, 50, 48,2);

  mylcd.setTextColor(RED);
  mylcd.drawNumber(0xDEADBEF, 50, 64,4);

  mylcd.setTextColor(BLUE);
  mylcd.drawString("apmp", 50,76,6);
  mylcd.setTextColor(GREEN);
  mylcd.drawString("I implore", 50,122,2);

  mylcd.drawString("my foonting turling.", 50, 138,1);
  mylcd.drawString("And hooptiously me", 50, 146,1);
  mylcd.drawString("with crinkly bindle,", 50, 154,1);
  mylcd.drawString("Or I will rend thee", 50, 162,1);
  */
}

//draw some oblique lines
void lines_test(void)
{
    int i=0;
    mylcd.fillScreen(BLACK); 
    for(i = 0; i< mylcd.width();i+=5)
    {
       mylcd.drawLine(0, 0, i, mylcd.height()-1,GREEN);
     }
     for(i = mylcd.height()-1; i>= 0;i-=5)
     {
       mylcd.drawLine(0, 0, mylcd.width()-1, i,GREEN);
     }
     delay(500);
     mylcd.fillScreen(BLACK); 
    for(i = mylcd.width() -1; i>=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, 0, i, mylcd.height()-1,RED);
     }
    for(i = mylcd.height()-1; i>=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, 0, 0, i,RED);
     }
     delay(500);
     mylcd.fillScreen(BLACK); 
     for(i = 0; i < mylcd.width();i+=5)
    {
      mylcd.drawLine(0, mylcd.height()-1, i, 0,GREEN);
     }
     for(i = 0; i < mylcd.height();i+=5)
    {
      mylcd.drawLine(0, mylcd.height()-1, mylcd.width()-1, i,GREEN);
     }
    delay(500);
      mylcd.fillScreen(BLACK); 
     for(i = mylcd.width()-1; i >=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, mylcd.height()-1, i, 0,YELLOW);
     }
     for(i = 0; i<mylcd.height();i+=5)
    {
      mylcd.drawLine(mylcd.width()-1, mylcd.height()-1, 0, i,YELLOW);
     }
     delay(500);
}

//draw some vertical lines and horizontal lines
void h_l_lines_test(void)
{
    int i=0;
    mylcd.fillScreen(BLACK);
    for(i =0;i<mylcd.height();i+=5)
    {
      mylcd.drawFastHLine(0,i,mylcd.width(),GREEN); 
      delay(5);
    }
     for(i =0;i<mylcd.width();i+=5)
    {
      mylcd.drawFastVLine(i,0,mylcd.height(),BLUE); 
           delay(5);
    }
}

//draw some rectangles
void rectangle_test(void)
{
  int i = 0;
   mylcd.fillScreen(BLACK);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.drawRect(i,(mylcd.height()-mylcd.width())/2+i+21,mylcd.width()-2*i-1,mylcd.width()-2*i,GREEN);  
        delay(5);
   }
}

//draw some filled rectangles
void fill_rectangle_test(void)
{
  int i = 0;
   mylcd.fillScreen(BLACK);
   mylcd.fillRect(0,(mylcd.height()-mylcd.width())/2+21,mylcd.width(),mylcd.width(),YELLOW);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.drawRect(i,(mylcd.height()-mylcd.width())/2+i+21,mylcd.width()-2*i,mylcd.width()-2*i,MAGENTA);  
        delay(5);
   }
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRect(i,(mylcd.height()-mylcd.width())/2+i+21,mylcd.width()-2*i,mylcd.width()-2*i,random(0xFFFF));  
        delay(5);
   }
}

//draw some filled circles
void fill_circles_test(void)
{
  int r=10,i=0,j=0;
   mylcd.fillScreen(BLACK);
  for(i=r;i<mylcd.width();i+=2*r)
  {
    for(j=r;j<mylcd.height();j+=2*r)
    {
      mylcd.fillCircle(i, j, r,MAGENTA);
    }
  }
}

//draw some circles
void circles_test(void)
{
  int r=10,i=0,j=0;
  for(i=0;i<mylcd.width()+r;i+=2*r)
  {
    for(j=0;j<mylcd.height()+r;j+=2*r)
    {
      mylcd.drawCircle(i, j+21, r,GREEN);
    }
  }  
}

//draw some triangles
void triangles_test(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
   for(i=0;i<mylcd.width()/2;i+=5)
   {
      mylcd.drawTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i+21,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i+21,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i+21,mylcd.color565(0, i+64, i+64));                   
   }
}

//draw some filled triangles
void fill_triangles_test(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
    for(i=mylcd.width()/2-1;i>0;i-=5)
   {
      mylcd.fillTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i+21,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i+21,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i+21,mylcd.color565(0, i+64, i+64));                   
      mylcd.fillTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i+21,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i+21,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i+21,mylcd.color565(i, 0, i));                   
   }
}

//draw some round rectangles
void round_rectangle(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
     for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRoundRect(i,(mylcd.height()-mylcd.width())/2+i+21,mylcd.width()-2*i,mylcd.width()-2*i,8,mylcd.color565(255-i,0,160-i));
        delay(5);
   } 
}

//draw some filled round rectangles
void fill_round_rectangle(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRoundRect(i,(mylcd.height()-mylcd.width())/2+i+21,mylcd.width()-2*i,mylcd.width()-2*i,8,mylcd.color565(255-i,160-i,0));
        delay(5);
   } 
}

void setup() 
{
  mylcd.init();
}

void loop() 
{
  mylcd.setRotation(0);
  //fill_screen_test();
  //delay(500);
  //text_test();

  /* MAYDAY 5525 */
  pic_display();
  //Monster_display();
  //Stone_display();
  //Masa_display();
  //Ming_display();

  //fill_rectangle_test();
  //delay(500);
  /*lines_test();
  delay(500);
  h_l_lines_test();
  delay(500);
  rectangle_test();
  delay(500);
  fill_rectangle_test();
  delay(500);
  fill_circles_test();
  delay(500);
  circles_test();
  delay(500);
  triangles_test();
  delay(500);
  fill_triangles_test();
  delay(500);
  round_rectangle();
  delay(500);
  fill_round_rectangle();
  delay(500);
 for(uint8_t rotation=0; rotation<4; rotation++) 
 {
    mylcd.setRotation(rotation);
    text_test();
    delay(1500);
 }*/
}
