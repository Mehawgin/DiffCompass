#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "pic.h"
#include "monster.h"
#include "Stone.h"
#include "Masa.h"
#include "Ming.h"
#include "engine.h"
#include <Arduino.h>
//#include "ashin_nod.h"

TFT_eSPI mylcd = TFT_eSPI(); 

//define some colour values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


/* 五月天颜色数据 */
#define MONSTER   	0xD9C4
#define ASHIN     	0xE374
#define STONE     	0x1D47
#define MASA      	0xF667
#define MING      	0x2D3C

/* 表情位置 */
#define BASE_WIDTH 		72
#define BASE_HEIGHT 	80
/* 表情大小 */
#define FACE_WIDTH 		95
#define FACE_HEIGHT 	77


static bool first_time = 1;

struct Button 
{
	const uint8_t PIN;
	
	//0:Ashin 1:Monster 2:Stone 3:Masa 4:Ming
	uint32_t numberKeyPresses;
	bool pressed;
};
 
Button button1 = {9, 1, false};

#define MAX_MODE_NUM 6

//void IRAM_ATTR isr() 
//{
//	Serial.printf("botton pressed! \n\r");
//	button1.numberKeyPresses++;
//	if (MAX_MODE_NUM < button1.numberKeyPresses)
//	{
//	  button1.numberKeyPresses = 1;
//	}
//	button1.pressed = true;
//	first_time = 1;
//	mylcd.fillScreen(WHITE);
//	mylcd.pushImage(100, 91, 57, 107, Ding);
	//delay(500);
	//mylcd.fillScreen(BLACK); 

//
//	button1.numberKeyPresses = 1;
//
//}

void engine()
{
  int speed = 5;
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


/********************************************************************************/
/********************************************************************************/
/*************************************通用***************************************/
/********************************************************************************/
/********************************************************************************/
void Universal_display(int Mayday)
{
	int i;
	const unsigned short* Mayday_pic[5] = {0};

	if (MONSTER == Mayday)
	{
		Mayday_pic[0] = &Monster[0];
		Mayday_pic[1] = &Monster_Blink1[0];
		Mayday_pic[2] = &Monster_Blink2[0];
		Mayday_pic[3] = &Monster_Blink3[0];
		Mayday_pic[4] = &Monster_Blink4[0];
	}
	else if (STONE == Mayday)
	{
		Mayday_pic[0] = &Stone[0];
		Mayday_pic[1] = &Stone_Blink1[0];
		Mayday_pic[2] = &Stone_Blink2[0];
		Mayday_pic[3] = &Stone_Blink3[0];
		Mayday_pic[4] = &Stone_Blink4[0];
	}
	else if (MASA == Mayday)
	{
		Mayday_pic[0] = &Masa[0];
		Mayday_pic[1] = &Masa_Blink1[0];
		Mayday_pic[2] = &Masa_Blink2[0];
		Mayday_pic[3] = &Masa_Blink3[0];
		Mayday_pic[4] = &Masa_Blink4[0];
	}
	else if (MING == Mayday)
	{
		
		Mayday_pic[0] = &Ming[0];
		Mayday_pic[1] = &Ming_Blink1[0];
		Mayday_pic[2] = &Ming_Blink2[0];
		Mayday_pic[3] = &Ming_Blink3[0];
		Mayday_pic[4] = &Ming_Blink4[0];
	}

  if (first_time)
  {
    first_time = 0;
    /* 转场 */
    for (i = 11; i >= 0 ; i--)
    {
      mylcd.drawRect(20*i, 0, 20, 240, Mayday);
      mylcd.fillRect(20*i, 0, 20, 240, Mayday);
      delay(10);
    }
  }


	/* 眨眼 */
	mylcd.setSwapBytes(true);
	mylcd.fillScreen(Mayday);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
	delay(500);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[1]);
	delay(30);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[2]);
	delay(30);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[3]);
	delay(30);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[4]);
	delay(30);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[3]);
	delay(30);
	mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
	delay(30);

  /* 点头 */
	for (i = 0; i < 2; i++)
	{
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, FACE_HEIGHT + BASE_HEIGHT - 20, 240, 20, Mayday);
		mylcd.fillRect(0, FACE_HEIGHT + BASE_HEIGHT - 20, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT - 20, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, FACE_HEIGHT + BASE_HEIGHT - 40, 240, 20, Mayday);
		mylcd.fillRect(0, FACE_HEIGHT + BASE_HEIGHT - 40, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT - 40, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, FACE_HEIGHT + BASE_HEIGHT - 60, 240, 20, Mayday);
		mylcd.fillRect(0, FACE_HEIGHT + BASE_HEIGHT - 60, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT - 60, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, BASE_HEIGHT - 60, 240, 20, Mayday);
		mylcd.fillRect(0, BASE_HEIGHT - 60, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT - 40, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, BASE_HEIGHT - 40, 240, 20, Mayday);
		mylcd.fillRect(0, BASE_HEIGHT - 40, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT - 20, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, BASE_HEIGHT - 20, 240, 20, Mayday);
		mylcd.fillRect(0, BASE_HEIGHT - 20, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT -  0, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, BASE_HEIGHT, 240, 20, Mayday);
		mylcd.fillRect(0, BASE_HEIGHT, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT + 20, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, BASE_HEIGHT + 20, 240, 20, Mayday);
		mylcd.fillRect(0, BASE_HEIGHT + 20, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT + 40, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, FACE_HEIGHT + BASE_HEIGHT + 20, 240, 20, Mayday);
		mylcd.fillRect(0, FACE_HEIGHT + BASE_HEIGHT + 20, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT + 20, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
		mylcd.drawRect(0, FACE_HEIGHT + BASE_HEIGHT, 240, 20, Mayday);
		mylcd.fillRect(0, FACE_HEIGHT + BASE_HEIGHT, 240, 20, Mayday);
		mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT +  0, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
		delay(40);
	}
	delay(500);

  /* 眨眼 */
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[1]);
  delay(30);
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[2]);
  delay(30);
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[3]);
  delay(30);
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[4]);
  delay(30);
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[3]);
  delay(30);
  mylcd.pushImage(BASE_WIDTH, BASE_HEIGHT, FACE_WIDTH, FACE_HEIGHT, Mayday_pic[0]);
  delay(30);
  delay(1000);
}


