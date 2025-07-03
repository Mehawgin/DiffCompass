#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>

/* 按键 */
#define BUTTON_PIN_BOOT    	0  // 按键连接的GPIO（GPIO0，可修改）
#define BUTTON_PIN_5     	5  // 按键连接的GPI5（GPIO0，可修改）

// 按键状态定义
typedef enum {
  BTN_IDLE,      // 空闲
  BTN_PRESSED,   // 按下（消抖中）
  BTN_HOLD,      // 长按
  BTN_RELEASED,  // 释放
  BTN_DOUBLE     // 双击
} ButtonState;
ButtonState buttonState = BTN_IDLE;
unsigned long pressStartTime = 0;
unsigned long lastReleaseTime = 0;



/*  蓝牙   */


// BLE 服务 & 特性 UUID (可自定义)
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_RX "beb5483e-36e1-4688-b7f5-ea07361b26a8" // 接收数据（可写）
#define CHARACTERISTIC_UUID_TX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // 发送数据（可读+通知)

// 全局变量
BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pTxCharacteristic;
BLECharacteristic *pRxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// 连接状态回调
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("📱 device connected!");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("📱 connection broken,wait for reconnect!");
      pServer->startAdvertising(); // 重新广播
    }
};

// RX 数据接收回调（主机写入数据时会触发）
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue(); // 接收数据
      if (rxValue.length() > 0) {
        Serial.print("📥 receive data: ");
        for (int i = 0; i < rxValue.length(); i++){
          Serial.print(rxValue[i]);
        }
        Serial.println();
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("🚀 BLE slave activated!");

  pinMode(BUTTON_PIN_BOOT, INPUT_PULLUP);  // 启用内部上拉电阻
  Serial.println("🔘 ESP32-SC-SuperMini 按键测试");

  
  pinMode(BUTTON_PIN_5, OUTPUT);  // 启用内部上拉电阻
  digitalWrite(BUTTON_PIN_BOOT, LOW);

  // 初始化 BLE
  BLEDevice::init("ESP32-BLE-Slave"); // 设备名称
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 创建 BLE 服务
  pService = pServer->createService(SERVICE_UUID);

  // 创建可写 Characteristics（接收数据）
  pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE
  );
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // 创建可读 + Notify Characteristics（发送数据）
  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  pTxCharacteristic->addDescriptor(new BLE2902()); // 启用通知

  // 启动服务
  pService->start();
  
  // 开始广播
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // 提高连接稳定性
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("📻 BLE slave is broadcasting,wait for connect!");
}

void loop() 
{
    // 设备连接状态变化处理
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = true;
    delay(500); // 稳定连接
  }
  if (!deviceConnected && oldDeviceConnected) {
    oldDeviceConnected = false;
    delay(500);
  }
  
  bool isPressed = (digitalRead(BUTTON_PIN_BOOT) == LOW);  // 检测按键（低电平触发）
  switch (buttonState) 
  {
    case BTN_IDLE:
      if (isPressed) 
      {
        pressStartTime = millis();
        buttonState = BTN_PRESSED;
      }
      break;
    case BTN_PRESSED:
      if (!isPressed) 
      {
        // 短按释放（<500ms）
        if (millis() - pressStartTime < 500) 
        {
          if (millis() - lastReleaseTime < 500) 
          {
            // 双击（两次短按间隔 <500ms）
            buttonState = BTN_DOUBLE;
            Serial.println("🔄 双击");
            if (deviceConnected) 
            {
              String message = "Hello from ESP32S3!双击 (" + String(millis() / 1000) + "s)";
              pTxCharacteristic->setValue(message.c_str());
              pTxCharacteristic->notify(); // 发送通知
              delay(1000); // 每秒发送一次
            }
          } 
          else 
          {
            buttonState = BTN_RELEASED;
            Serial.println("🔼 短按释放");
              // 从机主动发送数据（可自定义）
            if (deviceConnected) 
            {
              String message = "Hello from ESP32S3!短按释放 (" + String(millis() / 1000) + "s)";
			  
			  digitalWrite(BUTTON_PIN_5, LOW);
			  delay(500);
			  digitalWrite(BUTTON_PIN_5, HIGH);
			  
              pTxCharacteristic->setValue(message.c_str());
              pTxCharacteristic->notify(); // 发送通知
              delay(1000); // 每秒发送一次
            }
          }
          lastReleaseTime = millis();
        }
        buttonState = BTN_IDLE;
      } 
      else if 
      (millis() - pressStartTime >= 500) 
      {
        // 长按（>500ms）
        buttonState = BTN_HOLD;
        Serial.println("⏳ 长按中...");
      }
      break;
    case BTN_HOLD:
      if (!isPressed) 
      {
        buttonState = BTN_IDLE;
        Serial.println("🔚 长按释放");
      }
      break;
    case BTN_DOUBLE:
      buttonState = BTN_IDLE;
      break;
    default:
      buttonState = BTN_IDLE;
      break;
  }
  delay(10);  // 降低CPU占用
}
