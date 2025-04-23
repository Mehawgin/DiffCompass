//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ���������������ҵ��;
//����Ӳ������Ƭ��STM32F103C8T6,F103C8T6���Ŀ�����,��Ƶ72MHZ������8MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//Chan@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//wiki����������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-21077707 
//�ֻ�: (����)18823372746 ������)15989313508
//����:(����/����) sales@qdtft.com  (�ۺ�/��������)service@qdtft.com
//QQ:(��ǰ��ѯ)3002706772 (����֧��)3002778157
//��������QQȺ:778679828
//��������:2020/05/07
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      VCC          ��          3.3V         //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ4����SPI����
//     LCDģ��                STM32��Ƭ��    
//       SDA         ��          PA7         //Һ����SPI��������д�ź�
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       BLK         ��          PB6          //Һ������������źţ��������Ҫ���ƣ���3.3V
//       SCL         ��          PA5         //Һ����SPI����ʱ���ź�
//       DC          ��          PB7         //Һ��������/��������ź�
//       RES         ��          PB8         //Һ������λ�����ź�
//       CS          ��          PB9         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//ģ�鲻���������ܣ�����Ҫ���д���������
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/		
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "pic.h"
#include "ashin.h"


//========================variable==========================//
uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//������ɫ����
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/ 
void DrawTestPage(uint8_t *str)
{
//���ƹ̶���up
LCD_Clear(WHITE);
//LCD_Fill(0,0,lcddev.width,20,BLUE);
//���ƹ̶���down
//LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
//POINT_COLOR=BLUE;
if(lcddev.dir==0)
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-16,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(0,12,WHITE,BLUE,str,16,0);//������ʾ
	Gui_StrCenter(0,lcddev.height-16,WHITE,BLUE,"www.lcdwiki.com",16,0);//������ʾ
}
else if(lcddev.dir==2)
{
	LCD_Fill(0,0,lcddev.width-1,16,BLUE);
	LCD_Fill(0,lcddev.height-30,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(0,0,WHITE,BLUE,str,16,0);//������ʾ
	Gui_StrCenter(0,lcddev.height-30,WHITE,BLUE,"www.lcdwiki.com",16,0);//������ʾ
}
else if(lcddev.dir==1)
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-32,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(21,12,WHITE,BLUE,str,16,0);//������ʾ
	Gui_StrCenter(21,lcddev.height-32,WHITE,BLUE,"www.lcdwiki.com",16,0);//������ʾ
}
else
{
	LCD_Fill(0,0,lcddev.width-1,28,BLUE);
	LCD_Fill(0,lcddev.height-32,lcddev.width-1,lcddev.height-1,BLUE);
	Gui_StrCenter(-21,12,WHITE,BLUE,str,16,0);//������ʾ
	Gui_StrCenter(-21,lcddev.height-32,WHITE,BLUE,"www.lcdwiki.com",16,0);//������ʾ
}
//���Ʋ�������
//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Display_ButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-24 
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
 * @date       :2018-08-24 
 * @function   :Drawing a 3D menu UI
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void menu_test(void)
{
	LCD_Clear(GRAY0);
	
	Display_ButtonUp((lcddev.width-98)/2,65,(lcddev.width-98)/2+98,85); //x1,y1,x2,y2
	Gui_StrCenter(0,67,BRED,BLUE,"ͼ����ʾ����",16,1);

	Display_ButtonUp((lcddev.width-98)/2,95,(lcddev.width-98)/2+98,115); //x1,y1,x2,y2
	Gui_StrCenter(0,97,BLACK,GRAY0,"��ɫ������",16,1);
	
	Display_ButtonUp((lcddev.width-98)/2,125,(lcddev.width-98)/2+98,145); //x1,y1,x2,y2
	Gui_StrCenter(0,127,BLUE,GRAY0,"������ʾ����",16,1);

	Display_ButtonUp((lcddev.width-98)/2,155,(lcddev.width-98)/2+98,175); //x1,y1,x2,y2
	Gui_StrCenter(0,157,RED,GRAY0,"ͼƬ��ʾ����",16,1);
	delay_ms(1500);
	delay_ms(500);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	DrawTestPage("�ۺϲ��Գ���");	
	Gui_StrCenter(0,78,RED,BLUE,"ȫ������",16,1);//������ʾ
	Gui_StrCenter(0,95,RED,BLUE,"�ۺϲ��Գ���",16,1);//������ʾ	
	Gui_StrCenter(0,112,GREEN,BLUE,"0.96\" ST7796H2",16,1);//������ʾ
	Gui_StrCenter(0,129,GREEN,BLUE,"240X198",16,1);//������ʾ
	Gui_StrCenter(0,146,BLUE,BLUE,"2023-09-09",16,1);//������ʾ
	delay_ms(1500);		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09 
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	//DrawTestPage("����1:��ɫ������");
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
 * @date       :2018-08-09 
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
	DrawTestPage("GUI����������");
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
 * @date       :2018-08-09 
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
	DrawTestPage("GUI��Բ������");
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
 * @date       :2018-08-09 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
	DrawTestPage("Ӣ����ʾ����");
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
 * @date       :2018-08-09 
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
	DrawTestPage("GUI Tri������");
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
 * @date       :2018-08-09 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{	
	DrawTestPage("������ʾ����");
	Show_Str(45,82,BLUE,YELLOW,"16X16:ȫ�����ӻ�ӭ",16,0);
	Show_Str(45,102,BLUE,YELLOW,"24X24:���Ĳ���",24,1);
	Show_Str(45,127,BLUE,YELLOW,"32X32:�������",32,1);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09 
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
	/*
	DrawTestPage("ͼƬ��ʾ����");
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(50,90,40,40,gImage_qq);
	Show_Str(50+12,135,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(100,90,40,40,gImage_qq);
	Show_Str(100+12,135,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,90,40,40,gImage_qq);
	Show_Str(150+12,135,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
	*/
	//DrawTestPage("ͼƬ��ʾ����");
	LCD_Fill(0,0,lcddev.width,lcddev.height,BLACK);
	Gui_Drawbmp16(50,90,95,77,gImage_ashin_eye);
	//Gui_Drawbmp16(0,0,40,40,gImage_ashin_stm32);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09 
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
	DrawTestPage("��Ļ��ת����");
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
	DrawTestPage("��̬������ʾ");
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
