#include "main.h"
#include "encoder.h"

void InitEncoder(void){
	DDRC&=~(1<<pin_A);// encoder pins to the input
	DDRC&=~(1<<pin_B);
	inputEnc=0;
	inputEnc_old=0;
}

//return the encoder state in the form of flags
void EncoderState(void){
	
	(!(PINC & (1<<pin_A)))?(inputEnc|=(1<<0)):(inputEnc&=~(1<<0));
	(!(PINC & (1<<pin_B)))?(inputEnc|=(1<<1)):(inputEnc&=~(1<<1));
	inputEnc = inputEnc & 3;//output status of the encoder in the form of 00,01,10,11
	if(inputEnc_old != inputEnc){

		switch(inputEnc_old){
			case 0:{
				(inputEnc==2)? (flagEncRight=1):(flagEncRight=0);
				(inputEnc==1)? (flagEncLeft=1):(flagEncLeft=0);
				break;
			}
			case 1:{
				(inputEnc==0)? (flagEncRight=1):(flagEncRight=0);
				(inputEnc==3)? (flagEncLeft=1):(flagEncLeft=0);
				break;
			}
			case 2:{
				(inputEnc==3)? (flagEncRight=1):(flagEncRight=0);
				(inputEnc==0)? (flagEncLeft=1):(flagEncLeft=0);
				break;
			}
			case 3:{
				(inputEnc==1)? (flagEncRight=1):(flagEncRight=0);
				(inputEnc==2)? (flagEncLeft=1):(flagEncLeft=0);
				break;
			}
		}
		inputEnc_old = inputEnc;
		}else{
		flagEncRight=0;
		flagEncLeft=0;

	}

}
