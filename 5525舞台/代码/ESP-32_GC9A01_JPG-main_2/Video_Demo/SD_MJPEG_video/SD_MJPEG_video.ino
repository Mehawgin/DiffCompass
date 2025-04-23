#define MJPEG_FILENAME "/CMZW_CENTER_2.mjpeg"
#define MJPEG_BUFFER_SIZE (240 * 240 * 2 / 4)
#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <Arduino_GFX_Library.h>
#define TFT_BRIGHTNESS 128



//#define MISO     	12
//#define SCK    		14  //SCL
//#define MOSI    	13  //SDA
//#define SD_CS   	22
//#define TFT_CS   	15
//#define TFT_BLK 	-1
//#define TFT_DC  	 2
//#define TFT_RST 	27
//
////Arduino_DataBus *bus = new Arduino_HWSPI(27 /* DC */, 5 /* CS */, SCK, MOSI, MISO, true);
//Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, SCK, MOSI, MISO, VSPI);
//Arduino_GC9A01  *gfx = new Arduino_GC9A01(bus, TFT_RST, 1, true);

#define MISO     	25
#define SCK    		26  //SCL
#define MOSI    	27  //SDA
#define SD_CS   	33
#define TFT_CS   	13
#define TFT_BLK 	-1
#define TFT_DC  	14
#define TFT_RST 	12
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, SCK, MOSI, MISO, VSPI);
Arduino_TFT *gfx = new Arduino_ST7796(bus, TFT_RST, 1 /* rotation */);

#include "MjpegClass.h"
static MjpegClass mjpeg;

void setup()
{
	Serial.begin(115200);

	// Init Video
	gfx->begin();
	gfx->fillScreen(BLACK);
	delay(200);
	gfx->fillScreen(WHITE);
	delay(200);
	gfx->fillScreen(RED);
	delay(200);
	gfx->fillScreen(GREEN);
	delay(200);
	gfx->fillScreen(BLUE);

  // Init SD card
  SPI.begin(SCK, MISO, MOSI, SD_CS);
  if( !SD.begin(SD_CS) )
  
  // if (!SD.begin(SC, SPI, 80000000)) /* SPI bus mode */
  // if ((!SD_MMC.begin()) && (!SD_MMC.begin())) /* 4-bit SD bus mode */
  // if ((!SD_MMC.begin("/sdcard", true)) && (!SD_MMC.begin("/sdcard", true))) /* 1-bit SD bus mode */
  {
    Serial.println(F("ERROR: SD card mount failed!"));
    gfx->println(F("ERROR: SD card mount failed!"));
  }
  else
  {
    File vFile = SD.open(MJPEG_FILENAME);
    // File vFile = SD_MMC.open(MJPEG_FILENAME);
    if (!vFile || vFile.isDirectory())
    {
      Serial.println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
      gfx->println(F("ERROR: Failed to open " MJPEG_FILENAME " file for reading"));
    }
    else
    {
      uint8_t *mjpeg_buf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
      if (!mjpeg_buf)
      {
        Serial.println(F("mjpeg_buf malloc failed!"));
      }
      else
      {
        
        Serial.println(F("MJPEG video start"));
        mjpeg.setup(vFile, mjpeg_buf, gfx, true);
        Serial.println(mjpeg.readMjpegBuf());
        // Read video

        
       while (mjpeg.readMjpegBuf())
        
        {
          // Play video
          mjpeg.drawJpg();
                
        }
        
        Serial.println(mjpeg.readMjpegBuf());
        Serial.println(F("MJPEG video end"));
        vFile.close();
        Serial.println(F("Reboot"));
        esp_restart();
        
      }
    }
  }

#ifdef TFT_BL
  delay(60000);
  ledcDetachPin(TFT_BL);
#endif
  gfx->displayOff();
  esp_deep_sleep_start();
}
  
void loop()
{
}
