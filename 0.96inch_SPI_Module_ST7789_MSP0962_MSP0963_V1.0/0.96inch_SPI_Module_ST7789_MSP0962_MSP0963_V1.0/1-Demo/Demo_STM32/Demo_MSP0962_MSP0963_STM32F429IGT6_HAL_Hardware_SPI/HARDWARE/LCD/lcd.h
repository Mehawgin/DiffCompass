//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F429IGT6,����ԭ��Apollo STM32F4/F7������,��Ƶ180MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/22
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
//       SDA         ��          PF9          //Һ����SPI��������д�ź�
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       BLK         ��          PD6          //Һ������������źţ��������Ҫ���ƣ���3.3V
//       SCL         ��          PF7          //Һ����SPI����ʱ���ź�
//       DC          ��          PD5          //Һ��������/��������ź�
//       RES         ��          PD12         //Һ������λ�����ź�
//       CS          ��          PD11         //Һ����Ƭѡ�����ź�
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
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

//LCD��Ҫ������
typedef struct  
{										    
	uint16_t width;			//LCD ���
	uint16_t height;			//LCD �߶�
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //���������������ƣ�0��������1��������	
	uint16_t	 wramcmd;		//��ʼдgramָ��
	uint16_t  setxcmd;		//����x����ָ��
	uint16_t  setycmd;		//����y����ָ��	 
	uint8_t   xoffset;    
  uint8_t	 yoffset;	
}_lcd_dev; 	

//ˢ�»�����buf��С
#define BUF_SIZE   10*1024

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת

//////////////////////////////////////////////////////////////////////////////////	  
//����LCD�ĳߴ�
#define LCD_W 240
#define LCD_H 198

//TFTLCD������Ҫ���õĺ���		   
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern uint16_t  BACK_COLOR; //������ɫ��Ĭ��Ϊ��ɫ

////////////////////////////////////////////////////////////////////
/*-----------------LCD�˿ڶ���----------------*/ 
//BL���Ŷ���
#define LCD_BL_PORT   GPIOD        
#define LCD_BL_PIN    GPIO_PIN_6   //�����������       PB6

//CS���Ŷ���
#define LCD_CS_PORT   GPIOD  
#define LCD_CS_PIN    GPIO_PIN_11   //Ƭѡ����            PB9

//RS���Ŷ���
#define LCD_RS_PORT   GPIOD  
#define LCD_RS_PIN    GPIO_PIN_5   //�Ĵ���/����ѡ������ PB7 

//RST���Ŷ���
#define LCD_RST_PORT  GPIOD  
#define LCD_RST_PIN   GPIO_PIN_12   //��λ����            PB8

////////////////////////////////////////////////////////////////////
/*-----------------LCD�˿ڿ��ƶ���----------------*/ 
//QDtechȫϵ��ģ������������ܿ��Ʊ��������û�Ҳ���Խ�PWM���ڱ�������
//ֱ�Ӳ����Ĵ����������LCDˢ������
//GPIO��λ�����ߣ�
#define LCD_BL_SET  LCD_BL_PORT->BSRR=LCD_BL_PIN     //BL��������
#define	LCD_CS_SET  LCD_CS_PORT->BSRR=LCD_CS_PIN     //CS�������� 	
#define	LCD_RS_SET	LCD_RS_PORT->BSRR=LCD_RS_PIN     //RS�������� 	  
#define	LCD_RST_SET	LCD_RST_PORT->BSRR=LCD_RST_PIN   //RST��������	  

//GPIO��λ�����ͣ�
#define LCD_BL_CLR  LCD_BL_PORT->BSRR=(uint32_t)LCD_BL_PIN<<16U		 //BL��������				    
#define	LCD_CS_CLR  LCD_CS_PORT->BSRR=(uint32_t)LCD_CS_PIN<<16U      //CS��������  	
#define	LCD_RS_CLR	LCD_RS_PORT->BSRR=(uint32_t)LCD_RS_PIN<<16U      //RS��������  	 
#define	LCD_RST_CLR	LCD_RST_PORT->BSRR=(uint32_t)LCD_RST_PIN<<16U    //RST��������  
		  
//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
#define GRAY0       0xEF7D 
#define GRAY1       0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2       0x4208 
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);	 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);//����
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);								    
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WR_DATA(uint8_t data);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);		   
uint16_t LCD_BGR2RGB(uint16_t c);
void LCD_SetParam(void);
void LCD_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction);
void LCD_Fill_Colors(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd,uint16_t *colors,uint8_t flag);
void LCD_Write_nData_8Bit(uint8_t *Data,uint32_t n);					  		 
#endif  
	 
	 



