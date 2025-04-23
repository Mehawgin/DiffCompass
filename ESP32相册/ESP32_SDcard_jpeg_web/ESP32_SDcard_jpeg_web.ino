/**    基于ESP32   
 *  SD卡模块       
 *  SDA/SS    5     
 *  SCK       18  
 *  MOSI      23  
 *  MISO      19   
 *  GND
 *  5V
 *  
 *  TFT模块
 *  VCC             3.3
 *  #define TFT_MISO 19
 *  #define TFT_MOSI 23
 *  #define TFT_SCLK 18
 *  #define TFT_CS   15  // Chip select control pin
 *  #define TFT_DC    2  // Data Command control pin
 *  #define TFT_RST   4  // Reset pin (could connect to RST pin)
 *  
 *  PAJ7620
 *  IIC_SCL  22
 *  IIC_SDA  21
 *  VCC     3.3
 *  GND     
 */
#include <SPI.h>

#include <FS.h>
#include <SD.h>

#include <TFT_eSPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <EEPROM.h>//数据保存库
// JPEG decoder library
#include <JPEGDecoder.h>
/*天气API*/
#include <ArduinoJson.h>//使用JSON-v5版的库
/*PAJ7620*/
#include <Wire.h>
#include "paj7620.h"
#include "html.h"//网页文件

TFT_eSPI tft = TFT_eSPI();


const char* ssid = "**********"; //Replace youself wifi ssid
const char* password = "*********"; //Replace youself wifi password

WebServer server(80);//相册用

WiFiClient client;//创建一个网络对象  获取天气用

int tft_num = 0;//相册计数器
bool  upload_flag = false;//文件上传
File fsUploadFile;//创建网页文件指针
/*PAJ7620*/
/*定义主要的手势*/
#define Forward   1
#define Backward  2
#define Right     3
#define Left      4
#define Up        5
#define Down      6
#define Clockwise 7
#define anticlockwise 8
#define wave      9
#define GES_REACTION_TIME    500       // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME      800       // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME     1000

uint8_t flag_page = 100;//确定页面标志位
int flag_pic = 0;//确定照片标志位
uint32_t t=0;//超时标志位
bool flag_finsh = 0;//确定加载标志位

