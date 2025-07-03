#define MJPEG_FILENAME "/new/CMZW_CENTER_10fps.mjpeg"
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 / 8)
#include <WiFi.h>
#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>
#include <Arduino_GFX_Library.h>
#include <esp_task_wdt.h>
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

//Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, SCK, MOSI, MISO);
// 在 TFT 初始化时降低 SPI 速率// ESP32引脚（非S3）
#define SD_CS   	15
#define MISO     	2
#define SCK    		4  //SCL
#define MOSI    	16  //SDA
#define TFT_DC    17  // 屏幕DC引脚
#define TFT_RST   5  // 屏幕复位
#define TFT_CS    18  // 屏幕片选
Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS, SCK, MOSI, MISO);  // 40MHz → 20MHz
Arduino_ST7796  *gfx = new Arduino_ST7796(bus, TFT_RST, 3, false);
#include "MjpegClass.h"

#define TFT_BRIGHTNESS 128
#define LED_PIN     1  			// LED引脚
#define KEY 		13			//按键引脚




// ESP32-S3引脚
//#define SD_CS   	4
//#define MISO     	5
//#define SCK    		6  		//SCL
//#define MOSI    	7  		//SDA
//#define TFT_DC    	15  	// 屏幕DC引脚
//#define TFT_RST   	16		// 屏幕复位
//#define TFT_CS    	17  	// 屏幕片选






static MjpegClass mjpeg;
SPIClass MySPI(SPI);
bool video_file_ok = 0;
uint8_t *mjpeg_buf = NULL;
int frame_count = 0;

//建立一个变量用来保存上次调用中断处理程序的时间，如果这个时间小于250毫秒则不再确认按下按钮。
unsigned long button_time = 0;  
unsigned long last_button_time = 0;




struct Button 
{
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
}; 


Button button1 = {0, 6, false};

/*********************************************************/
/********************* 初始化LED与按键管脚 *****************/
/*********************************************************/
void key_init()
{
	//nMode(LED_PIN,OUTPUT);
//	设置KEY引脚为上拉输入
	pinMode(KEY,INPUT_PULLUP);
}

/*********************************************************/
/********************* 按键扫描函数 ***********************/
/*********************************************************/
void key_scan()
{
  if(digitalRead(KEY) == LOW)
  {
    //延时消抖
    delay(5);
    //如果仍为低电平，按键按下
    if(digitalRead(KEY) == LOW)
    {		
	  Serial.println("Botton pressed！");
	  //SD_uninit();
	  //SD_init();
	  mjpeg.Replay();
	  frame_count = 0;

      //等待按键松开
      while(digitalRead(KEY) == LOW);
    }
  }
} 

/*********************************************************/
/********************* 后台运行任务 ************************/
/*********************************************************/
/* 暂时没用上 */
void backgroundTask(void *pvParams) 
{
	//BT_init();

	while (1) 
	{
        Serial.println("[Background Task] Running...");
        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
}

/*********************************************************/
/********************* SD卡读取文件初始化 ******************/
/*********************************************************/
void SD_init()
{
	MySPI.begin(SCK, MISO, MOSI, SD_CS);
	if( !SD.begin(SD_CS) )
	{
	  Serial.println(F("ERROR: SD card mount failed!"));
	  gfx->println(F("ERROR: SD card mount failed!"));
	}
	else
	{
	  File vFile = SD.open(MJPEG_FILENAME);
	  if (!vFile || vFile.isDirectory())
	  {
		Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
		gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
	  }
	  else
	  {
		mjpeg_buf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
		if (!mjpeg_buf)
		{
		  Serial.println(F("mjpeg_buf malloc failed!"));
		}
		else
		{
		  mjpeg.setup(vFile, mjpeg_buf, gfx, false);
		  video_file_ok = 1;
		}
	  }
	}
}

/*********************************************************/
/********************* SD卡读取文件去初始化 *****************/
/*********************************************************/
void SD_uninit()
{
    // 1. 关闭并释放视频文件相关资源
    if (video_file_ok) 
	{
        //mjpeg.close();        // 关闭MJPEG解码器（如果有）
        if (mjpeg_buf) 
		{
            free(mjpeg_buf);  // 释放视频缓冲区
            mjpeg_buf = NULL;
        }
        video_file_ok = 0;
    }
	
    // 2. 确保所有文件都已关闭
    // SD库会自动关闭打开的文件，但显式关闭更安全
    if (SD.exists(MJPEG_FILENAME)) 
	{
        File vFile = SD.open(MJPEG_FILENAME);
        if (vFile) 
		{
            vFile.close();
        }
    }
	
    // 3. 结束SD卡访问
    SD.end();
    // 4. 可选：重置SPI总线（针对某些特殊情况）
    MySPI.end();
    
    Serial.println(F("SD card unmounted successfully"));
    if(gfx) gfx->println(F("SD card unmounted successfully"));
}

/*********************************************************/
/********************* 屏幕检测 ***************************/
/*********************************************************/
void Screen_Test()
{
	// Init Video
	gfx->begin();
	gfx->fillScreen(BLACK);
	delay(500);
	gfx->fillScreen(BLUE);
	delay(500);
	gfx->fillScreen(GREEN);
}

void setup()
{
	WiFi.mode(WIFI_OFF);
	Serial.begin(115200);
	
	//LED引脚初始化
	//pinMode(LED_PIN, OUTPUT);
	//digitalWrite(LED_PIN, 1);

    xTaskCreate(backgroundTask, "BackgroundTask", 2048, NULL, 1, NULL);
	//蓝牙初始化
	//BT_init();

	//按键初始化
	key_init();

	// 设置 10 秒看门狗超时，暂时调试
	esp_task_wdt_init(10, false);  

	//测试屏幕
	Screen_Test();

	//SD卡读取视频文件初始化
	SD_init();

}


  
void loop()
{
	int last_ms = millis();

	if (1 == video_file_ok)
	{
		frame_count = 0;
		Serial.println(F("MJPEG video start"));
		int start_ms = millis();

		//视频播放
		while (mjpeg.readMjpegBuf())
		{
			
			// Play video
			Serial.printf("Play video[%d] time[%d ms] \n\r", frame_count,(millis() - last_ms));
			last_ms = millis();

			//当前帧播放
			mjpeg.drawJpg();
			frame_count ++;
			key_scan();
		}

		int time_used = millis() - start_ms;
		float fps = 1000.0 * frame_count / time_used;
		Serial.printf("Frame total count:[%d] \n\r", frame_count);
		Serial.printf("Average FPS: %0.1f\n", fps);
		
		Serial.println(F("MJPEG video end"));
		//vFile.close();
		Serial.println(F("Reboot"));
		esp_restart();
	}
	
  gfx->displayOff();
  esp_deep_sleep_start();
}
