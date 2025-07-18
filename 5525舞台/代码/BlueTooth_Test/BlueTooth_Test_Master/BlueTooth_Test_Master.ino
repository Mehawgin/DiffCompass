#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEAddress.h>

#define   KEY_5 		    5			//输出引脚
#define   KEY_6 		    6			//输出引脚
#define   KEY_7 		    7			//输出引脚
#define   KEY_8 		    8			//输出引脚
#define   KEY_10 		    10			//输出引脚
#define   KEY_20 		    20			//输出引脚
#define   KEY_21 		    21			//输出引脚


#define   KEY_BOOT 		9			//按键引脚

// 同从机的 UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_RX "beb5483e-36e1-4688-b7f5-ea07361b26a8" // 可写
#define CHARACTERISTIC_UUID_TX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // 可读 + 通知

bool deviceFound = false;
BLEAdvertisedDevice *targetDevice; // 存储扫描到的设备
BLERemoteCharacteristic *pRemoteTxCharacteristic; // 接收通知
BLERemoteCharacteristic *pRemoteRxCharacteristic; // 发送数据


/*********************************************************/
/********************* 按键扫描函数 ***********************/
/*********************************************************/
void key_scan()
{
  if(digitalRead(KEY_BOOT) == LOW)
  {
    //延时消抖
    delay(5);
    //如果仍为低电平，按键按下
    if(digitalRead(KEY_BOOT) == LOW)
    {		
		Serial.println("Botton pressed！");

		digitalWrite(KEY_5, LOW);
		digitalWrite(KEY_6, LOW);
		digitalWrite(KEY_7, LOW);
		digitalWrite(KEY_8, LOW);
		digitalWrite(KEY_10, LOW);
		digitalWrite(KEY_20, LOW);
		digitalWrite(KEY_21, LOW);
		delay(500);
		digitalWrite(KEY_5, HIGH);
		digitalWrite(KEY_6, HIGH);
		digitalWrite(KEY_7, HIGH);
		digitalWrite(KEY_8, HIGH);
		digitalWrite(KEY_10, HIGH);
		digitalWrite(KEY_20, HIGH);
		digitalWrite(KEY_21, HIGH);

			  
      //等待按键松开
      while(digitalRead(KEY_BOOT) == LOW);
    }
  }
} 
/***********************************************/
/********************* 扫描回调 *****************/
/***********************************************/
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks 
{
	void onResult(BLEAdvertisedDevice advertisedDevice) 
	{
		if (advertisedDevice.getName() == "ESP32-BLE-Slave") 
		{
			advertisedDevice.getScan()->stop(); // 停止扫描
			targetDevice = new BLEAdvertisedDevice(advertisedDevice);
			deviceFound = true;
			Serial.println("🔍 find target device");
		}
	}
};

/***********************************************/
/*********** 接收 BLE 通知的回调函数 **************/
/***********************************************/
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify
) 
{
  Serial.print("📥 receive note: ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)pData[i]);

  }
  Serial.println();    
  Serial.print("LED switch!\n");
  //digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

/***********************************************/
/**************** 蓝牙初始化函数 *****************/
/***********************************************/
void BT_init()
{
	// 初始化 BLE
	BLEDevice::init("ESP32-BLE-Master");

	// 扫描设备
	BLEScan* pBLEScan = BLEDevice::getScan();
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true); // 主动扫描（获取更多信息）
	pBLEScan->start(5); // 扫描5秒
	if (!deviceFound) 
	{
		Serial.println("❌ target device not find");
		return;
	}

	// 连接设备
	BLEClient* pClient = BLEDevice::createClient();
	if (pClient->connect(targetDevice))
	{
		Serial.println("✅ slave device connected!");
	} 
	else 
	{
		Serial.println("❌ connect fail");
		return;
	}

	// 获取服务
	BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
	if (pRemoteService == nullptr) 
	{
		Serial.println("❌ service not found");
		return;
	}

	// 获取 TX（接收通知）和 RX（发送数据）特性
	pRemoteTxCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID_TX);
	pRemoteRxCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID_RX);

	// 启用通知监听
	if (pRemoteTxCharacteristic->canNotify()) 
	{
		pRemoteTxCharacteristic->registerForNotify(notifyCallback);	
	}

	Serial.println("🔄 BLE master is ready!");
}



void setup() 
{
	Serial.begin(115200);

	//LED引脚初始化
	//pinMode(LED_PIN, OUTPUT);

	pinMode(KEY_5,OUTPUT);	
	pinMode(KEY_6,OUTPUT);	
	pinMode(KEY_7,OUTPUT);	
	pinMode(KEY_8,OUTPUT);	
	pinMode(KEY_10,OUTPUT);	
	pinMode(KEY_20,OUTPUT);	
	pinMode(KEY_21,OUTPUT);	
  	pinMode(KEY_BOOT,INPUT_PULLUP);  
  	digitalWrite(KEY_5, LOW);
  	digitalWrite(KEY_6, LOW);
  	digitalWrite(KEY_7, LOW);
  	digitalWrite(KEY_8, LOW);
  	digitalWrite(KEY_10, LOW);
  	digitalWrite(KEY_20, LOW);
  	digitalWrite(KEY_21, LOW);

	//蓝牙初始化
	BT_init();
}

void loop() 
{
	  Serial.println("Botton loop");
    key_scan();  

    delay(500);
  // 向从机发送数据（可自定义）
  //if (pRemoteRxCharacteristic != nullptr) 
	//{
  //  String message = "Hello from Master! (" + String(millis() / 1000) + "s)";
  //  pRemoteRxCharacteristic->writeValue(message.c_str(), message.length());
  //  delay(2000); // 每2秒发送一次
  //}
}
