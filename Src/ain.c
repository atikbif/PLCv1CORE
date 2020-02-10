/*
 * ain.c
 *
 *  Created on: 8 џэт. 2020 у.
 *      Author: User
 */

#include "ain.h"
#include <stdint.h>
#include "os_conf.h"

extern short ain[AI_CNT];
extern uint16_t ai_type;
extern uint8_t answer_90[246];

void update_ethip_ain() {
	uint8_t i = 0;
	for(i=0;i<AI_CNT;i++) {
		if(ai_type & ((uint16_t)1<<i)) {answer_90[i*2] = ain[i]/100;}	// mA
		else { answer_90[i*2] = ain[i]/10; }	// mV
		answer_90[i*2+1] = 0xFF;
	}
}
