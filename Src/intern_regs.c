/*
 * intern_regs.c
 *
 *  Created on: 5 февр. 2020 г.
 *      Author: User
 */

#include <stdint.h>
#include "os_conf.h"

extern short ireg[IREG_CNT];
extern uint8_t answer_95[128];

void update_ethip_intern_regs() {
	uint8_t i = 0;
	for(i=0;i<64;i++) {
		answer_95[i*2] = ireg[i]&0xFF;
		answer_95[i*2+1] = ireg[i]>>8;
	}
}

