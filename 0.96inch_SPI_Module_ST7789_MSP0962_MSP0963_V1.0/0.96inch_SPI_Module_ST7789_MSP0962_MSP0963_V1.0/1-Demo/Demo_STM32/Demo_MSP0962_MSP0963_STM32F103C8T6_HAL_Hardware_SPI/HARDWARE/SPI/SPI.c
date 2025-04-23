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
#include "spi.h"

SPI_HandleTypeDef SPI1_Handler; /* SPI1��� */

/*****************************************************************************
 * @name       :void SPI_Set_8Bit(void)
 * @date       :2018-08-09 
 * @function   :set SPI to 8 bit mode
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI_Set_8Bit(void)
{
		SPI1_Handler.Init.DataSize = SPI_DATASIZE_8BIT; 
    __HAL_SPI_DISABLE(&SPI1_Handler); // DISABLE SPI
    SPI1_Handler.Instance->CR1 &= ~SPI_CR1_DFF; // SPI 8
    __HAL_SPI_ENABLE(&SPI1_Handler);  // ENABLE SPI
}

/*****************************************************************************
 * @name       :void SPI_Set_16Bit(void)
 * @date       :2018-08-09 
 * @function   :set SPI to 16 bit mode
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void SPI_Set_16Bit(void)
{
		SPI1_Handler.Init.DataSize = SPI_DATASIZE_16BIT; 
    __HAL_SPI_DISABLE(&SPI1_Handler); // DISABLE SPI
    SPI1_Handler.Instance->CR1 |= SPI_CR1_DFF;  // SPI 16
    __HAL_SPI_ENABLE(&SPI1_Handler); // ENABLE SPI
}

/*****************************************************************************
 * @name       :uint8_t SPI_WriteByte(uint8_t Byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
uint8_t SPI_WriteByte(uint8_t Byte)
{	
	while((SPI1_Handler.Instance->SR&SPI_FLAG_TXE) == RESET);
	SPI1_Handler.Instance->DR = Byte;
	while((SPI1_Handler.Instance->SR&SPI_FLAG_RXNE)==RESET);
	return SPI1_Handler.Instance->DR;	
} 

/*****************************************************************************
 * @name       :uint16_t SPI_WriteWord(uint16_t Byte)
 * @date       :2018-08-09 
 * @function   :Write two bytes of data using STM32's hardware SPI
 * @parameters :Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
uint16_t SPI_WriteWord(uint16_t Data)
{	
	SPI_Set_16Bit();
	while((SPI1_Handler.Instance->SR&SPI_FLAG_TXE) == RESET);
	SPI1_Handler.Instance->DR = Data;
	while((SPI1_Handler.Instance->SR&SPI_FLAG_RXNE)==RESET);
	SPI_Set_8Bit();
	return SPI1_Handler.Instance->DR;	
}

/*****************************************************************************
 * @name       :void SPI_Write_nByte(uint8_t *Bbuf,uint32_t n)
 * @date       :2018-08-09 
 * @function   :Write n bytes of data using STM32's hardware SPI
 * @parameters :Bbuf:pointer to data buffer
							  n:Size amount of data to be sent
 * @retvalue   :None
******************************************************************************/
void SPI_Write_nByte(uint8_t *Bbuf,uint32_t n)
{
    HAL_SPI_Transmit(&SPI1_Handler, Bbuf,  n, 1000);
} 

/*****************************************************************************
 * @name       :void SPI_Write_nByte(uint8_t *Bbuf,uint32_t n)
 * @date       :2018-08-09 
 * @function   :Write 2xn bytes of data using STM32's hardware SPI
 * @parameters :Bbuf:pointer to data buffer
							  n:Size amount of data to be sent
 * @retvalue   :None
******************************************************************************/
void SPI_Write_nWord(uint16_t *Bbuf,uint32_t n)
{
		SPI_Set_16Bit();
    HAL_SPI_Transmit(&SPI1_Handler, (uint8_t *)Bbuf,  n, 1000);
		SPI_Set_8Bit();
} 

/*****************************************************************************
 * @name       :void SPI_SetSpeed(u8 SpeedSet)
 * @date       :2018-08-09 
 * @function   :Set hardware SPI Speed
 * @parameters :SpeedSet:SPI frequency division coefficient
 * @retvalue   :None
******************************************************************************/
void SPI_SetSpeed(uint8_t SpeedSet)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SpeedSet)); /* �ж���Ч�� */
    __HAL_SPI_DISABLE(&SPI1_Handler);             /* �ر�SPI */
    SPI1_Handler.Instance->CR1 &= 0XFFC7;         /* λ3-5���㣬�������ò����� */
    SPI1_Handler.Instance->CR1 |= SpeedSet << 3;     /* ����SPI�ٶ� */
    __HAL_SPI_ENABLE(&SPI1_Handler);              /* ʹ��SPI */
} 

/*****************************************************************************
 * @name       :void SPI2_Init(void)	
 * @date       :2018-08-09 
 * @function   :Initialize the STM32 hardware SPI1
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI1_Init(void)	
{
		__HAL_RCC_SPI1_CLK_ENABLE();  /* SPI1ʱ��ʹ�� */

    SPI1_Handler.Instance = SPI1;                                /* SPI1 */
    SPI1_Handler.Init.Mode = SPI_MODE_MASTER;                        /* ����SPI����ģʽ������Ϊ��ģʽ */
    SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES;              /* ����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ */
    SPI1_Handler.Init.DataSize = SPI_DATASIZE_8BIT;                  /* ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ */
    SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;               /* ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ */
    SPI1_Handler.Init.CLKPhase = SPI_PHASE_2EDGE;                    /* ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ����� */
    SPI1_Handler.Init.NSS = SPI_NSS_SOFT;                            /* NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ���� */
    SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; /* ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ2 */
    SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;                   /* ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ */
    SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;                   /* �ر�TIģʽ */
    SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   /* �ر�Ӳ��CRCУ�� */
    SPI1_Handler.Init.CRCPolynomial = 7;                             /* CRCֵ����Ķ���ʽ */
    HAL_SPI_Init(&SPI1_Handler);                                     /* ��ʼ�� */

    __HAL_SPI_ENABLE(&SPI1_Handler); /* ʹ��SPI1 */

    SPI_WriteByte(0XFF); /* ��������, ʵ���Ͼ��ǲ���8��ʱ������, �ﵽ���DR������, �Ǳ��� */  
}


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    if (hspi->Instance == SPI1)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE(); /*GPIOAʱ��ʹ�� */

        /* SCK��MISO��MOSI����ģʽ����(�������) */
        GPIO_InitStructure.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
}
