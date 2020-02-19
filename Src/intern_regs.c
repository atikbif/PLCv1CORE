/*
 * intern_regs.c
 *
 *  Created on: 5 февр. 2020 г.
 *      Author: User
 */

#include <stdint.h>
#include "os_conf.h"

extern unsigned short ireg[IREG_CNT];
extern uint8_t answer_95[128];
extern uint8_t answer_94[28];
extern unsigned char ibit[IBIT_CNT];

void update_ethip_intern_regs() {
	uint8_t i = 0;
	for(i=0;i<64;i++) {
		answer_95[i*2] = ireg[i]&0xFF;
		answer_95[i*2+1] = ireg[i]>>8;
	}
}

void update_ethip_intern_bits() {
	uint8_t i = 0;
	uint8_t byte_num;
	for(i=0;i<64;i++) {
		byte_num = i/8;
		if(ibit[i]) answer_94[byte_num] |= 1<<(i%8);
		else answer_94[byte_num] &= ~(1<<(i%8));
	}
}
