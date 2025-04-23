//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC12C5A60S2,晶振30M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for C51
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
//创建日期:2018/8/22
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
//********************************************************************************
//=========================================电源接线================================================//
//VCC接DC 3.3V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI
//液晶屏模块            单片机
//  SDA          接       P15        //SPI写信号
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块            单片机
//  CS           接       P13       //片选信号
//  RES          接       P33       //复位信号
//  DC           接       P12       //数据/命令选择控制信号
//  SCL          接       P17       //SPI时钟信号
//  BLK          接       P32       //背光控制信号，如果不需要控制，接3.3V
//=========================================触摸屏接线=========================================//
//模块不带触摸功能，不需要进行触摸屏接线

#include "sys.h"
#include "lcd.h"

//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

/*****************************************************************************
 * @name       :void spi_write_byte(u8 d)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using C51's Software SPI
 * @parameters :d:Data to be written
 * @retvalue   :None
******************************************************************************/
void spi_write_byte(u8 d)
{
	u8 val=0x80;
	while(val)
	{
		if(d&val)
		{
			LCD_SDI = 1;
		}
		else
		{
			LCD_SDI = 0;
		}
		LCD_CLK = 0;
		LCD_CLK = 1;
		val>>=1;
	}
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 Reg)	 
{	
	LCD_RS=0;
	LCD_CS=0;
	spi_write_byte(Reg);
	LCD_CS=1;
} 

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
 void LCD_WR_DATA(u8 Data)
{
	LCD_RS=1;
	LCD_CS=0;
	spi_write_byte(Data);
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void LCD_WR_DATA_16Bit(u16 Data)
{
	LCD_CS=0;
	LCD_RS=1;
	spi_write_byte(Data>>8);
	spi_write_byte(Data);
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
{
  LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	u16 i,j;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
	LCD_CS=0;
	LCD_RS=1;
    for(i=0;i<lcddev.width;i++)
	 {
	  for (j=0;j<lcddev.height;j++)
	   	{
        	spi_write_byte(Color>>8);
			spi_write_byte(Color);
	    }

	  }
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetWindows(x,y,x,y);//设置光标位置 
	LCD_WR_DATA_16Bit(POINT_COLOR); 	    
} 	 

/*****************************************************************************
 * @name       :void LCD_Reset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_Reset(void)
{	
	LCD_RESET=0;
	delay_ms(20);
	LCD_RESET=1;
	delay_ms(20);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{
	LCD_Reset(); //初始化之前复位
//************* GC9A01初始化**********//	
 	LCD_WR_REG(0xEF);
	LCD_WR_REG(0xEB);
	LCD_WR_DATA(0x14); 
	
  LCD_WR_REG(0xFE);			 
	LCD_WR_REG(0xEF); 

	LCD_WR_REG(0xEB);	
	LCD_WR_DATA(0x14); 

	LCD_WR_REG(0x84);			
	LCD_WR_DATA(0x40); 

	LCD_WR_REG(0x85);			
	LCD_WR_DATA(0xFF); 

	LCD_WR_REG(0x86);			
	LCD_WR_DATA(0xFF); 

	LCD_WR_REG(0x87);			
	LCD_WR_DATA(0xFF);

	LCD_WR_REG(0x88);			
	LCD_WR_DATA(0x0A);

	LCD_WR_REG(0x89);			
	LCD_WR_DATA(0x21); 

	LCD_WR_REG(0x8A);			
	LCD_WR_DATA(0x00); 

	LCD_WR_REG(0x8B);			
	LCD_WR_DATA(0x80); 

	LCD_WR_REG(0x8C);			
	LCD_WR_DATA(0x01); 

	LCD_WR_REG(0x8D);			
	LCD_WR_DATA(0x01); 

	LCD_WR_REG(0x8E);			
	LCD_WR_DATA(0xFF); 

	LCD_WR_REG(0x8F);			
	LCD_WR_DATA(0xFF); 


	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x20);

	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x08);
	
	LCD_WR_REG(0x3A);			
	LCD_WR_DATA(0x05); 


	LCD_WR_REG(0x90);			
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x08); 

	LCD_WR_REG(0xBD);			
	LCD_WR_DATA(0x06);
	
	LCD_WR_REG(0xBC);			
	LCD_WR_DATA(0x00);	

	LCD_WR_REG(0xFF);			
	LCD_WR_DATA(0x60);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x04);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA(0x13);
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA(0x13);

	LCD_WR_REG(0xC9);			
	LCD_WR_DATA(0x22);

	LCD_WR_REG(0xBE);			
	LCD_WR_DATA(0x11); 

	LCD_WR_REG(0xE1);			
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0E);

	LCD_WR_REG(0xDF);			
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x0c);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0xF0);   
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x26);
 	LCD_WR_DATA(0x2A);

 	LCD_WR_REG(0xF1);    
 	LCD_WR_DATA(0x43);
 	LCD_WR_DATA(0x70);
 	LCD_WR_DATA(0x72);
 	LCD_WR_DATA(0x36);
 	LCD_WR_DATA(0x37);  
 	LCD_WR_DATA(0x6F);


 	LCD_WR_REG(0xF2);   
 	LCD_WR_DATA(0x45);
 	LCD_WR_DATA(0x09);
 	LCD_WR_DATA(0x08);
 	LCD_WR_DATA(0x08);
 	LCD_WR_DATA(0x26);
 	LCD_WR_DATA(0x2A);

 	LCD_WR_REG(0xF3);   
 	LCD_WR_DATA(0x43);
 	LCD_WR_DATA(0x70);
 	LCD_WR_DATA(0x72);
 	LCD_WR_DATA(0x36);
 	LCD_WR_DATA(0x37); 
 	LCD_WR_DATA(0x6F);

	LCD_WR_REG(0xED);	
	LCD_WR_DATA(0x1B); 
	LCD_WR_DATA(0x0B); 

	LCD_WR_REG(0xAE);			
	LCD_WR_DATA(0x77);
	
	LCD_WR_REG(0xCD);			
	LCD_WR_DATA(0x63);		


	LCD_WR_REG(0x70);			
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x0E); 
	LCD_WR_DATA(0x0F); 
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x03);

	LCD_WR_REG(0xE8);			
	LCD_WR_DATA(0x34);

	LCD_WR_REG(0x62);			
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x71);
	LCD_WR_DATA(0xED);
	LCD_WR_DATA(0x70); 
	LCD_WR_DATA(0x70);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x71);
	LCD_WR_DATA(0xEF);
	LCD_WR_DATA(0x70); 
	LCD_WR_DATA(0x70);

	LCD_WR_REG(0x63);			
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x71);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x70); 
	LCD_WR_DATA(0x70);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x71);
	LCD_WR_DATA(0xF3);
	LCD_WR_DATA(0x70); 
	LCD_WR_DATA(0x70);

	LCD_WR_REG(0x64);			
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);

	LCD_WR_REG(0x66);			
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xCD);
	LCD_WR_DATA(0x67);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x67);			
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x98);

	LCD_WR_REG(0x74);			
	LCD_WR_DATA(0x10);	
	LCD_WR_DATA(0x85);	
	LCD_WR_DATA(0x80);
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x4E);
	LCD_WR_DATA(0x00);					
	
  LCD_WR_REG(0x98);			
	LCD_WR_DATA(0x3e);
	LCD_WR_DATA(0x07);

	LCD_WR_REG(0x35);	
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11); 
	delay_ms(120); 

	LCD_WR_REG(0x29); 		

	//设置LCD属性参数
	LCD_direction(USE_HORIZONTAL);//设置LCD显示方向 
	LCD_BL=1;//点亮背光	 
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(yEnd);

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
	lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,1<<3);//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<5)|(1<<6)|(1<<3));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;			
			LCD_WriteReg(0x36,(1<<6)|(1<<7)|(1<<3));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<7)|(1<<5)|(1<<3));//BGR==1,MY==1,MX==0,MV==1
		break;	
		default:break;
	}		
}	 





