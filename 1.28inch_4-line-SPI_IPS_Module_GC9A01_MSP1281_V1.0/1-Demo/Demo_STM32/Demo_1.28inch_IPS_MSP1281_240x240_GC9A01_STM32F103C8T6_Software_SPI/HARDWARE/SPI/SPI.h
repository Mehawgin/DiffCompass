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
#include "sys.h"

#ifndef _SPI_H_
#define _SPI_H_




//�����Գ���ʹ�õ���ģ��SPI�ӿ�����

#define LCD_CTRL   	  	GPIOA		//����TFT���ݶ˿�
#define SPI_SCLK        GPIO_Pin_5	//PA5--->>TFT --SCL/SCK
#define SPI_MOSI        GPIO_Pin_7	//PA7 MOSI--->>TFT --SDA/DIN

//Һ�����ƿ���1�������궨��

#define	SPI_MOSI_SET  	LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	LCD_CTRL->BSRR=SPI_SCLK    


//Һ�����ƿ���0�������궨��

#define	SPI_MOSI_CLR  	LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	LCD_CTRL->BRR=SPI_SCLK    

void SPI_WriteByte(u8 Data);
void SPI_GPIO_Init(void);

#endif
