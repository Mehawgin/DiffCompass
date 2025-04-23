/////////////////////////////////////////////////////////////////
/*
  Button2.h - Arduino Library to simplify working with buttons.
  Created by Lennart Hennigs.
*/
/////////////////////////////////////////////////////////////////
#pragma once

#ifndef Button2_h
#define Button2_h
/////////////////////////////////////////////////////////////////
#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
  #include <functional>
#endif
#include "Arduino.h"
/////////////////////////////////////////////////////////////////

#define DEBOUNCE_MS 50
#define LONGCLICK_MS 200
#define DOUBLECLICK_MS 300
#define CAPACITIVE_TOUCH_THRESHOLD 35

#define UNDEFINED_PIN 255
#define VIRTUAL_PIN 254

/////////////////////////////////////////////////////////////////

enum clickType {
  single_click, 
  double_click, 
  triple_click, 
  long_click,
  //增加此选项: 点按后紧接着长按, 触发此事件
  //Add for click once and then long click
  combo_long_click,
  empty
};

class Button2 {

protected:
  int id;
  byte pin;
  byte state;
  byte prev_state;
  byte click_count = 0;
  clickType last_click_type = empty;
  bool was_pressed = false;
  bool is_capacitive = false;
  unsigned long click_ms;
  unsigned long down_ms;

  bool longclick_detected_retriggerable;
  uint16_t longclick_detected_counter = 0;
  bool longclick_detected = false;
  bool longclick_detected_reported = false;
  
  unsigned int debounce_time_ms;
  unsigned int longclick_time_ms;
  unsigned int doubleclick_time_ms;
  
  unsigned int down_time_ms = 0;
  bool pressed_triggered = false;

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
  typedef std::function<void(Button2 &btn)> CallbackFunction;
  typedef std::function<byte()> StateCallbackFunction;
#else
  typedef void (*CallbackFunction)(Button2 &);
  typedef byte (*StateCallbackFunction)();
#endif

  StateCallbackFunction get_state_cb = NULL;

  CallbackFunction pressed_cb = NULL;
  CallbackFunction released_cb = NULL;
  CallbackFunction change_cb = NULL;
  CallbackFunction tap_cb = NULL;
  CallbackFunction click_cb = NULL;
  CallbackFunction longclick_detected_cb = NULL;
  CallbackFunction long_cb = NULL;
  CallbackFunction double_cb = NULL;
  CallbackFunction triple_cb = NULL;

  //增加此选项: 点按后紧接着长按, 触发此事件
  //Add for click once and then long click
  CallbackFunction combo_long_cb = NULL; //Add for click once and then long click

public:
  Button2(){  pin = UNDEFINED_PIN; id = _nextID++; } //  default contructor
  Button2(byte attachTo, byte buttonMode = INPUT_PULLUP, boolean isCapacitive = false, boolean activeLow = true);

  void begin(byte attachTo, byte buttonMode = INPUT_PULLUP, boolean isCapacitive = false , boolean activeLow  = true);

  void setDebounceTime(unsigned int ms) {debounce_time_ms=ms;}
  void setLongClickTime(unsigned int ms) {longclick_time_ms=ms;}
  void setDoubleClickTime(unsigned int ms) {doubleclick_time_ms=ms;}
  
  unsigned int getDebounceTime() const { return debounce_time_ms; }
  unsigned int getLongClickTime() const  { return longclick_time_ms; }
  unsigned int getDoubleClickTime() const { return doubleclick_time_ms; }
  byte getPin() const { return pin; }

  void reset();

  void setButtonStateFunction(StateCallbackFunction f) { get_state_cb = f; }

  void setChangedHandler(CallbackFunction f) { change_cb = f; }
  void setPressedHandler(CallbackFunction f) { pressed_cb = f; }
  void setReleasedHandler(CallbackFunction f) { released_cb = f; }

  void setTapHandler(CallbackFunction f) { tap_cb = f; }
  void setClickHandler(CallbackFunction f) { click_cb = f; }
  void setDoubleClickHandler(CallbackFunction f) { double_cb = f; }
  void setTripleClickHandler(CallbackFunction f) { triple_cb = f; }

  void setLongClickHandler(CallbackFunction f) { long_cb = f; }
  void setComboLongClickHandler(CallbackFunction f) { combo_long_cb = f; }
  void setLongClickDetectedHandler(CallbackFunction f) { longclick_detected_cb = f; }
  void setLongClickDetectedRetriggerable(bool retriggerable) { 
    longclick_detected_retriggerable = retriggerable;
  }

  unsigned int wasPressedFor() const {return down_time_ms;}
  boolean isPressed() const {return (state == _pressedState);}
  boolean isPressedRaw() {return (_getState() == _pressedState);}

  bool wasPressed() const {return was_pressed;}
  clickType read(bool keepState = false);
  clickType wait(bool keepState = false);
  void waitForClick(bool keepState = false);
  void waitForDouble(bool keepState = false);
  void waitForTriple(bool keepState = false);
  void waitForLong(bool keepState = false);

  byte getNumberOfClicks() const{return click_count;}
  clickType getType() const{return last_click_type;}
  const char * clickToString(clickType type) const{
    switch(type){
      case single_click:     return "click";
      case double_click:     return "double click";
      case long_click:       return "long click";
      case triple_click:     return "triple click";
      case combo_long_click: return "combo long click";
    }
    return "empty";
  }

  int getID() const{return id;}
  void setID(int newID){id = newID;}

  bool operator == (Button2 &rhs) { return (this == &rhs); }

  void loop();

private: 
  static int _nextID;
  
  byte _pressedState;
  byte _getState();
};
/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
