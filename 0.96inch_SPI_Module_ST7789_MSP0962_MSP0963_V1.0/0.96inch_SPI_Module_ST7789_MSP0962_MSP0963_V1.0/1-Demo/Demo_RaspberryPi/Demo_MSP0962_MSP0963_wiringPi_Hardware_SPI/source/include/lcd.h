//////////////////////////////////////////////////////////////////////////////////////////////////////	 
//This program is for learning only,Not to be used for any other purpose 
//without the permission of the author
//Testing Hardware:Raspberry PI all series
//QDtech-LCD liquid crystal driver for Raspberry PI
//xiaofeng@ShenZhen QDtech co.,LTD
//Company Website:www.qdtft.com
//Taobao Website:http://qdtech.taobao.com
//wiki Technology Website:http://www.lcdwiki.com
//We provide technical support,Any technical questions are welcome to 
//exchange and study at any time
//Fixed telephone (fax):+86 0755-23594567 
//cell-phone:15989313508(Mr Feng)
//E-mail:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//Technical Support QQ:3002773612  3002778157
//Technical Exchange QQ group:324828016
//Date:2021/4/6
//Version:V1.0
//Copyright reserved, piracy must be investigated
//Copyright(C) ShenZhen QDtech co.,LTD 2018-2028
//All rights reserved
/****************************************************************************************************
//This program uses the wiringPi gpio library,
//so the pin definition using wiringPi coding
//=====================================power supply wiring===========================================//
// OLED Module                Raspberry PI    
//    VCC        connect       DC 5V/3.3V      //LCD power positive, Physical pin 1,2,4,17
//    GND        connect          GND          //LCD power ground,Physical pin 6,9,14,20,25,30,34,39
//======================================data line wiring=============================================//
//The default data bus type for this module is 4-wire SPI
// OLED Module                Raspberry PI 
//    SDA        connect       19(wiringPi:12)      //LCD spi write signal
//======================================control line wiring==========================================//
// OLED Module                Raspberry PI 
//    RES        connect        5(wiringPi:9)       //LCD reset control signal
//    DC         connect        3(wiringPi:8)       //LCD data or command selection control signal
//    SCL        connect       23(wiringPi:14)      //LCD spi colck signal
//    CS         connect       24(wiringPi:10)       //LCD chip selection control signal
//    BLK        connect       12(wiringPi:1)      //LCD backlight control signal, if no control is needed, connect to 3.3V
//========================================touch screen wiring========================================//
//This module has no touch function,so it don't need touch screen wiring
*****************************************************************************************************/	
/****************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************************************/		
#ifndef __LCD_H
#define __LCD_H		
#include <wiringPi.h>
#include "type.h"	 
#include "stdlib.h"

//LCD important parameter set
typedef struct  
{										    
	uint16_t width;			    //LCD width
	uint16_t height;			//LCD height
	uint16_t id;				//LCD ID
	uint8_t  dir;			    //Horizontal screen or vertical screen control: 0,Horizontal screen; 1,vertical screen.	
	uint16_t	 wramcmd;	    //Start writing gram instruction
	uint16_t  setxcmd;		    //Set X coordinate command
	uint16_t  setycmd;		    //Set Y coordinate command	
	uint8_t   xoffset;    
  	uint8_t	 yoffset;	
}_lcd_dev; 	

//LCD parameter
extern _lcd_dev lcddev;	//LCD important parameter
/////////////////////////////////////User configuration area///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //Define the clockwise rotation direction of LCD screen:
                               // 0-0 degree rotation, 1-90 degree rotation, 2-180 degree rotation, 3-270 degree rotation

//////////////////////////////////////////////////////////////////////////////////	  
//Define the size of the LCD
#define LCD_W 240   
#define LCD_H 198
	   
extern uint16_t  POINT_COLOR;//Default red    
extern uint16_t  BACK_COLOR; //Background color. The default is white

////////////////////////////////////////////////////////////////////
//-----------------LCD port definition---------------- 
#define LCD_LED  1         //LCD backlight control signal wiringPi:1
#define LCD_RS   8         //data or command selection control signal wiringPi:8 
#define LCD_RST  9         //reset control signal  wiringPi:9
#define LCD_CS   10        //chip selection control signal  wiringPi:10

//-----------------LCD module pin operation definition---------------- 
//Qdtech full series modules use triode to control the backlight on and off, 
//users can also connect PWM to adjust the backlight brightness
#define LCD_LED_SET  digitalWrite(LCD_LED,HIGH)
#define LCD_LED_CLR  digitalWrite(LCD_LED,LOW)

#define LCD_RS_SET   digitalWrite(LCD_RS,HIGH)
#define LCD_RS_CLR   digitalWrite(LCD_RS,LOW)

#define LCD_RST_SET  digitalWrite(LCD_RST,HIGH)
#define LCD_RST_CLR  digitalWrite(LCD_RST,LOW)

#define LCD_CS_SET   digitalWrite(LCD_CS,HIGH)
#define LCD_CS_CLR   digitalWrite(LCD_CS,LOW)

//color definition
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0XBC40 //brown
#define BRRED 		0XFC07 //Brownish red
#define GRAY  		0X8430 //grey
#define GRAY0       0xEF7D 
#define GRAY1       0x8410 //grey1     
#define GRAY2       0x4208 
#define DARKBLUE    0X01CF	//dark blue
#define LIGHTBLUE   0X7D7C	//wathet blue  
#define GRAYBLUE    0X5458 //dusty blue
#define LIGHTGREEN  0X841F // light green
#define LIGHTGRAY   0XEF5B //light gray(PANNEL)
#define LGRAY 		0XC618 //light gray(PANNEL)
#define LGRAYBLUE   0XA651 //Light grey blue (middle layer color)
#define LBBLUE      0X2B12 //Light brown blue (reverse color of selection item)

//---------------LCD module control function-----------------------    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);	 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); 
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
uint16_t LCD_RD_DATA(void);									    
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WR_DATA(uint8_t data);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);		   
uint16_t LCD_BGR2RGB(uint16_t c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction );

#endif  
	 
	 



