/*
 * can_task.c
 *
 *  Created on: 22 мар. 2020 г.
 *      Author: User
 */

#include "can_task.h"
#include "cmsis_os.h"
#include "main.h"
#include "os_conf.h"
#include "can_tx_stack.h"

extern CAN_HandleTypeDef hcan1;
static CAN_RxHeaderTypeDef   RxHeader;
static uint8_t               RxData[8];

static CAN_TxHeaderTypeDef   TxHeader;
static uint32_t              TxMailbox=0;
static uint8_t               TxData[8];

#define HEARTBEAT_MAX	3

uint8_t heartbeat_cnt[8] = {HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX,HEARTBEAT_MAX};
uint8_t update_all = 1;
uint16_t update_tmr = 0;
uint16_t update_di = 0x0000;
uint16_t update_ai = 0x0000;

extern uint16_t ai_type;
extern uint16_t used_ai;

extern unsigned short ain_raw[AI_CNT];
extern unsigned short ain[AI_CNT];
extern unsigned char ain_alarm[AI_CNT];

extern unsigned char din[DI_CNT];
extern uint8_t din_fault[DI_CNT];

extern const char* di_names[14];
extern const char* do_names[6];
extern const char* adc_names[14];

extern uint8_t tdu[14];

extern tx_stack can1_tx_stack;
extern uint16_t app_id;
extern uint8_t can_addr;

static void can_write_from_stack() {
	tx_stack_data packet;
	uint8_t i = 0;
	uint8_t try = 0;
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=0) {
		try++;
		if(try>=10) return;
		if(get_tx_can_packet(&can1_tx_stack,&packet)) {
			if(packet.length>8) continue;
			TxHeader.StdId = packet.id;
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxHeader.DLC = packet.length;
			for(i=0;i<packet.length;++i) TxData[i] = packet.data[i];
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
		}else break;
	}
}

static void initCANFilter() {
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
}

static void update_di_data() {
	static uint16_t di_tmr=0;
	uint8_t di_mask = 0x00;
	uint8_t send_fault = 0x00;
	uint8_t send_state = 0x00;
	uint16_t di_fitted = 0x0000;
	uint8_t i = 0;

	tx_stack_data packet;

	di_fitted = ai_type & 0x3FFF;
	di_fitted &= ~used_ai;
	di_tmr++;
	if(di_tmr==20) {
		di_mask = update_di & di_fitted & 0xFF;
		if(di_mask)  {
			for(i=0;i<8;i++) {
				if(di_mask & (1<<i)) {
					if(din[i]) send_state |= 1<<i;
					if(din_fault[i]) send_fault |= 1<<i;
				}
			}

			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 5;
			packet.data[0] = 0x01; // packed physical digits
			packet.data[1] = 0x01; // start bit
			packet.data[2] = send_state; // state
			packet.data[3] = send_fault; // fault
			packet.data[4] = di_mask; // mask
			add_tx_can_packet(&can1_tx_stack,&packet);
			update_di &= 0xFF00;
		}
	}else if(di_tmr==40) {
		di_mask = ((update_di & di_fitted)>>8) & 0xFF;
		if(di_mask)  {
			HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin);
			for(i=0;i<8;i++) {
				if(i+8>=DI_CNT) break;
				if(di_mask & (1<<i)) {
					if(din[i+8]) send_state |= 1<<i;
					if(din_fault[i+8]) send_fault |= 1<<i;
				}
			}

			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 5;
			packet.data[0] = 0x01; // packed physical digits
			packet.data[1] = 0x09; // start bit
			packet.data[2] = send_state; // state
			packet.data[3] = send_fault; // fault
			packet.data[4] = di_mask; // mask
			add_tx_can_packet(&can1_tx_stack,&packet);
			update_di &= 0x00FF;
		}
		di_tmr=0;
	}
}

