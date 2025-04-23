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
#include "monster.h"
#include "Stone.h"
#include "Masa.h"
#include "Ming.h"

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
/*************************************冠佑***************************************/
/********************************************************************************/
/********************************************************************************/
void Ming_display()
{
  int i;

  /* 冠佑转场 */
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, MING);
    mylcd.fillRect(20*i, 0, 20, 198, MING);
    delay(10);
  }

  /* 冠佑眨眼 */
  mylcd.setSwapBytes(true);
  mylcd.fillScreen(MING);
  mylcd.pushImage(72, 70, 95, 77, Ming);
  delay(500);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming);
  delay(30);

  /* 冠佑点头 */
  for (i = 0; i < 2; i++)
  {
    mylcd.pushImage(72, 70, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 127, 240, 20, MING);
    mylcd.fillRect(0, 127, 240, 20, MING);
    mylcd.pushImage(72, 50, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 107, 240, 20, MING);
    mylcd.fillRect(0, 107, 240, 20, MING);
    mylcd.pushImage(72, 30, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 87, 240, 20, MING);
    mylcd.fillRect(0, 87, 240, 20, MING);
    mylcd.pushImage(72, 10, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 10, 240, 20, MING);
    mylcd.fillRect(0, 10, 240, 20, MING);
    mylcd.pushImage(72, 30, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 30, 240, 20, MING);
    mylcd.fillRect(0, 30, 240, 20, MING);
    mylcd.pushImage(72, 50, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 50, 240, 20, MING);
    mylcd.fillRect(0, 50, 240, 20, MING);
    mylcd.pushImage(72, 70, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 70, 240, 20, MING);
    mylcd.fillRect(0, 70, 240, 20, MING);
    mylcd.pushImage(72, 90, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 90, 240, 20, MING);
    mylcd.fillRect(0, 90, 240, 20, MING);
    mylcd.pushImage(72, 110, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 167, 240, 20, MING);
    mylcd.fillRect(0, 167, 240, 20, MING);
    mylcd.pushImage(72, 90, 95, 77, Ming);
    delay(40);
    mylcd.drawRect(0, 147, 240, 20, MING);
    mylcd.fillRect(0, 147, 240, 20, MING);
    mylcd.pushImage(72, 70, 95, 77, Ming);
    delay(40);
  }
  delay(500);

  /* 冠佑眨眼 */
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Ming);
  delay(30);
  delay(1000);
}

/********************************************************************************/
/********************************************************************************/
/*************************************玛莎***************************************/
/********************************************************************************/
/********************************************************************************/
void Masa_display()
{
  int i;
  /* 玛莎转场 */
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, MASA);
    mylcd.fillRect(20*i, 0, 20, 198, MASA);
    delay(10);
  }

  /* 玛莎眨眼 */
  mylcd.setSwapBytes(true);
  mylcd.fillScreen(MASA);
  mylcd.pushImage(72, 70, 95, 77, Masa);
  delay(500);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa);
  delay(30);

  /* 玛莎点头 */
  for (i = 0; i < 2; i++)
  {
    mylcd.pushImage(72, 70, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 127, 240, 20, MASA);
    mylcd.fillRect(0, 127, 240, 20, MASA);
    mylcd.pushImage(72, 50, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 107, 240, 20, MASA);
    mylcd.fillRect(0, 107, 240, 20, MASA);
    mylcd.pushImage(72, 30, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 87, 240, 20, MASA);
    mylcd.fillRect(0, 87, 240, 20, MASA);
    mylcd.pushImage(72, 10, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 10, 240, 20, MASA);
    mylcd.fillRect(0, 10, 240, 20, MASA);
    mylcd.pushImage(72, 30, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 30, 240, 20, MASA);
    mylcd.fillRect(0, 30, 240, 20, MASA);
    mylcd.pushImage(72, 50, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 50, 240, 20, MASA);
    mylcd.fillRect(0, 50, 240, 20, MASA);
    mylcd.pushImage(72, 70, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 70, 240, 20, MASA);
    mylcd.fillRect(0, 70, 240, 20, MASA);
    mylcd.pushImage(72, 90, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 90, 240, 20, MASA);
    mylcd.fillRect(0, 90, 240, 20, MASA);
    mylcd.pushImage(72, 110, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 167, 240, 20, MASA);
    mylcd.fillRect(0, 167, 240, 20, MASA);
    mylcd.pushImage(72, 90, 95, 77, Masa);
    delay(40);
    mylcd.drawRect(0, 147, 240, 20, MASA);
    mylcd.fillRect(0, 147, 240, 20, MASA);
    mylcd.pushImage(72, 70, 95, 77, Masa);
    delay(40);
  }
  delay(500);

  /* 玛莎眨眼 */
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Masa);
  delay(30);
  delay(1000);
}

