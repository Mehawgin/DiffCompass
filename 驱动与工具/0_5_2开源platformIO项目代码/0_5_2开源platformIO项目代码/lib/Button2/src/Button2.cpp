/////////////////////////////////////////////////////////////////
/*
  Button2.cpp - Arduino Library to simplify working with buttons.
  Created by Lennart Hennigs.
*/
/////////////////////////////////////////////////////////////////

#include "Button2.h"

/////////////////////////////////////////////////////////////////
// initalize static counter

int Button2::_nextID = 0;

/////////////////////////////////////////////////////////////////
// contructor

Button2::Button2(byte attachTo, byte buttonMode /* = INPUT_PULLUP */, boolean isCapacitive /* = false */, boolean activeLow /* = true */) {
  begin(attachTo, buttonMode, isCapacitive, activeLow);
}

/////////////////////////////////////////////////////////////////

void Button2::begin(byte attachTo, byte buttonMode /* = INPUT_PULLUP */, boolean isCapacitive /* = false */, boolean activeLow /* = true */) {  
  pin = attachTo;
  id = _nextID++;
  longclick_detected_counter = 0;
  longclick_detected_retriggerable = false;
  _pressedState = activeLow ? LOW : HIGH;
  setDebounceTime(DEBOUNCE_MS);
  setLongClickTime(LONGCLICK_MS);
  setDoubleClickTime(DOUBLECLICK_MS);
  if (!isCapacitive) {
    if (attachTo != VIRTUAL_PIN) {
      pinMode(attachTo, buttonMode);
    }
  } else {
    is_capacitive = true;
  }	
  //  state = activeLow ? HIGH : LOW;
  state = _getState();
  prev_state = state ;
}

/////////////////////////////////////////////////////////////////

clickType Button2::read(bool keepState /* = false */) {
    if (!keepState) {
      clickType res = last_click_type;
      last_click_type = empty;
      was_pressed = false;
      return res;
    }
    return last_click_type;
}

/////////////////////////////////////////////////////////////////

clickType Button2::wait(bool keepState /* = false */) {
    while(!wasPressed()) {
      loop();
    }
    return read(keepState);
}

/////////////////////////////////////////////////////////////////

void Button2::waitForClick(bool keepState /* = false */) {
  do {
    while(!wasPressed()) {
      loop();
    }
  } while(read() != single_click);
}

/////////////////////////////////////////////////////////////////

void Button2::waitForDouble(bool keepState  /* = false */) {
  do {
    while(!wasPressed()) {
      loop();
    }
  } while(read() != double_click);
}

/////////////////////////////////////////////////////////////////

void Button2::waitForTriple(bool keepState /* = false */) {
  do {
    while(!wasPressed()) {
      loop();
    }
  } while(read() != triple_click);
}

/////////////////////////////////////////////////////////////////

void Button2::waitForLong(bool keepState  /* = false */) {
  do {
    while(!wasPressed()) {
      loop();
    }
  } while(read() != long_click);
}

/////////////////////////////////////////////////////////////////

byte Button2::_getState() {
  if (get_state_cb != NULL) return get_state_cb();
  if (!is_capacitive) {
    return digitalRead(pin);
  } else {
    #if defined(ARDUINO_ARCH_ESP32)
      int capa = touchRead(pin);
      return capa < CAPACITIVE_TOUCH_THRESHOLD ? LOW : HIGH;
    #endif
  }
  return state;
}

/////////////////////////////////////////////////////////////////

void Button2::loop() {
  if (pin != UNDEFINED_PIN) {
    unsigned long now = millis();
    prev_state = state;
    state = _getState();
    
    // is button pressed?
    if (state == _pressedState) {
      // is it pressed now?
      if (prev_state != _pressedState) {
        down_ms = now;
        pressed_triggered = false;
        click_ms = down_ms;
      // trigger pressed event (after debounce has passed)
      } else if (!pressed_triggered && (now - down_ms >= debounce_time_ms)) {
        pressed_triggered = true;
        click_count++;
        if (change_cb != NULL) change_cb (*this);      
        if (pressed_cb != NULL) pressed_cb (*this);
      }
      // is a longpress detected callback defined?
      if (longclick_detected_cb != NULL) {
        // check to see that the longclick_ms period has been exceeded and call the appropriate callback
        bool longclick_period_detected = now - down_ms >= (longclick_time_ms * (longclick_detected_counter + 1));
        if (longclick_period_detected && !longclick_detected_reported) {
          longclick_detected_reported = true;
          longclick_detected = true;
          if (longclick_detected_retriggerable) {
            // increate the counter and reset the "reported" flag (as the counter will stop the false trigger)
            longclick_detected_counter++;
            longclick_detected_reported = false;
          }
          if (longclick_detected_cb != NULL) longclick_detected_cb(*this);
        }
      }

    // is the button released?
    } else if (state != _pressedState) {
      // is it released right now?
      if (prev_state == _pressedState) {
        down_time_ms = now - down_ms;
        // is it beyond debounce time?
        if (down_time_ms >= debounce_time_ms) {
          last_click_type = single_click;
          // trigger release        
          if (change_cb != NULL) change_cb (*this);
          if (released_cb != NULL) released_cb (*this);
          // trigger tap
          if (tap_cb != NULL) tap_cb (*this);        
          // was it a longclick? (preceeds single / double / triple clicks)
          if (down_time_ms >= longclick_time_ms) {
            longclick_detected = true;
          }
        }
      // is the button released and the time has passed for multiple clicks?
      } else if (now - click_ms > doubleclick_time_ms) {
        // was there a longclick?
        if (longclick_detected) {
          // was it part of a combination?
          if (click_count == 1) {
            last_click_type = long_click;
            if (long_cb != NULL) long_cb (*this);
            was_pressed = true;
          }
          
  //增加此选项: 点按后紧接着长按, 触发此事件
  //Add for click once and then long click
          else if (click_count == 2) {
            last_click_type = combo_long_click;
            if (combo_long_cb != NULL) combo_long_cb (*this);
            was_pressed = true;
          }
          longclick_detected = false;
          longclick_detected_reported = false;
          longclick_detected_counter = 0;
        // determine the number of single clicks
        } else if (click_count > 0) {
          switch (click_count) {
            case 1: 
              last_click_type = single_click;
              if (click_cb != NULL) click_cb (*this);
              break;
            case 2: 
              last_click_type = double_click;
              if (double_cb != NULL) double_cb (*this);
              break;
            case 3: 
              last_click_type = triple_click;
              if (triple_cb != NULL) triple_cb (*this);
              break;
          }
          was_pressed = true;
        }
        // clean up
        click_count = 0;
        click_ms = 0;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////

void Button2::reset() {
  pin = UNDEFINED_PIN;
  click_count = 0;
  last_click_type = empty;
  down_time_ms = 0;
  pressed_triggered = false;
  longclick_detected = false;
  longclick_detected_reported = false;
  longclick_detected_counter = 0;
  
  pressed_cb = NULL;
  released_cb = NULL;
  change_cb = NULL;
  tap_cb = NULL;
  click_cb = NULL;
  long_cb = NULL;
  double_cb = NULL;
  triple_cb = NULL;
  longclick_detected_cb = NULL;
}

/////////////////////////////////////////////////////////////////
