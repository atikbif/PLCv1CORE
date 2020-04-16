/*
 * scada.c
 *
 *  Created on: 16 апр. 2020 г.
 *      Author: User
 */

#include "scada.h"
#include <stdint.h>
#include "can_task.h"

extern uint8_t answer_96[16];
extern uint8_t answer_97[128];
extern uint8_t answer_98[128];
extern uint8_t answer_9b[2];

extern uint8_t net_bits[128];
extern uint16_t net_regs[128];

extern uint8_t heartbeat_cnt[MAX_NODE_CNT];
extern uint8_t net_heartbeat_cnt[MAX_NET_CNT];

void net_bits_to_scada_first() {
	uint8_t byte_num = 0;
	uint8_t bit_num = 0;
	for(uint8_t i=0;i<64;i++) {
		byte_num = i/8;
		bit_num = i%8;
		if(net_bits[i]) {
			answer_96[byte_num] |= 1<<bit_num;
		}else {
			answer_96[byte_num] &= ~(1<<bit_num);
		}
	}
}

void net_bits_to_scada_second() {
	uint8_t byte_num = 0;
	uint8_t bit_num = 0;
	for(uint8_t i=64;i<128;i++) {
		byte_num = i/8;
		bit_num = i%8;
		if(net_bits[i]) {
			answer_96[byte_num] |= 1<<bit_num;
		}else {
			answer_96[byte_num] &= ~(1<<bit_num);
		}
	}
}

void net_regs_to_scada_first() {
	for(uint8_t i=0;i<64;i++) {
		answer_97[i*2] = net_regs[i] & 0xFF;
		answer_97[i*2+1] = (net_regs[i]>>8)&0xFF;
	}
}

void net_regs_to_scada_second() {
	for(uint8_t i=0;i<64;i++) {
		answer_98[i*2] = net_regs[64+i] & 0xFF;
		answer_98[i*2+1] = (net_regs[64+i]>>8)&0xFF;
	}
}

void node_and_cluster_state_to_scada() {
	uint8_t node_state = 0;
	uint8_t clust_state = 0;
	for(uint8_t i=0;i<8;i++) {
		if(heartbeat_cnt[i]<HEARTBEAT_MAX) node_state |= 1 << i;
		if(net_heartbeat_cnt[i]<HEARTBEAT_MAX) clust_state |= 1 << i;
	}
	node_state|=0x80;	// имитация наличия модуля FE в скаде
	answer_9b[0] = node_state;
	answer_9b[1] = clust_state;
}
