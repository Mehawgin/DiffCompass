//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ���������������ҵ��;
//����Ӳ������Ƭ��STM32F103C8T6,F103C8T6���Ŀ�����,��Ƶ72MHZ������8MHZ
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
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                STM32��Ƭ��    
//    SDI(MOSI)      ��          PA7          //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PA6          //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       LED         ��          PB6          //Һ������������źţ��������Ҫ���ƣ����Բ��ӣ�
//       SCK         ��          PA5          //Һ����SPI����ʱ���ź�
//      LCD_RS       ��          PB7          //Һ��������/��������ź�
//      LCD_RST      ��          PB8          //Һ������λ�����ź�
//      LCD_CS       ��          PB9          //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ�� 
//     CTP_INT       ��          PA8          //���ݴ����������ж��ź�
//     CTP_SDA       ��          PA9          //���ݴ�����IIC���������ź�
//     CTP_RST       ��          PA10         //���ݴ�����������λ�ź�
//     CTP_SCL       ��          PB5          //���ݴ�����IIC����ʱ���ź�
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
#include "spi.h"

/*****************************************************************************
 * @name       :void SPI_WriteByte(u8 Byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :SPIx: SPI type,x for 1,2,3
                Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
void SPI_WriteByte(u8 Byte)
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
		if(Byte&0x80)
		{
			SPI_MOSI_SET;
		}
		else
		{
			SPI_MOSI_CLR;
		}
		SPI_SCLK_CLR;
		SPI_SCLK_SET;
		Byte<<=1;
	}
} 


/*****************************************************************************
 * @name       :u8 SPI_ReadByte(void)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :SPIx: SPI type,x for 1,2,3
                Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
u8 SPI_ReadByte(void)
{
	u8 value=0,i=0,byte=0xFF;
	for(i=0;i<8;i++)
	{
		value<<=1;
		if(byte&0x80)
		{
			SPI_MOSI_SET;
		}
		else
		{
			SPI_MOSI_CLR;
		}
		byte<<=1;
		SPI_SCLK_CLR;
		if(SPI_MISO_READ)
		{
			value += 1;
		}
		SPI_SCLK_SET;	
	}
	return value;
} 

/*****************************************************************************
 * @name       :void SPI2_Init(void)	
 * @date       :2018-08-09 
 * @function   :Initialize the STM32 hardware SPI2
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI_GPIO_Init(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	//����SPI1�ܽ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
}
