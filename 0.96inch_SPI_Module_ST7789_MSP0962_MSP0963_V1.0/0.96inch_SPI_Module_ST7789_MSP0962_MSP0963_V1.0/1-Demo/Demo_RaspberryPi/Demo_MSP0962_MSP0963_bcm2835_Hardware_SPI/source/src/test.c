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
//This program uses the bcm2835 gpio library,
//so the pin definition using BCM coding
//=====================================power supply wiring===========================================//
// OLED Module                Raspberry PI    
//    VCC        connect       DC 5V/3.3V      //LCD power positive, Physical pin 1,2,4,17
//    GND        connect          GND          //LCD power ground,Physical pin 6,9,14,20,25,30,34,39
//======================================data line wiring=============================================//
//The default data bus type for this module is 4-wire SPI
// OLED Module                Raspberry PI 
//    SDA        connect       19(bcm:10)      //LCD spi write signal
//======================================control line wiring==========================================//
// OLED Module                Raspberry PI 
//    RES        connect        5(bcm:3)       //LCD reset control signal
//    DC         connect        3(bcm:2)       //LCD data or command selection control signal
//    SCL        connect       23(bcm:11)      //LCD spi colck signal
//    CS         connect       24(bcm:8)       //LCD chip selection control signal
//    BLK        connect       12(bcm:18)      //LCD backlight control signal, if no control is needed, connect to 3.3V
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
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "pic.h"

//========================variable==========================//
uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(uint8_t *str)
 * @date       :2021-04-06 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/ 
void DrawTestPage(uint8_t *str)
{
//绘制固定栏up
LCD_Clear(WHITE);
//LCD_Fill(0,0,lcddev.width,20,BLUE);
//绘制固定栏down
//LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
//POINT_COLOR=BLUE;
if(lcddev.dir==0)
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-16,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(0,12,WHITE,BLUE,str,16,0);//居中显示
	Gui_StrCenter(0,lcddev.height-16,WHITE,BLUE,"www.lcdwiki.com",16,0);//居中显示
}
else if(lcddev.dir==2)
{
	LCD_Fill(0,0,lcddev.width-1,16,BLUE);
	LCD_Fill(0,lcddev.height-30,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(0,0,WHITE,BLUE,str,16,0);//居中显示
	Gui_StrCenter(0,lcddev.height-30,WHITE,BLUE,"www.lcdwiki.com",16,0);//居中显示
}
else if(lcddev.dir==1)
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-32,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(21,12,WHITE,BLUE,str,16,0);//居中显示
	Gui_StrCenter(21,lcddev.height-32,WHITE,BLUE,"www.lcdwiki.com",16,0);//居中显示
}
else
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-32,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(-21,12,WHITE,BLUE,str,16,0);//居中显示
	Gui_StrCenter(-21,lcddev.height-32,WHITE,BLUE,"www.lcdwiki.com",16,0);//居中显示
}
//绘制测试区域
//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Display_ButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
 * @date       :2021-04-06 
 * @function   :Drawing a 3D button
 * @parameters :x1:the bebinning x coordinate of the button
                y1:the bebinning y coordinate of the button
								x2:the ending x coordinate of the button
								y2:the ending y coordinate of the button
 * @retvalue   :None
******************************************************************************/ 
void Display_ButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	POINT_COLOR=WHITE;
	LCD_DrawLine(x1,  y1,  x2,y1); //H
	LCD_DrawLine(x1,  y1,  x1,y2); //V
	
	POINT_COLOR=GRAY1;
	LCD_DrawLine(x1+1,y2-1,x2,y2-1);  //H
	POINT_COLOR=GRAY2;
	LCD_DrawLine(x1,y2,x2,y2);  //H
	POINT_COLOR=GRAY1;
	LCD_DrawLine(x2-1,y1+1,x2-1,y2);  //V
	POINT_COLOR=GRAY2;
  LCD_DrawLine(x2,y1,x2,y2); //V
}

