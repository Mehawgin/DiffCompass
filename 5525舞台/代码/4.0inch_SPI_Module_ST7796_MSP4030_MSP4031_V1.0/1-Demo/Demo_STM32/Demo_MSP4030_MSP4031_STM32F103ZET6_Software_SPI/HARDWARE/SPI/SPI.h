//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103ZET6,����ԭ��ELITE STM32������,��Ƶ72MHZ������12MHZ
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
//    SDI(MOSI)      ��          PB15         //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PB14         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       LED         ��          PB9          //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK         ��          PB13         //Һ����SPI����ʱ���ź�
//     LCD_RS        ��          PB10         //Һ��������/��������ź�
//     LCD_RST       ��          PB12         //Һ������λ�����ź�
//     LCD_CS        ��          PB11         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ�� 
//     CTP_INT       ��          PC10         //���ݴ������ж��ź�
//     CTP_SDA       ��          PC3          //���ݴ�����IIC�����ź�
//     CTP_RST       ��          PC13         //���ݴ�������λ�ź�
//     CTP_SCL       ��          PC0          //���ݴ�����IICʱ���ź�
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
#include "sys.h"

#ifndef _SPI_H_
#define _SPI_H_

//�����Գ���ʹ�õ������SPI�ӿ�����
//SPI��ʱ�����Ŷ���ΪPB13
//SPI�Ķ��������Ŷ���ΪPB14
//SPI��д�������Ŷ���ΪPB15

#define SPI_GPIO  GPIOB
#define SPI_SCLK  13
#define SPI_MISO  14
#define SPI_MOSI  15

//SPI����
//GPIO��λ�����ߣ�
#define	SPI_SCLK_SET  SPI_GPIO->BSRR=1<<SPI_SCLK    		  
#define	SPI_MOSI_SET	SPI_GPIO->BSRR=1<<SPI_MOSI  		  

//GPIO��λ�����ͣ�							    
#define	SPI_SCLK_CLR  SPI_GPIO->BRR=1<<SPI_SCLK       	 
#define	SPI_MOSI_CLR	SPI_GPIO->BRR=1<<SPI_MOSI    

#define SPI_MISO_READ ((SPI_GPIO->IDR&(1<<SPI_MISO))?1:0)	  
 
void SPI_WriteByte(u8 Byte);
u8 SPI_ReadByte(void);
void SPI_GPIO_Init(void);

#endif
