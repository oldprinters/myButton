#include "button.h"

Button::Button(int16_t p, uint32_t lP, uint32_t sp): Timer(1500), pin(p), longPress(lP), shotPress(sp) {
  pinMode(pin, INPUT_PULLDOWN);
  postPress.setDt(longPress);
}
//************************************************
void Button::press_button(){
  if(!firstPress && postPress.getTimer()){
    setTimer(shotPress);
    tTime = millis();
    firstPress = true;
  } else {
    if((millis() - tTime) < 800){
      fDouble();
      setTimer(-1);                //сброс таймеров
      firstPress = false;
      postPress.setTimer(longPress);
    }
  }
}
//**********************************************
void Button::cycle(){
  if(firstPress && getTimer() && postPress.getTimer()){
    firstPress = false;
    if(digitalRead(pin))
      fLong();
    else
      fShort();
    postPress.setTimer(longPress);
  }
}
