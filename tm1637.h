
#ifndef TM1637_H_
#define TM1637_H_

#include "main.h"

extern const uint8_t TM1637_digitToSegment[];
uint8_t TM1637_brightness_reg;
uint8_t flag_dot ;

#define TM1637_DIGITS_COUNT    4
#define TM1637_MAX_BRIGHTNESS  7

#define TM1637_DDR  DDRD
#define TM1637_PORT PORTD
#define TM1637_PIN  PIND
#define TM1637_DIO  PD7
#define TM1637_CLK  PD6

#define TM1637_CMD_SETUP           0b01000000
#define TM1637_CMD_SET_DATA        0b11000000
#define TM1637_CMD_SET_BRIGHTNESS  0b10000000

//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     --- .
//      D

//=== Decimal digits
//                  .GFEDCBA
#define TM1637_0  0b00111111
#define TM1637_1  0b00000110
#define TM1637_2  0b01011011
#define TM1637_3  0b01001111
#define TM1637_4  0b01100110
#define TM1637_5  0b01101101
#define TM1637_6  0b01111101
#define TM1637_7  0b00000111
#define TM1637_8  0b01111111
#define TM1637_9  0b01101111
#define TM1637_minus 0b01000000
#define TM1637_dot 0b10000000

void TM1637_init(void);
void TM1637_start(void);
void TM1637_stop(void);

void TM1637_turnOnOff(uint8_t on);
void TM1637_turnOn(void);
void TM1637_turnOff(void);

/** Set the display brightness (brightness range: 0-7) **/
void TM1637_setBrightness(uint8_t brightness);

/** Turn the display on and set its brightness (brightness range: 0-7) in a more performant
 *  way than calling TM1637_turnOn and TM1637_setBrightness subsequently **/
void TM1637_turnOnAndSetBrightness(uint8_t brightness);

/** Display raw segments data, starting at given digit/position **/
void TM1637_setSegments(uint8_t segments[], uint8_t length, uint8_t pos);

/** Display a number in a given numerical system (supported bases: 2-16) **/
 uint8_t TM1637_displayNumber(int32_t num);

/** Clear the display - turn off all segments **/
void TM1637_clear(void);



#endif /* TM1637_H_ */