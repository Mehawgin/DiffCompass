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
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
//#include "pic.h"
//#include "monster.h"
//#include "Stone.h"
//#include "Masa.h"
//#include "Ming.h"
#include "engine.h"
#include <Arduino.h>
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




struct Button 
{
	const uint8_t PIN;
	uint32_t numberKeyPresses;
	bool pressed;
};
 
Button button1 = {0, 0, false};
///********************************************************************************/
///********************************************************************************/
///*************************************怪兽***************************************/
///********************************************************************************/
///********************************************************************************/
//void Monster_display()
//{
//  int i;
//
//  /* 怪兽转场 */
//  for (i = 11; i >= 0 ; i--)
//  {
//    mylcd.drawRect(20*i, 0, 20, 198, MONSTER);
//    mylcd.fillRect(20*i, 0, 20, 198, MONSTER);
//    delay(10);
//  }
//
//  /* 怪兽眨眼 */
//  mylcd.setSwapBytes(true);
//  mylcd.fillScreen(MONSTER);
//  mylcd.pushImage(72, 70, 95, 77, Monster);
//  delay(500);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink1);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink2);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink4);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster);
//  delay(30);
//
//  /* 怪兽点头 */
//  for (i = 0; i < 2; i++)
//  {
//    mylcd.pushImage(72, 70, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 127, 240, 20, MONSTER);
//    mylcd.fillRect(0, 127, 240, 20, MONSTER);
//    mylcd.pushImage(72, 50, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 107, 240, 20, MONSTER);
//    mylcd.fillRect(0, 107, 240, 20, MONSTER);
//    mylcd.pushImage(72, 30, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 87, 240, 20, MONSTER);
//    mylcd.fillRect(0, 87, 240, 20, MONSTER);
//    mylcd.pushImage(72, 10, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 10, 240, 20, MONSTER);
//    mylcd.fillRect(0, 10, 240, 20, MONSTER);
//    mylcd.pushImage(72, 30, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 30, 240, 20, MONSTER);
//    mylcd.fillRect(0, 30, 240, 20, MONSTER);
//    mylcd.pushImage(72, 50, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 50, 240, 20, MONSTER);
//    mylcd.fillRect(0, 50, 240, 20, MONSTER);
//    mylcd.pushImage(72, 70, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 70, 240, 20, MONSTER);
//    mylcd.fillRect(0, 70, 240, 20, MONSTER);
//    mylcd.pushImage(72, 90, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 90, 240, 20, MONSTER);
//    mylcd.fillRect(0, 90, 240, 20, MONSTER);
//    mylcd.pushImage(72, 110, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 167, 240, 20, MONSTER);
//    mylcd.fillRect(0, 167, 240, 20, MONSTER);
//    mylcd.pushImage(72, 90, 95, 77, Monster);
//    delay(40);
//    mylcd.drawRect(0, 147, 240, 20, MONSTER);
//    mylcd.fillRect(0, 147, 240, 20, MONSTER);
//    mylcd.pushImage(72, 70, 95, 77, Monster);
//    delay(40);
//  }
//  delay(500);
//
//  /* 怪兽眨眼 */
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink1);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink2);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink4);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster_Blink3);
//  delay(30);
//  mylcd.pushImage(72, 70, 95, 77, Monster);
//  delay(30);
//  delay(1000);
//}





#define MAX_MODE_NUM 6
//
//
// 
//void IRAM_ATTR isr() 
//{
//	button1.numberKeyPresses++;
//	if (MAX_MODE_NUM < button1.numberKeyPresses)
//	{
//	  button1.numberKeyPresses = 0;
//	}
//	button1.pressed = true;
//	//mylcd.fillScreen(WHITE);
//	mylcd.pushImage(100, 91, 57, 107, Ding);
//	//delay(500);
//	//mylcd.fillScreen(BLACK); 
//}




void engine()
{
  int speed = 10;
	mylcd.setSwapBytes(true);
	mylcd.pushImage(0, 0, 240, 198, engine1);
	delay(speed);
	mylcd.pushImage(0, 0, 240, 198, engine2);
	delay(speed);
	mylcd.pushImage(0, 0, 240, 198, engine3);
	delay(speed);
	mylcd.pushImage(0, 0, 240, 198, engine4);
	delay(speed);
}





void setup() 
{
	mylcd.init();
	pinMode(button1.PIN, INPUT_PULLUP);
//	attachInterrupt(button1.PIN, isr, FALLING);
}
 
void loop() 
{

	engine();






		/* MAYDAY 5525 */
//	if (0 == button1.numberKeyPresses)
//	{
//		pic_display();
//	}
//	else if (1 == button1.numberKeyPresses)
//	{
//		Monster_display();
//	}
//	else if (2 == button1.numberKeyPresses)
//	{
//		Stone_display();
//	}
//	else if (3 == button1.numberKeyPresses)
//	{
//		Masa_display();
//	}
//	else if (4 == button1.numberKeyPresses)
//	{
//		Ming_display();
//	}
//	else if (5 == button1.numberKeyPresses)
//	{
//		pic_display();
//		Monster_display();
//		Stone_display();
//		Masa_display();
//		Ming_display();
//	}
//	else if (6 == button1.numberKeyPresses)
//	{
//		text_test();
//	}
//	//if (button1.pressed) 
//	{
//		//text_test();
//    //delay(500);
//		button1.pressed = false;
//	}
}




