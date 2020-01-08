/*
 * din.c
 *
 *  Created on: 2 џэт. 2020 у.
 *      Author: User
 */

#include "din.h"
#include "os_conf.h"
#include <stdint.h>

extern unsigned char din[DI_CNT];
uint8_t din_break[DI_CNT]={0};
uint8_t din_short_circuit[DI_CNT]={0};
uint8_t din_fault[DI_CNT]={0};

extern short ain[AI_CNT];
short break_level=40;
short input_on_level=128;
short short_circuit_level=255;

uint16_t di_state_reg = 0x0000;
uint16_t di_sh_circ_reg = 0x0000;
uint16_t di_break_reg = 0x0000;
uint16_t di_fault_reg = 0x0000;

extern uint8_t answer_91[28];

static void update_ethip_din() {
	uint8_t tmp=0;
	uint8_t bit_offset = 0;
	uint8_t byte_num = 0;
	uint8_t bit_num = 0;
	uint8_t copy_value = 0;
	for(tmp=0;tmp<DI_CNT;tmp++) {
		bit_offset = tmp*2;
		byte_num = bit_offset/8;
		bit_num = bit_offset % 8;
		copy_value = answer_91[byte_num];
		if(din_fault[tmp]) {
			copy_value |= 1<<bit_num;
			copy_value |= 1<<(bit_num+1);
		}else {
			if(din[tmp]==0)  {copy_value |= 1<<bit_num;copy_value &= ~((uint8_t)1<<(bit_num+1));}
			else {copy_value &= ~((uint8_t)1<<bit_num);copy_value &= ~((uint8_t)1<<(bit_num+1));}
		}
		answer_91[byte_num] = copy_value;
	}
}


void init_din(void) {
	uint8_t tmp=0;
	for(tmp=0;tmp<DI_CNT;tmp++) {
		din[tmp] = 0;
		din_break[tmp] = 0;
		din_short_circuit[tmp] = 0;
		din_fault[tmp] = 0;
	}
}

void update_din() {
	uint8_t tmp=0;
	uint16_t tmp_di_state_reg = 0x0000;
	uint16_t tmp_di_sh_circ_reg = 0x0000;
	uint16_t tmp_di_break_reg = 0x0000;
	uint16_t tmp_di_fault_reg = 0x0000;
	for(tmp=0;tmp<DI_CNT;tmp++) {
		if(ain[tmp]>=input_on_level) din[tmp]=1;else din[tmp]=0;
		if(ain[tmp]<=break_level) din_break[tmp]=1;else din_break[tmp]=0;
		if(ain[tmp]>=short_circuit_level) din_short_circuit[tmp]=1;else din_short_circuit[tmp]=0;
		if(din_break[tmp] || din_short_circuit[tmp]) din_fault[tmp] = 1;else din_fault[tmp]=0;
		if(din[tmp]) tmp_di_state_reg |= (uint16_t)1<<tmp;
		if(din_short_circuit[tmp]) tmp_di_sh_circ_reg |= (uint16_t)1<<tmp;
		if(din_break[tmp]) tmp_di_break_reg |= (uint16_t)1<<tmp;
		if(din_fault[tmp]) tmp_di_fault_reg |= (uint16_t)1<<tmp;
	}
	di_state_reg = tmp_di_state_reg;
	di_sh_circ_reg = tmp_di_sh_circ_reg;
	di_break_reg = tmp_di_break_reg;
	di_fault_reg = tmp_di_fault_reg;
	update_ethip_din();
}

