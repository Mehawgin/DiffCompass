//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STC12C5A60S2,����11.0592M  ��Ƭ��������ѹ5V
//QDtech-TFTҺ������ for C51
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
//��������:2018/7/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
//********************************************************************************
//=========================================��Դ����================================================//
//5V��DC 5V��Դ
//GND�ӵ�
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI
//Һ����ģ��              ��Ƭ��
// SDI(MOSI)      ��       P15       //SPIд�ź�
// SDO(MISO)      ��       P16       //SPI���źţ��������Ҫ�����ܣ��˹ܽſɲ���
//=======================================Һ���������߽���==========================================//
//Һ����ģ��              ��Ƭ��
//  LCD_CS        ��       P13       //Һ����Ƭѡ�����ź�
//  LCD_RST       ��       P33       //Һ������λ�����ź�
//  LCD_RS        ��       P12       //Һ��������/��������ź�
//  SCK           ��       P17       //SPIʱ���ź�
//  LED           ��       P32       //Һ������������źţ��������Ҫ���ƣ����Բ��ӣ�
//=========================================����������=========================================//
//��ʹ�ô�������ģ�鱾������������ɲ�����
//������ģ��              ��Ƭ��
//  CTP_SCL       ��       P36       //���ݴ�����IIC����ʱ���ź�
//  CTP_RST       ��       P37       //���ݴ�����������λ�ź�
//  CTP_SDA       ��       P34       //���ݴ�����IIC���������ź�
//  CTP_INT       ��       P35       //���ݴ����������ж��ź�
//**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/
#ifndef __CTPIIC_H
#define __CTPIIC_H
#include "sys.h"	    
  	   		   
sbit CTP_IIC_SCL = P3^6;  		 //IICʱ��
sbit CTP_IIC_SDA = P3^4;		   //IIC����

#define CTP_SDA_OUT() {P3M1 &= ~(1<<4);P3M0 &= ~(1<<4);}
#define CTP_SDA_IN()  {P3M1 |= (1<<4);P3M0 &= ~(1<<4);}

//IIC���в�������
void CTP_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CTP_IIC_Start(void);				//����IIC��ʼ�ź�
void CTP_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CTP_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CTP_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CTP_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CTP_IIC_Ack(void);					//IIC����ACK�ź�
void CTP_IIC_NAck(void);					//IIC������ACK�ź�

#endif







