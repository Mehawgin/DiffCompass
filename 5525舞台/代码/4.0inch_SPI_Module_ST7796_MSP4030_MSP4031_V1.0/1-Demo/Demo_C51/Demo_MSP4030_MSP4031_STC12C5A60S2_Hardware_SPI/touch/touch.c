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
#include <stddef.h>
#include "sys.h"
#include "touch.h"
#include "lcd.h"
#include "gui.h"

_m_tp_dev tp_dev=
{
	TP_Init,
	NULL,
	0,
	0,
 	0,	
};					
//Ĭ��Ϊtouchtype=0������.
 
/*****************************************************************************
 * @name       :u8 TP_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
								1-Has been calibrated
******************************************************************************/  
u8 TP_Init(void)
{			    		   
	if(FT6336_Init())
	{
		return 1;
	}
	tp_dev.scan=FT6336_Scan;	//ɨ�躯��ָ��GT911������ɨ��
	return 0;
}