//####################################################################################################
// 初始化函数
//####################################################################################################
void setup() {
  Serial.begin(115200);
  PAJ7620_setup();
  WIFI_setup();
  TFT_setup();
  client.setTimeout(5000);//设置天气服务器连接超时时间
  //EEPROM
  EEPROM.begin(512);
  tft_num =  EEPROM.read(20);
  Serial.print("the tft number is");Serial.println(tft_num);
  WEB_setup();
  SD_setup();
}
//####################################################################################################
// 主循环
//####################################################################################################
void loop(){
  if(upload_flag == false)
  {
    if(flag_finsh == 0)//页面未加载
    {
      switch(flag_page % 2)
      {
        case 0://天气界面
        {
          flag_finsh = 1;//完成加载
          weather_api();
        }
        break;
        case 1://照片界面
        {
          flag_finsh = 1;//完成加载
          limit();//形成循环
          jpg_draw(flag_pic);
        }
        break;
      }
    }
    else if(flag_finsh == 1)//页面已加载，进入手势扫描 和网络服务处理
    {
      uint8_t num = 0;
      num = PAJ7620_scan();//扫描手势传感器
      if(num >= 3 && num <=6)
      {
        if(num == Right)
        {
          flag_page++;
        }
        else if(num == Left)
        {
          flag_page--;
        }
        if(flag_page % 2==1)//处在照片界面 
        {
          if(num == Up)
          {
            flag_pic++;
          }
          else if(num == Down)
          {
            flag_pic--;
          }
        }
        server.handleClient();
        flag_finsh =0;
      }
    }
  }
  server.handleClient();//上传图片服务处理
  if(upload_flag == true)//防止未上传超时
  {
    t++;
    delay(5);
    server.handleClient();//上传图片服务处理
  }
  else
  {
    t=0;
  }

  if(t > 6000)
  {
    upload_flag = false;
    t = 0;
  }
  Serial.print(t);
}
//####################################################################################################
//  PAJ7620手势传感器扫描
//####################################################################################################
uint8_t PAJ7620_scan(){
  uint8_t num = 0;
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        //delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          //Serial.println("Forward");
          num = Forward;
          //delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          //Serial.println("Backward");
          num = Backward;
          //delay(GES_QUIT_TIME);
        }
        else
        {
         // Serial.println("Right");
          num = Right;
        }          
        break;
      case GES_LEFT_FLAG: 
        //delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          //Serial.println("Forward");
          num = Forward;
         // delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          //Serial.println("Backward");
          num = Backward;
          //delay(GES_QUIT_TIME);
        }
        else
        {
          //Serial.println("Left");
          num = Left;
        }          
        break;
      case GES_UP_FLAG:
        //delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          //Serial.println("Forward");
          num = Forward;
          //delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          //Serial.println("Backward");
          num = Backward;
         // delay(GES_QUIT_TIME);
        }
        else
        {
          //Serial.println("Up");
          num = Up;
        }          
        break;
      case GES_DOWN_FLAG:
        //delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          //Serial.println("Forward");
          num = Forward;
          //delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          //Serial.println("Backward");
          num = Backward;
          //delay(GES_QUIT_TIME);
        }
        else
        {
          //Serial.println("Down");
          num = Down;
        }          
        break;
      case GES_FORWARD_FLAG:
        //Serial.println("Forward");
        num = Forward;
        //delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        //Serial.println("Backward");
        num = Backward;
        //delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        //Serial.println("Clockwise");
        num = Clockwise;
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        //Serial.println("anti-clockwise");
        num = anticlockwise;
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
          num = wave;
        }
        break;
    }
  }
  return num;
  delay(100);
}
//####################################################################################################
//  web服务初始化
//####################################################################################################
void WEB_setup(){
  server.on("/", HTTP_GET, handleRoot);//发送开始获取
  //把上传的数据保存到spiffs
  server.on("/", HTTP_POST,[](){uplaodFinish();}, handleFileUpload);//下载文件
  //访问的url没有在找spiffs中找到回复404
  server.onNotFound([](){if(!handleFileRead(server.uri()))server.send(404, "text/plain", "FileNotFound");});
  server.begin();//网络服务开启
}
//####################################################################################################
//  SD初始化
//####################################################################################################
void SD_setup(){
if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");//判断SD卡类型
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  Serial.println("initialisation done.");
}
//####################################################################################################
//  TFT初始化
//####################################################################################################
void TFT_setup(){
  // Set all chip selects high to avoid bus contention during initialisation of each peripheral
  digitalWrite(22, HIGH); // Touch controller chip select (if used)
  digitalWrite(15, HIGH); // TFT screen chip select  片选信号
  digitalWrite( 5, HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)
  tft.begin();
}
//####################################################################################################
//  WIFI初始化
//####################################################################################################
void WIFI_setup(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    // Wait for connection
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50) {//wait 25 seconds
    Serial.print(".");
    delay(500);
  }
  if (i == 51) {
    Serial.print("Could not connect to");
    Serial.println(ssid);
    while (1) {
      delay(500);
    }
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());//输出IP地址
}
//####################################################################################################
//  PAJ7620初始化
//####################################################################################################
void PAJ7620_setup(){
  uint8_t error = 0;
  error = paj7620Init();      // initialize Paj7620 registers
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
}
//####################################################################################################
// 天气获取并显示
//####################################################################################################
void weather_api(){//天气API获取
  if(client.connect("api.seniverse.com",80)==1)//连接服务器并判断是否连接成功，若成功就发送GET 请求数据下发       
  {                                             //换成你自己在心知天气申请的私钥//改成你所在城市的拼音     
   //client.print("GET  /v3/weather/now.json?key=*********&location=beijing&language=zh-Hans&unit=c HTTP/1.1\r\n"); //心知天气的URL格式   
   client.print("GET  /v3/weather/daily.json?key=***********&location=shijiazhuang&language=zh-Hans&unit=c HTTP/1.1\r\n"); //心知天气的三天天气URL格式
   client.print("Host:api.seniverse.com\r\n");
   client.print("Accept-Language:zh-cn\r\n");
   client.print("Connection:close\r\n\r\n"); //向心知天气的服务器发送请求。
 
                 
   String status_code = client.readStringUntil('\r');        //读取GET数据，服务器返回的状态码，若成功则返回状态码200
   //Serial.println(status_code);
   /*
    * {"results":
    * [
    * {"location":
    * {"id":"WX4FBXXFKE4F","name":"北京","country":"CN","path":"北京,北京,中国","timezone":"Asia/Shanghai","timezone_offset":"+08:00"}
    * ,"now":{"text":"晴","code":"1","temperature":"10"},"last_update":"2020-04-04T23:10:00+08:00"}
    * ]
    * }
   */
   if(client.find("{")==1)//跳过返回的数据头，直接读取后面的JSON数据
   //if(client.available())
    {
      String json_from_server=client.readStringUntil(']');  //读取返回的JSON数据
      json_from_server = "{"+json_from_server+"]}]}";
      Serial.println(json_from_server);
      parseUserData(json_from_server);                      //将读取的JSON数据，传送到JSON解析函数中进行显示。
    }
    else
    {
       Serial.println("Not find.");
    }
  }
  else                                        
  { 
   Serial.println("connection failed this time");
   delay(500);                                            //请求失败等5秒
  } 
  client.stop(); //关闭HTTP客户端，采用HTTP短链接，数据请求完毕后要客户端要主动断开 
}
//####################################################################################################
// JOSN解析函数
//####################################################################################################
void parseUserData(String content){   // Json数据解析并串口打印.可参考https://www.bilibili.com/video/av65322772
 int weather_num[3];
 const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 210;
 DynamicJsonBuffer jsonBuffer(1660);
 
 JsonObject& root = jsonBuffer.parseObject(content);
 
 JsonObject& results_0 = root["results"][0];

 JsonObject& results_daily0 = results_0["daily"][0];
 JsonObject& results_daily1 = results_0["daily"][1];
 JsonObject& results_daily2 = results_0["daily"][2];
 
 const char* results_0_now_data = results_daily0["date"];//天气时间
 const char* results_0_now_text = results_daily0["text_day"];//天气时间
 
 const char* results_0_now_code = results_daily0["code_day"];//天气现象数值
 const char* results_1_now_code = results_daily1["code_day"];//天气现象数值
 const char* results_2_now_code = results_daily2["code_day"];//天气现象数值

 String high_tem_0= results_daily0["high"];//天气温度最高数值
 String high_tem_1= results_daily1["high"];//天气温度最高数值
 String high_tem_2= results_daily2["high"];//天气温度最高数值

 String low_tem_0= results_daily0["low"];//天气温度最低数值
 String low_tem_1= results_daily1["low"];//天气温度最低数值
 String low_tem_2= results_daily2["low"];//天气温度最低数值

 String hum= results_daily0["humidity"];//天气湿度数值

 const char* wind_speed0 = results_daily0["wind_speed"];//天气风速数值
 const char* wind_speed1 = results_daily1["wind_speed"];//天气风速数值
 const char* wind_speed2 = results_daily2["wind_speed"];//天气风速数值
 
 const char* rain= results_daily0["rainfall"];//天气降雨量数值
 
 //atoi()函数将字符转换为数字
 weather_num[0] = atoi(results_0_now_code);
 weather_num[1] = atoi(results_1_now_code);
 weather_num[2] = atoi(results_2_now_code);
 
 /*Serial.println(results_0_now_code);                       //通过串口打印出需要的信息
 Serial.println(results_1_now_code);
 Serial.println(results_2_now_code);
 Serial.print("\r\n");*/


 drawSdJpeg(0,0,0,3);//加载主页面

 tft_showstring(30,145,2,results_0_now_data);//显示今日日期
 
 
 drawSdJpeg(weather_num[0],25,25,1);//加载今天天气
 drawSdJpeg(weather_num[1],45,188,4);//加载明天天气
 drawSdJpeg(weather_num[2],45,245,4);//加载后天天气

 
 tft_showstring(180,34,2,low_tem_0+"-"+high_tem_0+"C");//显示今日温度
 tft_showstring(180,63,2,wind_speed0);//显示今日风速
 tft_showstring(180,90,2,hum+"%");//显示今日湿度
 tft_showstring(190,119,2,rain);//显示今日降雨量


 tft_showstring(180,189,2,low_tem_1+"-"+high_tem_1+"C");//显示明日温度
 tft_showstring(180,210,2,wind_speed1);//显示明日风速

 tft_showstring(180,248,2,low_tem_2+"-"+high_tem_2+"℃");//显示后天温度
 tft_showstring(180,270,2,wind_speed2);//显示后天风速
}
//####################################################################################################
// 显示数字
//####################################################################################################
void tft_showstring(int x,int y,int c,String z){
  tft.setCursor(x, y, c);
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.println(z);
}
//####################################################################################################
// 控制显示
//####################################################################################################
void jpg_draw(int bmp_screen_num){
  //tft.setRotation(2);  //设置旋转
  tft.fillScreen(0x0000);//背景颜色
  drawSdJpeg(bmp_screen_num,0,0,0);     // This draws a jpeg pulled off the SD Card
  //delay(5000);
}
//####################################################################################################
//读取SD卡图片
//####################################################################################################
void drawSdJpeg(int bmp_screen_num, int xpos, int ypos,int mode_pic) {
  String filename = "";
  int mode_ = 0;
  switch(mode_pic){
    case 0://加载照片
      filename = "/loge"+String(bmp_screen_num)+".jpg";
      mode_ =1;
       break;
    case 1://加载64x64天气图片
      filename = "/img/64x64/"+String(bmp_screen_num)+".jpg";//重定向文件
      break;
    case 2://无用
      break;
    case 3://加载天气主页面图片
      filename = "/img/main.jpg";//重定向文件
      break;
    case 4://加载40x40天气图片
      filename = "/img/40x40/"+String(bmp_screen_num)+".jpg";//重定向文件
      break;
    }
    
  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");

  // Use one of the following methods to initialise the decoder:
  boolean decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //boolean decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();
    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos,mode_);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}
