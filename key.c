#include "key.h"
#include "main.h"
void BtnInit(void){
	DDRC &=~(1<<3);
	PORTC |=(1<<3);
	keyTemp1=0x00;
	keyTemp2=0x00;

}

void GetKeyCode(void){
	//uint8_t ret = 0;
	static uint8_t lev = 0;
	cnt_but++;
	if(cnt_but>251){cnt_but=250;}
	if( lev == 0){
		(!(PINC & (1<<3)))?(keyTemp1 |=(1<<0)):(keyTemp1 &=~(1<<0));
		lev = 1;
		}else if (lev == 1){
		(!(PINC & (1<<3)))?(keyTemp2 |=(1<<0)):(keyTemp2 &=~(1<<0));
		if ((keyTemp1==1)&&(keyTemp2==1)){
			flagButPress1 = 1;
		}
		lev=0;
	}
	
	//return ret;
}