/*****************************************************************************
 * @name       :void menu_test(void)
 * @date       :2021-04-06 
 * @function   :Drawing a 3D menu UI
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void menu_test(void)
{
	LCD_Clear(GRAY0);
	
	Display_ButtonUp((lcddev.width-98)/2,65,(lcddev.width-98)/2+98,85); //x1,y1,x2,y2
	Gui_StrCenter(0,67,BRED,BLUE,"图形显示测试",16,1);

	Display_ButtonUp((lcddev.width-98)/2,95,(lcddev.width-98)/2+98,115); //x1,y1,x2,y2
	Gui_StrCenter(0,97,BLACK,GRAY0,"纯色填充测试",16,1);
	
	Display_ButtonUp((lcddev.width-98)/2,125,(lcddev.width-98)/2+98,145); //x1,y1,x2,y2
	Gui_StrCenter(0,127,BLUE,GRAY0,"中文显示测试",16,1);

	Display_ButtonUp((lcddev.width-98)/2,155,(lcddev.width-98)/2+98,175); //x1,y1,x2,y2
	Gui_StrCenter(0,157,RED,GRAY0,"图片显示测试",16,1);
	delay_ms(1500);
	delay_ms(500);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2021-04-06 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	DrawTestPage("综合测试程序");	
	Gui_StrCenter(0,78,RED,BLUE,"全动电子",16,1);//居中显示
	Gui_StrCenter(0,95,RED,BLUE,"综合测试程序",16,1);//居中显示	
	Gui_StrCenter(0,112,GREEN,BLUE,"0.96\" ST7796H2",16,1);//居中显示
	Gui_StrCenter(0,129,GREEN,BLUE,"240X198",16,1);//居中显示
	Gui_StrCenter(0,146,BLUE,BLUE,"2023-09-09",16,1);//居中显示
	delay_ms(1500);		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2021-04-06 
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	//DrawTestPage("测试1:纯色填充测试");
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,WHITE);
	Show_Str(40,30,BLACK,YELLOW,"WHITE",16,1);delay_ms(1000);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,BLACK);
	Show_Str(40,30,WHITE,YELLOW,"BLACK",16,1);delay_ms(1000);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,RED);
	Show_Str(40,30,BLUE,YELLOW,"RED",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,GREEN);
	Show_Str(40,30,BLUE,YELLOW,"GREEN",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,BLUE);
	Show_Str(40,30,RED,YELLOW,"BLUE",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,GRAY);
	Show_Str(40,30,RED,YELLOW,"GRAY",16,1);delay_ms(1000);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2021-04-06 
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
	uint8_t i=0;
	DrawTestPage("GUI矩形填充测试");
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawRectangle(lcddev.width/2-40+(i*16),lcddev.height/2-40+(i*13),lcddev.width/2-40+(i*16)+30,lcddev.height/2-40+(i*13)+30); 
	}
	delay_ms(1500);	
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawFillRectangle(lcddev.width/2-40+(i*16),lcddev.height/2-40+(i*13),lcddev.width/2-40+(i*16)+30,lcddev.height/2-40+(i*13)+30); 
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2021-04-06 
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	uint8_t i=0;
	DrawTestPage("GUI画圆填充测试");
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-40+(i*15),lcddev.height/2-25+(i*13),ColorTab[i],15,0);
	delay_ms(1500);	
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-40+(i*15),lcddev.height/2-25+(i*13),ColorTab[i],15,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2021-04-06 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
	DrawTestPage("英文显示测试");
	Show_Str(50,77,BLUE,YELLOW,"6X12:abcdefgh01234567",12,0);
	Show_Str(50,89,BLUE,YELLOW,"6X12:ABCDEFGH01234567",12,1);
	Show_Str(50,101,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:",12,0);
	Show_Str(50,114,BLUE,YELLOW,"8X16:abcde01234",16,0);
	Show_Str(50,130,BLUE,YELLOW,"8X16:ABCDE01234",16,1);
	Show_Str(50,146,BLUE,YELLOW,"8X16:~!@#$%^&*()",16,0); 
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2021-04-06 
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	uint8_t i=0;
	DrawTestPage("GUI Tri填充测试");
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Draw_Triangel(lcddev.width/2-40+(i*15),lcddev.height/2-12+(i*11),lcddev.width/2-25-1+(i*15),lcddev.height/2-12-26-1+(i*11),lcddev.width/2-10-1+(i*15),lcddev.height/2-12+(i*11));
	}
	delay_ms(1500);	
	LCD_Fill(0,30,lcddev.width-1,lcddev.height-32,WHITE);
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Fill_Triangel(lcddev.width/2-40+(i*15),lcddev.height/2-12+(i*11),lcddev.width/2-25-1+(i*15),lcddev.height/2-12-26-1+(i*11),lcddev.width/2-10-1+(i*15),lcddev.height/2-12+(i*11));
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2021-04-06 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{	
	DrawTestPage("中文显示测试");
	Show_Str(45,82,BLUE,YELLOW,"16X16:全动电子欢迎",16,0);
	Show_Str(45,102,BLUE,YELLOW,"24X24:中文测试",24,1);
	Show_Str(45,127,BLUE,YELLOW,"32X32:字体测试",32,1);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2021-04-06 
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
	DrawTestPage("图片显示测试");
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(50,90,40,40,gImage_qq);
	Show_Str(50+12,135,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(100,90,40,40,gImage_qq);
	Show_Str(100+12,135,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,90,40,40,gImage_qq);
	Show_Str(150+12,135,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2021-04-06 
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Rotate_Test(void)
{
	uint8_t i=0;
	uint8_t *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};
	
	for(i=0;i<4;i++)
	{
	LCD_direction(i);
	DrawTestPage("屏幕旋转测试");
	Show_Str(40,35,BLUE,YELLOW,Direction[i],16,1);
	Gui_Drawbmp16(40,55,40,40,gImage_qq);
	delay_ms(1000);delay_ms(1000);
	}
	LCD_direction(USE_HORIZONTAL);
}

/*****************************************************************************
 * @name       :void Test_Dynamic_Num(void)
 * @date       :2018-11-13 
 * @function   :Dynamic number test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Dynamic_Num(void)
{
		uint8_t i;
	DrawTestPage("动态数字显示");
	POINT_COLOR=BLUE;
	srand(123456);
	LCD_ShowString(40,100,16,"PM2.5:      ug/m3",1);
	LCD_ShowString(40,120,16,"  TEP:      C",1);
	POINT_COLOR=RED;
	for(i=0;i<15;i++)
	{
		LCD_ShowNum(90,100,rand()%10000,5,16);
		LCD_ShowNum(90,120,rand()%50,5,16);
		delay_ms(500);
	}
}
