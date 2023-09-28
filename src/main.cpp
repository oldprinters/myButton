#include <Arduino.h>
#include "Button.h"
#include "Timer.h"

const int16_t PIN_BUTTON{4};
const int16_t PIN_LED{2};
const int16_t DREBEZG{50};
const int32_t TIME_SHOT{350};
const int32_t TIME_CLICK{700};

volatile int buttonStatus_i{}, ft_i{};
volatile uint32_t buttonTime_i{}, t_pause{}, t_wait{};

int16_t nClicks{};
Timer t1(500);
Button button_I(PIN_BUTTON);

//*********************************************
void IRAM_ATTR button_interr_i(){ 
  if(!ft_i){
    ft_i = 1;
    buttonTime_i = millis();
  } 
  t_pause = millis();
}
//---------------------------------------------
void blink(int16_t n, bool zd = 0){
  Timer t1(200);
  for(int i = 0; i < n; i++){
    t1.setTimer();
    digitalWrite(PIN_LED, HIGH);
    while(!t1.getTimer());
    digitalWrite(PIN_LED, LOW);
    if(zd){
      t1.setTimer();
      while(!t1.getTimer());
    }
  }
}
//---------------------------------------------
int16_t getPressButton(){
  if(ft_i){
    int32_t t_click = millis();
    if(t_click - t_pause > DREBEZG){
      if(digitalRead(PIN_BUTTON) == HIGH){
          if(t_click - buttonTime_i < TIME_SHOT){
              buttonTime_i = t_click;
          } else {
            buttonStatus_i = 2;
          }
          nClicks++;
          ft_i = 0;
      } 
    }
  } else if(nClicks > 0 && millis() - buttonTime_i > TIME_CLICK){
    buttonStatus_i = 1;
  }
  return buttonStatus_i;
}
//---------------------------------------------
void clearButton(){
  buttonStatus_i = 0;
  nClicks = 0;
  ft_i = 0;
}
//*********************************************
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  blink(3, true);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), button_interr_i, CHANGE);
}
//*********************************************
void loop() {
  int16_t res = getPressButton();
  if( res > 0 ){
    switch(res){
      case 1: blink(nClicks, 1); break;
      case 2: blink(8); break;
    }
    clearButton();
  }
}