static void update_ai_data() {
	static uint16_t ai_tmr=0;
	static uint8_t ai_num = 0;
	static const uint8_t ai_max_num = 14;

	tx_stack_data packet;

	ai_tmr++;
	if(ai_tmr>=50) {
		ai_tmr=0;
		for(;;) {
			if((used_ai & (1<<ai_num)) && (update_ai & (1<<ai_num))) {

				packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
				packet.length = 8;
				packet.data[0] = 0x05; // Analogue data scaled with status
				packet.data[1] = ai_num + 1; // inputs number
				packet.data[2] = ain[ai_num]; // ain value
				packet.data[3] = tdu[ai_num]; // tdu type
				if(ain_alarm[ai_num]) {
					packet.data[4] = 0x02; // alarm bits
					packet.data[5] = 0x00;
				}else {
					packet.data[4] = 0x00; // alarm bits
					packet.data[5] = 0x00;
				}
				packet.data[6] = ain_raw[ai_num] & 0xFF; // raw value
				packet.data[7] = ain_raw[ai_num] >> 8;
				add_tx_can_packet(&can1_tx_stack,&packet);
				update_ai &= ~(1<<ai_num);
				break;
			}else {
				ai_num++;
				if(ai_num>=ai_max_num) {ai_num=0;break;}
			}
		}
	}
}

static void update_all_data() {
	uint16_t di_fitted = 0;
	tx_stack_data packet;
	update_tmr++;
	switch(update_tmr) {
		case 10:	// network status
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 3;
			packet.data[0] = 0x0D; // request not fragmented, eoid - 0x0D
			packet.data[1] = 0x01; // cluster number
			packet.data[2] = 0x00; // not networked
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 20:	// module data, internal faults
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x09; // internal faults
			packet.data[2] = 0x00; // faults value
			packet.data[3] = 0x00; // faults value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 30:	// module data, analogue o/p fitted
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x08; // analogue o/p fitted
			packet.data[2] = 0x00; // value
			packet.data[3] = 0x00; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 40:	// module data, relay o/p fitted
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x07; // relay o/p fitted
			packet.data[2] = 0x3F; // value
			packet.data[3] = 0x00; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 50:	// module data, switch i/p fitted
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x06; // switch i/p fitted
			packet.data[2] = 0x00; // value
			packet.data[3] = 0x00; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 60:	// module data, digital i/p fitted
			di_fitted = ai_type & 0x3FFF;
			di_fitted &= ~used_ai;
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x05; // digital i/p fitted
			packet.data[2] = di_fitted & 0xFF; // value
			packet.data[3] = di_fitted >> 8; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 70:	// module data, analogue i/p fitted
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x04; // analogue i/p fitted
			packet.data[2] = 0xFF; // value
			packet.data[3] = 0x3F; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 80:	// module data, os version
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 8;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x02; // os version
			packet.data[2] = 0x30; // value
			packet.data[3] = 0x31; // value
			packet.data[4] = 0x2E; // value
			packet.data[5] = 0x34; // value
			packet.data[6] = 0x30; // value
			packet.data[7] = 0x00; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 90:	// module data, bootloader version
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 8;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x01; // bootloader version
			packet.data[2] = 0x30; // value
			packet.data[3] = 0x31; // value
			packet.data[4] = 0x2E; // value
			packet.data[5] = 0x30; // value
			packet.data[6] = 0x37; // value
			packet.data[7] = 0x00; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 100:	// module data, application cn
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 4;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x03; // application cn
			packet.data[2] = app_id & 0xFF; // value
			packet.data[3] = app_id >> 8; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 110:	// module data, module type
			packet.id = 0x0400 | 0x07 | (can_addr<<3);	// event
			packet.length = 3;
			packet.data[0] = 0x1F; // request not fragmented, eoid - 0x1F
			packet.data[1] = 0x00; // module type
			packet.data[2] = 0x01; // value
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 120:	// display tx mask digital i/p
			di_fitted = ai_type & 0x3FFF;
			di_fitted &= ~used_ai;
			packet.id = 0x0400 | 0x06 | (can_addr<<3);	// event
			packet.length = 5;
			packet.data[0] = 0x0A; // tx mask, eoid - 0x0A
			packet.data[1] = 0x00; // display tx mask
			packet.data[2] = di_fitted & 0xFF; // value
			packet.data[3] = di_fitted >> 8; // value
			packet.data[4] = 0x01; // io type - digital i/p
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
		case 130:	// display tx mask analogue i/p
			packet.id = 0x0400 | 0x06 | (can_addr<<3);	// event
			packet.length = 5;
			packet.data[0] = 0x0A; // tx mask, eoid - 0x0A
			packet.data[1] = 0x00; // display tx mask
			packet.data[2] = used_ai & 0xFF; // value
			packet.data[3] = used_ai >> 8; // value
			packet.data[4] = 0x00; // io type - analogue i/p
			add_tx_can_packet(&can1_tx_stack,&packet);
			break;
	}
	if(update_tmr>=200) {update_tmr=0;update_all=0;update_di=0x3FFF;update_ai=0x3FFF;}
}

