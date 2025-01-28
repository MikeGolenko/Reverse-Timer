
#ifndef KEY_H_
#define KEY_H_

#include "main.h"

#define btn1_pin 3

uint8_t keyTemp1;
uint8_t keyTemp2;

uint8_t cnt_but, flagButPress1, flagButPressLong1;


void GetKeyCode(void);
void BtnInit(void);




#endif /* KEY_H_ */