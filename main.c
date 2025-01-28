

#include "main.h"

void timer2_init(void){
	TCCR2A |=(1<<WGM21);
	TCCR2B |=(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK2 |=(1<<OCIE2A);//|(1<<OCIE2B);
	OCR2A = 77;//1024*(1+77)/8000000=0.01
	//OCR2B = 77;
}
void USART_init(void){
	UBRR0H = 0;
	UBRR0L = 51;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(1<<UCSZ00);
}
void USART_transmit(uint8_t d){
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = d;
}

ISR (TIMER2_COMPA_vect){
	if(cnt1) cnt1--;
	flagKey = 1;
	flagEnc = 1;
	if(cnt2) cnt2--;
	if(cnt3) cnt3--;
	if(cnt4) cnt4--;
}

int main(void)
{
	timer2_init();
	TM1637_init();
	USART_init();
	InitEncoder();
	BtnInit();
	DDRD |=(1<<LED);
	DDRD |=(1<<2);
	DDRD |=(1<<3);
	DDRD |=(1<<5);

	
	num = EEPROM_read(1);
	
	TM1637_turnOnAndSetBrightness(1);
	TM1637_setSegments((uint8_t[]) { 0, 0, 0, TM1637_0 }, 4, 0);
	TM1637_displayNumber(num);
	
	sei();
	
	while (1)
	{
		if(cnt1==0){PORTD ^= (1<<LED);
			//flag_dot = !flag_dot;
		cnt1=100;}
		
		if(flagCNT){
			if(cnt2==0){
				num--;
				if(num==0){flagBOOM=1;flagCNT=0;}
					else{cnt2=100;}
				}
		}
		
		if (flagEnc) {EncoderState();flagEnc=0;}//check the encoder every 10ms

		if (flagEncRight){
			kr ++;
			if(kr>5){
				num++;
				if(num > 99){num = 0;}
				kr = 0;
			}
		}
		
		if (flagEncLeft){
			kl ++;
			if(kl>5){
				num--;
				if(num < 0){num = 99;}
				kl = 0;
			}
		}
		
		if(flagEncRight==0) {kr = 0;}
		if(flagEncLeft==0) {kl = 0;}
		
		TM1637_displayNumber(num);
		
		if (flagKey) {flagKey=0;GetKeyCode();}//check the button every 10 ms
			
		if(PINC & (1<<3)){cnt_but = 0;}//resetting the long press counter
			
		if((flagButPress1)&&(PINC & (1<<3))){
			(num==0)?(num = EEPROM_read(1)):(EEPROM_write(1 , num));
			flagCNT = ! flagCNT;
			cnt2 = num;
			flagBOOM = 0;
			flagButPress1=0;
			flagButPressLong1 = 0;
			
			}else if((flagButPress1)&&(!(PINC & (1<<3)))&&(cnt_but>250)){
				flagButPress1 = 0;flagButPressLong1 =1;
				}
			
			if((flagButPressLong1)&&(!(PINC & (1<<3)))){
				PORTD ^= (1<<3);
				num = 0;
				EEPROM_write(1 , num);
				flagCNT = 0;
				flagBOOM = 0;
				flagButPressLong1 = 0;
			}
			
			if(flagBOOM){
				
				if(cnt3==0){
				cnt_boom++;
				PORTD ^= (1<<2);
				sound(5, 759);
				cnt3=5;
				}
				if(cnt_boom > 100){flagBOOM = 0;PORTD &=~(1<<2);cnt_boom = 0;}
			}

		}
	}
	
	
void del_us(uint16_t i){while(--i){asm("NOP");asm("NOP");asm("NOP");asm("NOP");}}//delay 1 us

void sound(uint8_t time, uint16_t fs){cnt4=time;while(cnt4){PORTD^=(1<<5);del_us(fs);}PORTD &=~(1<<5);}


