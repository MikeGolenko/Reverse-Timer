#include "tm1637.h"

const uint8_t TM1637_digitToSegment[] = {
	TM1637_0,
	TM1637_1,
	TM1637_2,
	TM1637_3,
	TM1637_4,
	TM1637_5,
	TM1637_6,
	TM1637_7,
	TM1637_8,
	TM1637_9,
  /*TM1637_A,
	TM1637_b,
	TM1637_C,
	TM1637_d,
	TM1637_E,
	TM1637_F*/
};

static inline uint8_t TM1637_writeByte(uint8_t data) {
	// Write data byte
	for (uint8_t i = 0; i < 8; i++) {
		TM1637_DDR |=  (1 << TM1637_CLK);
		_delay_us(10);
		
		    if (data & 1) TM1637_DDR &= ~(1 << TM1637_DIO);
		    else TM1637_DDR |=  (1 << TM1637_DIO);
		    _delay_us(20);
			
			    TM1637_DDR &= ~(1 << TM1637_CLK);
			    _delay_us(20);
			    data >>= 1;
		    }
			
	  // Prepare for receiving acknowledgement
	  TM1637_DDR |=  (1 << TM1637_CLK);
	  TM1637_DDR &= ~(1 << TM1637_DIO);
	  TM1637_DDR |=  (1 << TM1637_DIO);

	  // Read acknowledgement
	  TM1637_DDR &= ~(1 << TM1637_CLK);
	  _delay_us(10);
	  uint8_t ack = TM1637_PIN &(1<<TM1637_DIO);
	  if (ack == 0)                     // Not strictly necessary, but it's a good idea
	  TM1637_DDR |=  (1 << TM1637_DIO);  // to avoid unnecessary voltage changes on DIO when possible
	  _delay_us(10);

	  return ack;
  }
  void TM1637_start(void){
	  TM1637_DDR |= (1<<TM1637_DIO);
	  _delay_us(20);
  }
  void TM1637_stop(void){
	  	  TM1637_DDR |=  (1 << TM1637_CLK);
	  	  _delay_us(10);
	  	  TM1637_DDR |=  (1 << TM1637_DIO);
	  	  _delay_us(10);
	  	  TM1637_DDR &= ~(1 << TM1637_CLK);
	  	  _delay_us(20);
	  	  TM1637_DDR &= ~(1 << TM1637_DIO);
	  	  _delay_us(20);
  }
  
  void TM1637_init(void) {
	  TM1637_DDR &= ~(1 << TM1637_DIO);
	  TM1637_DDR &= ~(1 << TM1637_CLK);
	  TM1637_PORT &= ~((1 << TM1637_DIO) | (1 << TM1637_CLK));

	  // Write TM1637_CMD_SETUP
	  TM1637_start();
	  TM1637_writeByte(TM1637_CMD_SETUP);
	  TM1637_stop();
	   
	   
  }
  static inline void TM1637_writeBrightnessReg(void) {
	  // Write TM1637_CMD_SET_BRIGHTNESS + TM1637_brightness_reg
	  TM1637_start();
	  TM1637_writeByte(TM1637_CMD_SET_BRIGHTNESS | (TM1637_brightness_reg & 0b1111));
	  TM1637_stop();
  }
  static inline void TM1637_turnOnOff_inline(uint8_t on) {
	  TM1637_brightness_reg = (on ? 0b1000 : 0) | (TM1637_brightness_reg & 0b0111);
	  TM1637_writeBrightnessReg();
  }

  void TM1637_turnOnOff(uint8_t on) {
	  TM1637_turnOnOff_inline(on);
  }

  void TM1637_turnOn(void) {
	  TM1637_turnOnOff_inline(1);
  }

  void TM1637_turnOff(void) {
	  TM1637_turnOnOff_inline(0);
  }
  void TM1637_setBrightness(uint8_t brightness) {
	  TM1637_brightness_reg = (TM1637_brightness_reg & 0b1000) | (brightness & 0b0111);
	  TM1637_writeBrightnessReg();
  }

  void TM1637_turnOnAndSetBrightness(uint8_t brightness) {
	  TM1637_brightness_reg = 0b1000 | (brightness & 0b0111);
	  TM1637_writeBrightnessReg();
  }
  void TM1637_setSegments(uint8_t segments[], uint8_t length, uint8_t pos) {
	  TM1637_start();
	  // Write TM1637_CMD_SET_DATA + first digit address
	  TM1637_writeByte(TM1637_CMD_SET_DATA | (pos & 0b11));
	  // Write data bytes
	  for (uint8_t i = 0; i < length; i++)
	  TM1637_writeByte(segments[i]);
	  TM1637_stop();
  }
  void TM1637_clear(void) {
	  TM1637_start();
	  TM1637_writeByte(TM1637_CMD_SET_DATA);
	  // Write blank segment data bytes
	  for (uint8_t i = 0; i < 4; i++)
	  TM1637_writeByte(0);
	  TM1637_stop();
  }
  
  uint8_t TM1637_displayNumber(int32_t num) {
	  // Assume: 2 <= base <= 16
	  if (num == 0) {
		  TM1637_setSegments((uint8_t[]) { 0, 0, 0, TM1637_0 }, 4, 0);
		  return 0;
	  }

	  uint16_t abs_num = num < 0 ? -num : num;
	  // Extract digits from num
	  uint8_t data[4] = {
		  (abs_num / 1000) ,
		  (abs_num / 100) % 10,
		  ((abs_num / 10) % 100)%10,
		  abs_num % 10
	  };
	  // Convert digits to segments
	  uint8_t started = 0;
	  for (uint8_t i = 0; i < 4; i++) {
		  if (started || data[i]) {
			  data[i] = TM1637_digitToSegment[data[i]];
			  if (!started && num < 0)
			  data[i - 1] = TM1637_minus;
			  started = 1;
		  } else data[i] = 0;
	  }
	  if(flag_dot){data[1] = data[1] | 0b10000000;};
	  TM1637_setSegments(data, 4, 0);
	  return 0;
  }
