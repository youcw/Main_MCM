#ifndef __S5PC210TQINPUT_H__
#define __S5PC210TQINPUT_H__
#include <regs.h>
#define rADC_CONTROL	__REG(0xE010E818)
#define rCLK_GATE_IP3	__REG(0xE010046C)
//GPH KEY0~5 GPH0 0~5
#define rGPH0CON	__REG(0xE0200C00)
#define rGPH0DAT	__REG(0xE0200C04)
#define rGPH0PUD	__REG(0xE0200C08)



#define USER_ADC_12BIT_MODE	0

#if(USER_ADC_12BIT_MODE == 1)
#define ADC_RES_MODE 		(1<<16)
#else
#define ADC_RES_MODE 		(0<<16)
#endif
typedef struct{
	int x;
	int y;
}Point;
void tq_touch_init(void);
void tq_test_button(void);
unsigned char tq_input_sys(void);
unsigned char get_button_value(void);
#define tq_button_init() {(rGPH0CON &= ~0xffffff);(rGPH0PUD = (rGPH0PUD &(~0xfff)) | 0xaaa);}
#define KEY0  	(1<<0)
#define KEY1	(1<<1)
#define KEY2  	(1<<2)
#define KEY3	(1<<3)
#define KEY4  	(1<<4)
#define KEY5	(1<<5)

#endif
