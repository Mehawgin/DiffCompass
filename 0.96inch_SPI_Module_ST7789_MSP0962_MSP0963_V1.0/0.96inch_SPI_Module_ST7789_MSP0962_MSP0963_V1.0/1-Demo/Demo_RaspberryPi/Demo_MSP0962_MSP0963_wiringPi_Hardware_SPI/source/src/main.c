//////////////////////////////////////////////////////////////////////////////////////////////////////	 
//This program is for learning only,Not to be used for any other purpose 
//without the permission of the author
//Testing Hardware:Raspberry PI all series
//QDtech-LCD liquid crystal driver for Raspberry PI
//xiaofeng@ShenZhen QDtech co.,LTD
//Company Website:www.qdtft.com
//Taobao Website:http://qdtech.taobao.com
//wiki Technology Website:http://www.lcdwiki.com
//We provide technical support,Any technical questions are welcome to 
//exchange and study at any time
//Fixed telephone (fax):+86 0755-23594567 
//cell-phone:15989313508(Mr Feng)
//E-mail:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//Technical Support QQ:3002773612  3002778157
//Technical Exchange QQ group:324828016
//Date:2021/4/6
//Version:V1.0
//Copyright reserved, piracy must be investigated
//Copyright(C) ShenZhen QDtech co.,LTD 2018-2028
//All rights reserved
/****************************************************************************************************
//This program uses the wiringPi gpio library,
//so the pin definition using wiringPi coding
//=====================================power supply wiring===========================================//
// OLED Module                Raspberry PI    
//    VCC        connect       DC 5V/3.3V      //LCD power positive, Physical pin 1,2,4,17
//    GND        connect          GND          //LCD power ground,Physical pin 6,9,14,20,25,30,34,39
//======================================data line wiring=============================================//
//The default data bus type for this module is 4-wire SPI
// OLED Module                Raspberry PI 
//    SDA        connect       19(wiringPi:12)      //LCD spi write signal
//======================================control line wiring==========================================//
// OLED Module                Raspberry PI 
//    RES        connect        5(wiringPi:9)       //LCD reset control signal
//    DC         connect        3(wiringPi:8)       //LCD data or command selection control signal
//    SCL        connect       23(wiringPi:14)      //LCD spi colck signal
//    CS         connect       24(wiringPi:10)       //LCD chip selection control signal
//    BLK        connect       12(wiringPi:1)      //LCD backlight control signal, if no control is needed, connect to 3.3V
//========================================touch screen wiring========================================//
//This module has no touch function,so it don't need touch screen wiring
*****************************************************************************************************/	
/****************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************************************/			
#include <wiringPi.h>
#include "lcd.h"
#include "test.h"
#include "type.h"

int main(void)
{	
	wiringPiSetup();	   //initialise wiringPi gpio library
	LCD_Init();	                 //LCD initialization
  //Cycle test
	while(1)
	{
		main_test(); 		//Test main interface
		menu_test();     	//3D menu display test
		Test_Color();  		//Simple screen filling test
		Test_FillRec();		//GUI rectangle drawing test
		Test_Circle(); 		//GUI circle test
		Test_Triangle();    //GUI triangle drawing test
		English_Font_test();//English font sample test
		Chinese_Font_test();//Chinese font sample test
		Pic_test();			//Image display sample test
		Test_Dynamic_Num(); //Dynamic number display test
		Rotate_Test();      //Rotating display test
	}
}

