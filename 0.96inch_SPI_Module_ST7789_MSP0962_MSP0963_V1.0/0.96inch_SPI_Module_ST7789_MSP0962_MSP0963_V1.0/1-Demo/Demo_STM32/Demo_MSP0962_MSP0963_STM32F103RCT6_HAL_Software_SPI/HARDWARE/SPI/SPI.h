//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
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
//       SDA         ��          PB15         //Һ����SPI��������д�ź�
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       BLK         ��          PB9          //Һ������������źţ��������Ҫ���ƣ���3.3V
//       SCL         ��          PB13         //Һ����SPI����ʱ���ź�
//       DC          ��          PB10         //Һ��������/��������ź�
//       RES         ��          PB12         //Һ������λ�����ź�
//       CS          ��          PB11         //Һ����Ƭѡ�����ź�
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

/*---------���SPI���Ŷ���-------------*/
//SCLK���Ŷ���
#define SPI_SCLK_PORT   GPIOB
#define SPI_SCLK_PIN    GPIO_PIN_13	//PA5--->>TFT --SCL/SCK

//MOSI���Ŷ���
#define SPI_MOSI_PORT   GPIOB
#define SPI_MOSI_PIN    GPIO_PIN_15	//PA7 MOSI--->>TFT --SDA/DIN

/*----------SPI���ſ���----------------*/
//����
#define	SPI_SCLK_SET  	SPI_SCLK_PORT->BSRR=SPI_SCLK_PIN    
#define	SPI_MOSI_SET  	SPI_MOSI_PORT->BSRR=SPI_MOSI_PIN    


//����
#define	SPI_SCLK_CLR  	SPI_SCLK_PORT->BRR=SPI_SCLK_PIN    
#define	SPI_MOSI_CLR  	SPI_MOSI_PORT->BRR=SPI_MOSI_PIN    

void SPI_WriteByte(uint8_t Data);
void SPI_GPIO_Init(void);

#endif
