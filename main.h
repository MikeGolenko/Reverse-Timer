#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "tm1637.h"
#include "encoder.h"
#include "key.h"
#include "eeprom.h"

#define LED 4



volatile uint8_t cnt1,cnt2,cnt3,cnt4;
uint8_t flagKey ;
uint8_t flagEnc, flagCNT, flagBOOM, cnt_boom;;
uint8_t kr,kl;
uint8_t cnt_enc_r,cnt_enc_l,e_dat;
int8_t num;

void del_us(uint16_t i);//1us delay
void sound (uint8_t time, uint16_t fs);//note function



#endif /* MAIN_H_ */