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
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "gui.h"
#include "test.h"

int main(void)
{	
	HAL_Init();                          //��ʼ��HAL��
	sys_stm32_clock_init(RCC_PLL_MUL9);  //��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	delay_init(72);	                     //��ʱ��ʼ��
	LCD_Init();	                         //Һ������ʼ��
  //ѭ������
	while(1)
	{
		main_test(); 		//����������
		menu_test();     //3D�˵���ʾ����
		Test_Color();  		//��ˢ��������
		Test_FillRec();		//GUI���λ�ͼ����
		Test_Circle(); 		//GUI��Բ����
		Test_Triangle();    //GUI�����λ�ͼ����
		English_Font_test();//Ӣ������ʾ������
		Chinese_Font_test();//��������ʾ������
		Pic_test();			//ͼƬ��ʾʾ������
		Test_Dynamic_Num(); //��̬������ʾ
		Rotate_Test();   //��ת��ʾ����
	}
}