//####################################################################################################
// 在TFT上绘图片
//####################################################################################################
void jpegRender(int xpos, int ypos,int mode_) {

  //jpegInfo(); // Print information from the JPEG file (could comment this line out)

  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;
  //调整选转角度并且居中显示
  if(mode_ == 1)
  {
    if(max_x > max_y)
    {
      tft.setRotation(1);
      xpos = (320-max_x)/2; //居中显示
      ypos = (240-max_y)/2; //居中显示
      if(xpos < 0 ||xpos > 320)
       xpos = 0;
      if(ypos < 0 || ypos >240)
       ypos = 0;
    }
    else if(max_x <= max_y)
    {
      tft.setRotation(2);
      xpos = (240-max_x)/2; //居中显示
      ypos = (320-max_y)/2; //居中显示
      if(xpos < 0 ||xpos > 240)
       xpos = 0;
      if(ypos < 0 || ypos >320)
       ypos = 0;
    }
  }
  else
  {
    tft.setRotation(2);
  }
  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);


    
  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = min(mcu_w, max_x % mcu_w);
  uint32_t min_h = min(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;
  

  
  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

    // Fetch data from the file, decode and display
    while (JpegDec.read()) {    // While there is more data in the file
      pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

    // Calculate coordinates of top left corner of current MCU
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;

    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ( (mcu_y + win_h) >= tft.height())
      JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }

  tft.setSwapBytes(swapBytes);
}
//####################################################################################################
// 打印TFT上图片信息
//####################################################################################################
void jpegInfo() {
  // Print information extracted from the JPEG file
  Serial.println("JPEG image info");
  Serial.println("===============");
  Serial.print("Width      :");
  Serial.println(JpegDec.width);
  Serial.print("Height     :");
  Serial.println(JpegDec.height);
  Serial.print("Components :");
  Serial.println(JpegDec.comps);
  Serial.print("MCU / row  :");
  Serial.println(JpegDec.MCUSPerRow);
  Serial.print("MCU / col  :");
  Serial.println(JpegDec.MCUSPerCol);
  Serial.print("Scan type  :");
  Serial.println(JpegDec.scanType);
  Serial.print("MCU width  :");
  Serial.println(JpegDec.MCUWidth);
  Serial.print("MCU height :");
  Serial.println(JpegDec.MCUHeight);
  Serial.println("===============");
  Serial.println("");
}
//####################################################################################################
// 将上传的文件发送回SD卡
//####################################################################################################
bool handleFileRead(String path){
  int upload_ = tft_num - 1;
  if(upload_<0)
    upload_ = 0;
  path = "/loge"+String(upload_)+".jpg";//上传JPG文件
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SD.exists(pathWithGz) || SD.exists(path)){
    if(SD.exists(pathWithGz))
      path += ".gz";
    File file = SD.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    upload_flag = false;//完成一次写入
    return true;
  }
  upload_flag = false;//完成一次写入
  return false;
}
//####################################################################################################
// 文件上传SD卡
//####################################################################################################
void handleFileUpload(){//网络服务处理函数
  upload_flag = true;//正在进行上传
  if(server.uri() != "/") return;
  HTTPUpload& upload = server.upload();
  String filename;
  char *file_sd;
  if(upload.status == UPLOAD_FILE_START){//开启下载上传的文件
    filename = upload.filename;
    if(!filename.startsWith("/")) 
    {
      filename = "/loge"+String(tft_num)+".jpg";//如果文件开头没有/则添加/ 并且对该图片添加计数尾缀
      tft_num++;//文件数+1
      EEPROM.write(20,tft_num);//将数据保存
      EEPROM.commit();
    }
    Serial.print("handleFileUpload Name: "); Serial.println(filename);//打印文件名
    
    SD.remove(filename);
    fsUploadFile = SD.open(filename, "w");//将上传的文件保存
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);//将上传文件写入SD卡
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile)
      fsUploadFile.close();
  }
}
//####################################################################################################
// 加载网页
//####################################################################################################
void handleRoot(){
  upload_flag = true;//进入上传就绪状态（打开了网页）
  server.send(200, "text/html", mainPageString);
  server.client().stop();
}
//####################################################################################################
// 上传完成函数
//####################################################################################################
void uplaodFinish(){
  server.send(200, "text/html", uploadString);//重新发送网页
  upload_flag = true;//上传完成，但是网页回复仍未完成
}
//####################################################################################################
// 限幅函数
//####################################################################################################
uint8_t limit(){
  if(flag_pic >= tft_num)
  {
    flag_pic = flag_pic - tft_num;
  }
  else if(flag_pic < 0)
  {
    flag_pic = flag_pic + tft_num;
  }
}
//####################################################################################################
// 文件格式获取
//####################################################################################################
String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
