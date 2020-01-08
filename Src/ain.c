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
uint8_t answer_90[246];

void update_ethip_ain() {
	uint8_t i = 0;
	for(i=0;i<AI_CNT;i++) {
		if(ai_type & ((uint16_t)1<<i)) {	// mA
			answer_90[i*2] = ain[i]*5/62;
			answer_90[i*2+1] = 0xFF;
		}else {	// mV
			answer_90[i*2] = ain[i]/10;
			answer_90[i*2+1] = 0xFF;
		}
	}
}