/********************************************************************************/
/********************************************************************************/
/*************************************石头***************************************/
/********************************************************************************/
/********************************************************************************/
void Stone_display()
{
  int i;

  /* 石头转场 */
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, STONE);
    mylcd.fillRect(20*i, 0, 20, 198, STONE);
    delay(10);
  }

  /* 石头眨眼 */
  mylcd.setSwapBytes(true);
  mylcd.fillScreen(STONE);
  mylcd.pushImage(72, 70, 95, 77, Stone);
  delay(500);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone);
  delay(30);

  /* 石头点头 */
  for (i = 0; i < 2; i++)
  {
    mylcd.pushImage(72, 70, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 127, 240, 20, STONE);
    mylcd.fillRect(0, 127, 240, 20, STONE);
    mylcd.pushImage(72, 50, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 107, 240, 20, STONE);
    mylcd.fillRect(0, 107, 240, 20, STONE);
    mylcd.pushImage(72, 30, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 87, 240, 20, STONE);
    mylcd.fillRect(0, 87, 240, 20, STONE);
    mylcd.pushImage(72, 10, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 10, 240, 20, STONE);
    mylcd.fillRect(0, 10, 240, 20, STONE);
    mylcd.pushImage(72, 30, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 30, 240, 20, STONE);
    mylcd.fillRect(0, 30, 240, 20, STONE);
    mylcd.pushImage(72, 50, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 50, 240, 20, STONE);
    mylcd.fillRect(0, 50, 240, 20, STONE);
    mylcd.pushImage(72, 70, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 70, 240, 20, STONE);
    mylcd.fillRect(0, 70, 240, 20, STONE);
    mylcd.pushImage(72, 90, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 90, 240, 20, STONE);
    mylcd.fillRect(0, 90, 240, 20, STONE);
    mylcd.pushImage(72, 110, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 167, 240, 20, STONE);
    mylcd.fillRect(0, 167, 240, 20, STONE);
    mylcd.pushImage(72, 90, 95, 77, Stone);
    delay(40);
    mylcd.drawRect(0, 147, 240, 20, STONE);
    mylcd.fillRect(0, 147, 240, 20, STONE);
    mylcd.pushImage(72, 70, 95, 77, Stone);
    delay(40);
  }
  delay(500);

  /* 石头眨眼 */
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Stone);
  delay(30);
  delay(1000);

}
/********************************************************************************/
/********************************************************************************/
/*************************************怪兽***************************************/
/********************************************************************************/
/********************************************************************************/
void Monster_display()
{
  int i;

  /* 怪兽转场 */
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, MONSTER);
    mylcd.fillRect(20*i, 0, 20, 198, MONSTER);
    delay(10);
  }

  /* 怪兽眨眼 */
  mylcd.setSwapBytes(true);
  mylcd.fillScreen(MONSTER);
  mylcd.pushImage(72, 70, 95, 77, Monster);
  delay(500);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster);
  delay(30);

  /* 怪兽点头 */
  for (i = 0; i < 2; i++)
  {
    mylcd.pushImage(72, 70, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 127, 240, 20, MONSTER);
    mylcd.fillRect(0, 127, 240, 20, MONSTER);
    mylcd.pushImage(72, 50, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 107, 240, 20, MONSTER);
    mylcd.fillRect(0, 107, 240, 20, MONSTER);
    mylcd.pushImage(72, 30, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 87, 240, 20, MONSTER);
    mylcd.fillRect(0, 87, 240, 20, MONSTER);
    mylcd.pushImage(72, 10, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 10, 240, 20, MONSTER);
    mylcd.fillRect(0, 10, 240, 20, MONSTER);
    mylcd.pushImage(72, 30, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 30, 240, 20, MONSTER);
    mylcd.fillRect(0, 30, 240, 20, MONSTER);
    mylcd.pushImage(72, 50, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 50, 240, 20, MONSTER);
    mylcd.fillRect(0, 50, 240, 20, MONSTER);
    mylcd.pushImage(72, 70, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 70, 240, 20, MONSTER);
    mylcd.fillRect(0, 70, 240, 20, MONSTER);
    mylcd.pushImage(72, 90, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 90, 240, 20, MONSTER);
    mylcd.fillRect(0, 90, 240, 20, MONSTER);
    mylcd.pushImage(72, 110, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 167, 240, 20, MONSTER);
    mylcd.fillRect(0, 167, 240, 20, MONSTER);
    mylcd.pushImage(72, 90, 95, 77, Monster);
    delay(40);
    mylcd.drawRect(0, 147, 240, 20, MONSTER);
    mylcd.fillRect(0, 147, 240, 20, MONSTER);
    mylcd.pushImage(72, 70, 95, 77, Monster);
    delay(40);
  }
  delay(500);

  /* 怪兽眨眼 */
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink1);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink2);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink4);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
  delay(30);
  mylcd.pushImage(72, 70, 95, 77, Monster);
  delay(30);
  delay(1000);
}

