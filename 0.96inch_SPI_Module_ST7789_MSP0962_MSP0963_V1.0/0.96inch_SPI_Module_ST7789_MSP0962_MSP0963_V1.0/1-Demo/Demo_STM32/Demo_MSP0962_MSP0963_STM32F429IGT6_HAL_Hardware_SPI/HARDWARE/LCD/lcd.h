//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F429IGT6,正点原子Apollo STM32F4/F7开发板,主频180MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/08/22
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接          3.3V         //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI总线
//     LCD模块                STM32单片机    
//       SDA         接          PF9          //液晶屏SPI总线数据写信号
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机 
//       BLK         接          PD6          //液晶屏背光控制信号，如果不需要控制，接3.3V
//       SCL         接          PF7          //液晶屏SPI总线时钟信号
//       DC          接          PD5          //液晶屏数据/命令控制信号
//       RES         接          PD12         //液晶屏复位控制信号
//       CS          接          PD11         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//模块不带触摸功能，不需要进行触摸屏接线
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

//LCD重要参数集
typedef struct  
{										    
	uint16_t width;			//LCD 宽度
	uint16_t height;			//LCD 高度
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t	 wramcmd;		//开始写gram指令
	uint16_t  setxcmd;		//设置x坐标指令
	uint16_t  setycmd;		//设置y坐标指令	 
	uint8_t   xoffset;    
  uint8_t	 yoffset;	
}_lcd_dev; 	

//刷新缓冲区buf大小
#define BUF_SIZE   10*1024

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 240
#define LCD_H 198

//TFTLCD部分外要调用的函数		   
extern uint16_t  POINT_COLOR;//默认红色    
extern uint16_t  BACK_COLOR; //背景颜色，默认为白色

////////////////////////////////////////////////////////////////////
/*-----------------LCD端口定义----------------*/ 
//BL引脚定义
#define LCD_BL_PORT   GPIOD        
#define LCD_BL_PIN    GPIO_PIN_6   //背光控制引脚       PB6

//CS引脚定义
#define LCD_CS_PORT   GPIOD  
#define LCD_CS_PIN    GPIO_PIN_11   //片选引脚            PB9

//RS引脚定义
#define LCD_RS_PORT   GPIOD  
#define LCD_RS_PIN    GPIO_PIN_5   //寄存器/数据选择引脚 PB7 

//RST引脚定义
#define LCD_RST_PORT  GPIOD  
#define LCD_RST_PIN   GPIO_PIN_12   //复位引脚            PB8

////////////////////////////////////////////////////////////////////
/*-----------------LCD端口控制定义----------------*/ 
//QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度
//直接操作寄存器可以提高LCD刷屏速率
//GPIO置位（拉高）
#define LCD_BL_SET  LCD_BL_PORT->BSRR=LCD_BL_PIN     //BL引脚拉高
#define	LCD_CS_SET  LCD_CS_PORT->BSRR=LCD_CS_PIN     //CS引脚拉高 	
#define	LCD_RS_SET	LCD_RS_PORT->BSRR=LCD_RS_PIN     //RS引脚拉高 	  
#define	LCD_RST_SET	LCD_RST_PORT->BSRR=LCD_RST_PIN   //RST引脚拉高	  

//GPIO复位（拉低）
#define LCD_BL_CLR  LCD_BL_PORT->BSRR=(uint32_t)LCD_BL_PIN<<16U		 //BL引脚拉低				    
#define	LCD_CS_CLR  LCD_CS_PORT->BSRR=(uint32_t)LCD_CS_PIN<<16U      //CS引脚拉低  	
#define	LCD_RS_CLR	LCD_RS_PORT->BSRR=(uint32_t)LCD_RS_PIN<<16U      //RS引脚拉低  	 
#define	LCD_RST_CLR	LCD_RST_PORT->BSRR=(uint32_t)LCD_RST_PIN<<16U    //RST引脚拉低  
		  
//画笔颜色
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
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
#define GRAY0       0xEF7D 
#define GRAY1       0x8410      	//灰色1      00000 000000 00000
#define GRAY2       0x4208 
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);	 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);//画点
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
	 
	 



