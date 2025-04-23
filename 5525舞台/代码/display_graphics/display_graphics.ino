// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of how to display picture and 
//how to use rotate function to display string.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                   CS  DC/RS  RESET  SDI/MOSI  SCK  SDO/MISO  LED    VCC     GND    
//ESP32-WROOM-32E:   15    2      27      13     14      12     21      5V     GND  

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
//#include "PlaneLeft.h"
//#include "PlaneRight.h"
#include "Plane_HZ.h"

// #define PLANE_HZ_LEFT
//#define PLANE_HZ_CENTER
 #define PLANE_HZ_RIGHT

#ifdef PLANE_HZ_LEFT
#define ROTATION 3
#define PLANE_IMAGE Plane_HZ_Left
#endif

#ifdef PLANE_HZ_CENTER
#define ROTATION 3
#define PLANE_IMAGE Plane_HZ_Center
#endif

#ifdef PLANE_HZ_RIGHT
#define ROTATION 1
#define PLANE_IMAGE Plane_HZ_Right
#endif


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


#define IN1 17
#define IN2 5
#define IN3 18
#define IN4 19
#define KEY 0
#define LED_BLUE 2

uint32_t delay_time = 1;


void step_change(int step)
{
  switch(step)
  {
    case 0: 
      digitalWrite(IN1, LOW );
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;

    case 1: 
      digitalWrite(IN1, LOW );
      digitalWrite(IN2, LOW );
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;

    case 2: 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW );
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;  

    case 3: 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW );
      digitalWrite(IN3, LOW );
      digitalWrite(IN4, HIGH);
      break; 

    case 4: 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW );
      digitalWrite(IN4, HIGH);
      break;  

    case 5: 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW );
      digitalWrite(IN4, LOW );
      break;

    case 6: 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW );
      break;  

    case 7: 
      digitalWrite(IN1, LOW );
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW );
      break; 

    case 8: 
      break;

  }
  delay(delay_time);
}

/* 初始化LED与按键管脚 */
void key_init()
{
	pinMode(LED_BLUE,OUTPUT);
//	设置KEY引脚为上拉输入
	pinMode(KEY,INPUT_PULLUP);
}

/* 按键扫描函数 */
void key_scan()
{  
  static bool state = 1;
  int i,j;
  if(digitalRead(KEY) == LOW)
  {
    //延时消抖
    delay(5);
    //如果仍为低电平，按键按下
    if(digitalRead(KEY) == LOW)
    {
      state = !state;
      if(state)
      {
        for (j = 0; j < 300; j++)
        {
          for(i = 0; i <= 7; i++)
          {
            step_change(i);
          }
        }
      }
      else
      {
        for (j = 0; j < 300; j++)
        {
          for(i = 7; i >= 0; i--)
          {
            step_change(i);
          }
        }
      }

      //每次按下，变换LED状态
      digitalWrite(LED_BLUE,!digitalRead(LED_BLUE));
      //等待按键松开
      while(digitalRead(KEY) == LOW);
    }
  }
} 


void setup() 
{
	mylcd.init();
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT); 
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);

	key_init();
}

void loop() 
{
	
	key_scan();
	mylcd.setRotation(ROTATION);
	mylcd.setSwapBytes(true);
    mylcd.pushImage(0, 0, 480, 320, PLANE_IMAGE);
	delay(5000);

}