/********************************************************************************/
/********************************************************************************/
/*************************************阿信***************************************/
/********************************************************************************/
/********************************************************************************/
void ashin_display()
{
  int i;
  /* 阿信转场 */
  /*
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, ASHIN);
    mylcd.fillRect(20*i, 0, 20, 198, ASHIN);    
    delay(10);
  }*/

  mylcd.setSwapBytes(true);
  mylcd.fillScreen(ASHIN);

  //左边眼白
  mylcd.drawEllipse(90, 100, 20, 30, WHITE);
  mylcd.fillEllipse(90, 100, 20, 30, WHITE);

  //右边眼白
  mylcd.drawEllipse(150, 100, 20, 30, WHITE);
  mylcd.fillEllipse(150, 100, 20, 30, WHITE);

  //左边眼珠
  mylcd.drawCircle(95, 100, 15, 0x14FB);
  mylcd.fillCircle(95, 100, 15, 0x14FB);

  //右边眼珠
  mylcd.drawCircle(145, 100, 15, 0x14FB);
  mylcd.fillCircle(145, 100, 15, 0x14FB);

  //嘴巴
  mylcd.pushImage(100, 140, 46, 18, mouth);
  delay(5000);
}

void pic_display()
{
  int i = 0;
  //mylcd.setSwapBytes(true);

  /* 阿信转场 */
  for (i = 11; i >= 0 ; i--)
  {
    mylcd.drawRect(20*i, 0, 20, 198, ASHIN);
    mylcd.fillRect(20*i, 0, 20, 198, ASHIN);    
    delay(10);
  }

  /* 阿信眨眼 */
  mylcd.setSwapBytes(true);
  mylcd.pushImage(0, 0, 240, 198, ashin2);
  delay(500);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink1);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink2);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink3);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink4);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink3);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin2);
  delay(30);

  delay(500);

  /* 阿信点头 */
  for (i = 0; i < 2; i++)
  {
    mylcd.pushImage(0, 0, 240, 198, ashin_bg);
    mylcd.pushImage(0, 70, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 127, 240, 20, ashin_cover);
    mylcd.pushImage(0, 50, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 107, 240, 20, ashin_cover);
    mylcd.pushImage(0, 30, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 87, 240, 20, ashin_cover);
    mylcd.pushImage(0, 10, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 10, 240, 20, ashin_cover);
    mylcd.pushImage(0, 30, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 30, 240, 20, ashin_cover);
    mylcd.pushImage(0, 50, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 50, 240, 20, ashin_cover);
    mylcd.pushImage(0, 70, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 70, 240, 20, ashin_cover);
    mylcd.pushImage(0, 90, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 90, 240, 20, ashin_cover);
    mylcd.pushImage(0, 110, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 167, 240, 20, ashin_cover);
    mylcd.pushImage(0, 90, 240, 77, ashin_half);
    delay(30);
    mylcd.pushImage(0, 147, 240, 20, ashin_cover);
    mylcd.pushImage(0, 70, 240, 77, ashin_half);
    delay(30);
  }
  mylcd.pushImage(0, 0, 240, 198, ashin2);

  /* 阿信眨眼 */
  delay(500);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink1);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink2);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink3);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink4);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin_blink3);
  delay(30);
  mylcd.pushImage(0, 0, 240, 198, ashin2);
  delay(1000);

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
  //pic_display();
  ashin_display();
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