/*********************************************************/
/********************* 按键扫描函数 ***********************/
/*********************************************************/
void key_scan()
{
	static bool direction = 0, Ispressed = 0;
	if(digitalRead(button1.PIN) == LOW)
	{
		//延时消抖
		delay(5);
		//如果仍为低电平，按键按下
		while(digitalRead(button1.PIN) == LOW)
		{		
			Serial.println("Botton_9 pressed！");
			button1.numberKeyPresses = 1;

			
			//等待按键松开
			//while(digitalRead(KEY_BOOT) == LOW);
		}

//		if (Ispressed)
//		{
//		 	Ispressed = 0;
//			direction = !direction;	
//		}
	}
}

void setup() 
{
	Serial.begin(115200);
	mylcd.init();
	pinMode(button1.PIN, INPUT_PULLUP);
//	attachInterrupt(button1.PIN, isr, FALLING);
}
 
void loop() 
{
	//Serial.printf("button1.numberKeyPresses[%d] \r\n", button1.numberKeyPresses);


	int dalay_s = 24,i = 0;;


	if (button1.numberKeyPresses)
	{
		mylcd.fillScreen(BLACK);
		for (i = 0; i < dalay_s; i++)
		{
			delay(1000);
			Serial.printf("[%d]s passed! \n\r", i);
		}
		button1.numberKeyPresses = 0;
	}
	engine();
	key_scan();

	
//	if (3 == button1.numberKeyPresses)
//	{
//		//pic_display();
//		engine();
//	}
//	else if (1 == button1.numberKeyPresses)
//	{
//		Universal_display(MONSTER);    
//	}
//	else if (5 == button1.numberKeyPresses)
//	{
//	//		Stone_display();
//		Universal_display(STONE);
//	}
//	else if (2 == button1.numberKeyPresses)
//	{
//	//		Masa_display();
//		Universal_display(MASA);
//	}
//	else if (4 == button1.numberKeyPresses)
//	{
//		Universal_display(MING);
//	//		Ming_display();
//	}
//	else if (6 == button1.numberKeyPresses)
//	{
//		//pic_display();
//		Universal_display(MONSTER);
//		first_time = 1;
//		Universal_display(STONE);
//		first_time = 1;
//		Universal_display(MASA);
//		first_time = 1;
//		Universal_display(MING);
//		first_time = 1;
//	}
//
//
//	if (button1.pressed) 
//	{
//		button1.pressed = false;
//	}
}




