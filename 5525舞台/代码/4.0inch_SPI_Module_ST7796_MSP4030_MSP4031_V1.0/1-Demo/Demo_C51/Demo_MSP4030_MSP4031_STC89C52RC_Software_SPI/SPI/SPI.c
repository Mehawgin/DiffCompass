//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STC89C52RC,����11.0592M  ��Ƭ��������ѹ5V
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
/*************************************************************************************************/
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/
#include "SPI.h"

/*****************************************************************************
 * @name       :void SPI_WriteByte(u8 byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using C51's Hardware SPI
 * @parameters :d:Data to be written
 * @retvalue   :None
******************************************************************************/
void SPI_WriteByte(u8 byte)
{		
	u8 i = 0;
	for(i=0;i<8;i++)
	{
		if(byte&(0x80>>i))
		{
			MOSI = 1;
		}
		else
		{
			MOSI = 0;
		}
		SCLK = 0;
		SCLK = 1;
	}
}
