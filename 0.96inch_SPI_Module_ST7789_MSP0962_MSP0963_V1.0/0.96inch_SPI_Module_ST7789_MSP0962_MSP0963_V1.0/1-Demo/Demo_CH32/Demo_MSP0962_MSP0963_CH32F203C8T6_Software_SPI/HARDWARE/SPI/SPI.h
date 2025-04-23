//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ���������������ҵ��;
//����Ӳ������Ƭ��CH32F203C8T6,F203C8T6��Сϵͳ������,��Ƶ144MHZ������8MHZ
//QDtech-TFTҺ������ for CH32 IOģ��
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
//     LCDģ��                CH32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                CH32��Ƭ��    
//       SDA         ��          PA7         //Һ����SPI��������д�ź�
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      CH32��Ƭ�� 
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
#include "debug.h"	

#ifndef _SPI_H_
#define _SPI_H_

//�����Գ���ʹ�õ������SPI�ӿ�����
//SPI��ʱ�����Ŷ���ΪPA5
//SPI�Ķ��������Ŷ���ΪPA6
//SPI��д�������Ŷ���ΪPA7

#define SPI_GPIO  GPIOA
#define SPI_SCLK  5
#define SPI_MOSI  7

//SPI����
//GPIO��λ�����ߣ�
#define	SPI_SCLK_SET  SPI_GPIO->BSHR=1<<SPI_SCLK    		  
#define	SPI_MOSI_SET	SPI_GPIO->BSHR=1<<SPI_MOSI  		  

//GPIO��λ�����ͣ�							    
#define	SPI_SCLK_CLR  SPI_GPIO->BCR=1<<SPI_SCLK       	 
#define	SPI_MOSI_CLR	SPI_GPIO->BCR=1<<SPI_MOSI    

void SPI_WriteByte(u8 Byte);
void SPI_GPIO_Init(void);

#endif
