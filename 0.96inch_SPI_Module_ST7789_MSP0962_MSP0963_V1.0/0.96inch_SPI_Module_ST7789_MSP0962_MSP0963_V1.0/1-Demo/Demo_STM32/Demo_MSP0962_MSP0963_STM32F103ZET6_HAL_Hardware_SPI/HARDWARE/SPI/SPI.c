//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103ZET6,正点原子ELITE STM32开发板,主频72MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/08/22
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接          3.3V         //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI总线
//     LCD模块                STM32单片机    
//       SDA         接          PB15         //液晶屏SPI总线数据写信号
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机 
//       BLK         接          PB9          //液晶屏背光控制信号，如果不需要控制，接3.3V
//       SCL         接          PB13         //液晶屏SPI总线时钟信号
//       DC          接          PB10         //液晶屏数据/命令控制信号
//       RES         接          PB12         //液晶屏复位控制信号
//       CS          接          PB11         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//模块不带触摸功能，不需要进行触摸屏接线
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

SPI_HandleTypeDef SPI2_Handler; /* SPI1句柄 */

/*****************************************************************************
 * @name       :void SPI_Set_8Bit(void)
 * @date       :2018-08-09 
 * @function   :set SPI to 8 bit mode
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI_Set_8Bit(void)
{
		SPI2_Handler.Init.DataSize = SPI_DATASIZE_8BIT; 
    __HAL_SPI_DISABLE(&SPI2_Handler); // DISABLE SPI
    SPI2_Handler.Instance->CR1 &= ~SPI_CR1_DFF; // SPI 8
    __HAL_SPI_ENABLE(&SPI2_Handler);  // ENABLE SPI
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
		SPI2_Handler.Init.DataSize = SPI_DATASIZE_16BIT; 
    __HAL_SPI_DISABLE(&SPI2_Handler); // DISABLE SPI
    SPI2_Handler.Instance->CR1 |= SPI_CR1_DFF;  // SPI 16
    __HAL_SPI_ENABLE(&SPI2_Handler); // ENABLE SPI
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
	while((SPI2_Handler.Instance->SR&SPI_FLAG_TXE) == RESET);
	SPI2_Handler.Instance->DR = Byte;
	while((SPI2_Handler.Instance->SR&SPI_FLAG_RXNE)==RESET);
	return SPI2_Handler.Instance->DR;	
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
	while((SPI2_Handler.Instance->SR&SPI_FLAG_TXE) == RESET);
	SPI2_Handler.Instance->DR = Data;
	while((SPI2_Handler.Instance->SR&SPI_FLAG_RXNE)==RESET);
	SPI_Set_8Bit();
	return SPI2_Handler.Instance->DR;	
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
    HAL_SPI_Transmit(&SPI2_Handler, Bbuf,  n, 1000);
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
    HAL_SPI_Transmit(&SPI2_Handler, (uint8_t *)Bbuf,  n, 1000);
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
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SpeedSet)); /* 判断有效性 */
    __HAL_SPI_DISABLE(&SPI2_Handler);             /* 关闭SPI */
    SPI2_Handler.Instance->CR1 &= 0XFFC7;         /* 位3-5清零，用来设置波特率 */
    SPI2_Handler.Instance->CR1 |= SpeedSet << 3;     /* 设置SPI速度 */
    __HAL_SPI_ENABLE(&SPI2_Handler);              /* 使能SPI */
} 

/*****************************************************************************
 * @name       :void SPI2_Init(void)	
 * @date       :2018-08-09 
 * @function   :Initialize the STM32 hardware SPI1
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI2_Init(void)	
{
		__HAL_RCC_SPI2_CLK_ENABLE();  /* SPI1时钟使能 */

    SPI2_Handler.Instance = SPI2;                                /* SPI1 */
    SPI2_Handler.Init.Mode = SPI_MODE_MASTER;                        /* 设置SPI工作模式，设置为主模式 */
    SPI2_Handler.Init.Direction = SPI_DIRECTION_2LINES;              /* 设置SPI单向或者双向的数据模式:SPI设置为双线模式 */
    SPI2_Handler.Init.DataSize = SPI_DATASIZE_8BIT;                  /* 设置SPI的数据大小:SPI发送接收8位帧结构 */
    SPI2_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;               /* 串行同步时钟的空闲状态为高电平 */
    SPI2_Handler.Init.CLKPhase = SPI_PHASE_2EDGE;                    /* 串行同步时钟的第二个跳变沿（上升或下降）数据被采样 */
    SPI2_Handler.Init.NSS = SPI_NSS_SOFT;                            /* NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制 */
    SPI2_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; /* 定义波特率预分频的值:波特率预分频值为2 */
    SPI2_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;                   /* 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始 */
    SPI2_Handler.Init.TIMode = SPI_TIMODE_DISABLE;                   /* 关闭TI模式 */
    SPI2_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   /* 关闭硬件CRC校验 */
    SPI2_Handler.Init.CRCPolynomial = 7;                             /* CRC值计算的多项式 */
    HAL_SPI_Init(&SPI2_Handler);                                     /* 初始化 */

    __HAL_SPI_ENABLE(&SPI2_Handler); /* 使能SPI1 */

    SPI_WriteByte(0XFF); /* 启动传输, 实际上就是产生8个时钟脉冲, 达到清空DR的作用, 非必需 */  
}


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    if (hspi->Instance == SPI2)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE(); /*GPIOA时钟使能 */

        /* SCK、MISO、MOSI引脚模式设置(复用输出) */
        GPIO_InitStructure.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
}
