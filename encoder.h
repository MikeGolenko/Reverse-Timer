
#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"
#define pin_A  1
#define pin_B  2

uint8_t inputEnc;
uint8_t inputEnc_old;
uint8_t flagEncRight;
uint8_t flagEncLeft;


void InitEncoder(void);
void EncoderState(void);



#endif /* ENCODER_H_ */