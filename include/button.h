#ifndef BUTTON_H
#define BUTTON_H
#include "Timer.h"
enum class PRESS_TYPE { NONE, ONE, DOUBLE, LONG };

class Button : public Timer {
  int pin;
  uint32_t *statBut;
  uint32_t tTime;
  uint32_t longPress;
  uint32_t shotPress;
  Timer postPress;
  bool firstPress{};  //первое нажатие
  void (*fDouble)();
  void (*fLong)();
  void (*fShort)();
public:
  Button(int16_t p, uint32_t longPress = 2000, uint32_t sp = 800);
  void press_button();

  void cycle();
};
#endif