void canTask(void const * argument) {
	uint16_t cnt = 0;
	uint16_t heartbeat_tmr = 0;
	uint8_t heartbeat_value = 1;
	uint16_t i = 0;
	uint16_t inp_tmr=0;
	tx_stack_data packet;
	initCANFilter();
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	for(;;) {
		cnt++;
		if(cnt>=500) {
			cnt = 0;

			packet.id = 0x0400 | 0x01 | (can_addr<<3);
			packet.length = 2;
			packet.data[0] = 0x49;
			packet.data[1] = heartbeat_value++;
			add_tx_can_packet(&can1_tx_stack,&packet);
		}
		heartbeat_tmr++;
		if(heartbeat_tmr>=1000) {
			heartbeat_tmr = 0;
			for(i=0;i<sizeof(heartbeat_cnt);i++) {
				if(heartbeat_cnt[i]<HEARTBEAT_MAX) heartbeat_cnt[i]++;
			}
		}
		if(update_all) update_all_data();
		update_ai_data();
		update_di_data();
		inp_tmr++;
		if(inp_tmr==30000) {
			update_di=0x3FFF;
		}
		else if(inp_tmr>=60000) {
			inp_tmr = 0;
			update_ai=0x3FFF;
		}
		can_write_from_stack();
		osDelay(1);
	}
}

void sendIOName(uint8_t ioNum, uint8_t type, uint8_t req_node, uint8_t req_num) {
	uint8_t name[20]={0};
	uint8_t i = 0;
	switch(type) {
		case 0:	// analogue input
			if(ioNum>=1 && ioNum<=14) {for(i=0;i<sizeof(adc_names[ioNum-1])-1;i++) name[i] = adc_names[ioNum-1][i];}
			break;
		case 1: // digital input
			if(ioNum>=1 && ioNum<=14) {for(i=0;i<sizeof(di_names[ioNum-1])-1;i++) name[i] = di_names[ioNum-1][i];}
			break;
		case 3: // relay output
			if(ioNum>=1 && ioNum<=6) {for(i=0;i<sizeof(do_names[ioNum-1])-1;i++) name[i] = do_names[ioNum-1][i];}
			break;
	}

	tx_stack_data packet;
	packet.id = (req_node<<3) | 0x05 | (can_addr<<3);
	packet.length = 8;
	packet.data[0] = (0x03<<5) | 0x0b; // ss-0x05 (fragmented response) eoid-0x0b(read name)
	packet.data[1] = req_num;
	packet.data[2] = 1; // part num
	for(i=0;i<5;i++) packet.data[3+i] = name[i];
	add_tx_can_packet(&can1_tx_stack,&packet);

	packet.data[1] = req_num;
	packet.data[2] = 2; // part num
	for(i=0;i<5;i++) packet.data[3+i] = name[i+5];
	add_tx_can_packet(&can1_tx_stack,&packet);

	packet.data[1] = req_num;
	packet.data[2] = 3; // part num
	for(i=0;i<5;i++) packet.data[3+i] = name[i+10];
	add_tx_can_packet(&can1_tx_stack,&packet);

	packet.data[1] = req_num;
	packet.data[2] = 4; // part num
	for(i=0;i<5;i++) packet.data[3+i] = name[i+15];
	add_tx_can_packet(&can1_tx_stack,&packet);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t srv = 0;
	uint8_t node = 0;
	uint8_t ss = 0;
	uint8_t eoid = 0;
	uint8_t dir = 0;
	uint8_t addr = 0x00;
	if(hcan==&hcan1) {
		if(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0)) {
			if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
				//HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin);
				srv = RxHeader.StdId & 0x07;
				node = (RxHeader.StdId>>3) & 0x0F;
				eoid = RxData[0] & 0x1F;
				ss = (RxData[0] >> 5) & 0x07;
				dir = (RxData[0] >> 10) & 0x01;
				addr = RxData[1];
				if(dir==0x00 && node==can_addr && ss==0x01 && eoid==0x0b) { // read name request
					uint8_t num = RxData[2];
					uint8_t type = RxData[4];
					uint8_t req_node = RxData[5];
					sendIOName(num,type,req_node,addr);
				}
				if(srv==0x01) { // heartbeat
					if(node<8) {
						if(heartbeat_cnt[node]==HEARTBEAT_MAX) {update_all = 1;update_tmr = 0;}
						heartbeat_cnt[node]=0;
					}
				}
			}
		}
	}
}
