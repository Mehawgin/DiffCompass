// Example for library:
// https://github.com/Bodmer/TJpg_Decoder

// This example if for an ESP8266 or ESP32, it renders a Jpeg file
// that is stored in a SD card file. The test image is in the sketch
// "data" folder (press Ctrl+K to see it). You must save the image
// to the SD card using you PC.

//                   CS  DC/RS  RESET  SDI/MOSI  SCK  SDO/MISO  LED  SD_CS   VCC   GND    
//ESP32-WROOM-32E:   15    2      27      13     14      12     21     22    5V    GND  

// Include the jpeg decoder library
#include <TJpg_Decoder.h>
#include <FS.h>
#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif
// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library



// Include SD
#define FS_NO_GLOBALS
#define SD_CS   22
//定义LED与按键管脚
#define LED_BLUE 2
#define KEY 16
#define MODE_MAX_NUM 2
#define FILE_NUMBER 252
#define FILE_NAME_SIZE_MAX 64

/* 选择哪一块屏幕 */
#define LEFT
//#define CENTER
//#define RIGHT


#ifdef LEFT
#define PLANE_FILE "/Plane_HZ_Left.jpg"
#define INDEX_ALIGN 252
#define CMZW_FILE "/CMZW_LEFT/CMZW_LEFT.mp40%03d.jpg"
#define ROTATION 3
#endif

#ifdef CENTER
#define PLANE_FILE "/Plane_HZ_Center.jpg"
#define INDEX_ALIGN 0
#define CMZW_FILE "/CMZW_CENTER/CMZW_CENTER.mp40%03d.jpg"
#define ROTATION 3
#endif

#ifdef RIGHT
#define PLANE_FILE "/Plane_HZ_Rgiht.jpg"
#define INDEX_ALIGN 252
#define CMZW_FILE "/CMZW_RIGHT/CMZW_RIGHT.mp40%03d.jpg"
#define ROTATION 1
#endif



struct Button 
{
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};


TFT_eSPI tft = TFT_eSPI();         // Invoke custom library
SPIClass MySPI(HSPI);
char file_name[FILE_NUMBER][FILE_NAME_SIZE_MAX];
volatile int flag = 0;
Button button1 = {0, 6, false};


/* 初始化LED与按键管脚 */
void key_init()
{
	pinMode(LED_BLUE,OUTPUT);
//	设置KEY引脚为上拉输入
	pinMode(KEY,INPUT_PULLUP);
}

/* 按键扫描函数 */
void key_scan()
{
  if(digitalRead(KEY) == LOW)
  {
    //延时消抖
    delay(5);
    //如果仍为低电平，按键按下
    if(digitalRead(KEY) == LOW)
    {
      flag++;
      if (flag > MODE_MAX_NUM)
      {
        flag = 0;
      }

//      mylcd.fillScreen(WHITE);
//      mylcd.pushImage(100, 135, 57, 107, Ding);

		tft.fillScreen(TFT_WHITE);
      //每次按下，变换LED状态
      digitalWrite(LED_BLUE,!digitalRead(LED_BLUE));
      //等待按键松开
      while(digitalRead(KEY) == LOW);
    }
  }
} 





// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}


void setup()
{
	key_init();
  Serial.begin(115200);
  Serial.println("\n\n Testing TJpg_Decoder library");

  //MySPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); // 40MHz
	int i;
	for(i = 0; i < FILE_NUMBER; i++)
	{
		snprintf(file_name[i], sizeof(file_name[i]), CMZW_FILE, i+INDEX_ALIGN);
	}
//  strcpy(file_name[0],"/01.jpg");
//  strcpy(file_name[1],"/02.jpg");
//  strcpy(file_name[2],"/03.jpg");
//  strcpy(file_name[3],"/04.jpg");
  
  pinMode(SD_CS, OUTPUT);//SD卡CS脚
  digitalWrite(SD_CS, HIGH);

  // Initialise SD before TFT
  if (!SD.begin(SD_CS, MySPI)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(0);
  }
  Serial.println("\r\nInitialisation done.");

  // Initialise the TFT
  tft.begin();
  tft.setRotation(ROTATION);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true); // We need to swap the colour bytes (endianess)

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(4);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);
}

void loop()
{
  int i = 0;
  //tft.fillScreen(TFT_RED);
  //delay(2000);
  key_scan();

  // Time recorded for test purposes
  uint32_t t = millis();

  // Get the width and height in pixels of the jpeg if you wish
  uint16_t w = 0, h = 0;

	if (flag == 0)
	{
		for(i=0;i<FILE_NUMBER;i++)
		{
			//TJpgDec.getSdJpgSize(&w, &h, file_name[i]);
			//Serial.print("FILENAME = ");Serial.print(file_name[i]);
			//Serial.print(" Width = "); Serial.print(w); Serial.print(", height = "); Serial.println(h);

			// Draw the image, top left at 0,0
			TJpgDec.drawSdJpg(0, 0, file_name[i]);

			// How much time did rendering take

      if (0 ==(i % 10))
      {
          t = millis() - t; 
          Serial.print(t); Serial.println(" ms");
      }


			// Wait before drawing again
			//delay(100);
			//key_scan();
			//if(digitalRead(KEY) == LOW)
				//break;
		}
	}
	else
	{
    char a[20] = "/test.jpg";
		TJpgDec.getSdJpgSize(&w, &h, a);
		Serial.print("FILENAME = ");Serial.print(a);
		Serial.print("Width = "); Serial.print(w); Serial.print(", height = "); Serial.println(h);
		
		TJpgDec.drawSdJpg(0, 0, a);
		Serial.print("zhang kai your mouth!OAOA!");
		delay(5000);
	}
	
  
}
