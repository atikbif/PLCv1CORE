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
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 5;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x01; // packed physical digits
			TxData[1] = 0x01; // start bit
			TxData[2] = send_state; // state
			TxData[3] = send_fault; // fault
			TxData[4] = di_mask; // mask
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
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
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 5;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x01; // packed physical digits
			TxData[1] = 0x09; // start bit
			TxData[2] = send_state; // state
			TxData[3] = send_fault; // fault
			TxData[4] = di_mask; // mask
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			update_di &= 0x00FF;
		}
		di_tmr=0;
	}
}

static void update_ai_data() {
	static uint16_t ai_tmr=0;
	static uint8_t ai_num = 0;
	static const uint8_t ai_max_num = 14;
	ai_tmr++;
	if(ai_tmr>=50) {
		ai_tmr=0;
		for(;;) {
			if((used_ai & (1<<ai_num)) && (update_ai & (1<<ai_num))) {
				TxHeader.StdId = 0x0400 | 0x07;	// event
				TxHeader.ExtId = 0;
				TxHeader.RTR = CAN_RTR_DATA;
				TxHeader.IDE = CAN_ID_STD;
				TxHeader.DLC = 8;
				TxHeader.TransmitGlobalTime = DISABLE;
				TxData[0] = 0x05; // Analogue data scaled with status
				TxData[1] = ai_num + 1; // inputs number
				TxData[2] = ain[ai_num]; // ain value
				TxData[3] = 0x02; // tdu type
				if(ain_alarm[ai_num]) {
					TxData[4] = 0x02; // alarm bits
					TxData[5] = 0x00;
				}else {
					TxData[4] = 0x00; // alarm bits
					TxData[5] = 0x00;
				}
				TxData[6] = ain_raw[ai_num] & 0xFF; // raw value
				TxData[7] = ain_raw[ai_num] >> 8;

				HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);

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
	update_tmr++;
	switch(update_tmr) {
		case 10:	// network status
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 3;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x0D; // request not fragmented, eoid - 0x0D
			TxData[1] = 0x01; // cluster number
			TxData[2] = 0x00; // not networked
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 20:	// module data, internal faults
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x09; // internal faults
			TxData[2] = 0x00; // faults value
			TxData[3] = 0x00; // faults value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 30:	// module data, analogue o/p fitted
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x08; // analogue o/p fitted
			TxData[2] = 0x00; // value
			TxData[3] = 0x00; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 40:	// module data, relay o/p fitted
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x07; // relay o/p fitted
			TxData[2] = 0x3F; // value
			TxData[3] = 0x00; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 50:	// module data, switch i/p fitted
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x06; // switch i/p fitted
			TxData[2] = 0x00; // value
			TxData[3] = 0x00; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 60:	// module data, digital i/p fitted
			di_fitted = ai_type & 0x3FFF;
			di_fitted &= ~used_ai;
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x05; // digital i/p fitted
			TxData[2] = di_fitted & 0xFF; // value
			TxData[3] = di_fitted >> 8; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 70:	// module data, analogue i/p fitted
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x04; // analogue i/p fitted
			TxData[2] = 0xFF; // value
			TxData[3] = 0x3F; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 80:	// module data, os version
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 8;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x02; // os version
			TxData[2] = 0x30; // value
			TxData[3] = 0x31; // value
			TxData[4] = 0x2E; // value
			TxData[5] = 0x34; // value
			TxData[6] = 0x30; // value
			TxData[7] = 0x00; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 90:	// module data, bootloader version
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 8;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x01; // bootloader version
			TxData[2] = 0x30; // value
			TxData[3] = 0x31; // value
			TxData[4] = 0x2E; // value
			TxData[5] = 0x30; // value
			TxData[6] = 0x37; // value
			TxData[7] = 0x00; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 100:	// module data, application cn
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 4;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x03; // application cn
			TxData[2] = 0x10; // value
			TxData[3] = 0x27; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 110:	// module data, module type
			TxHeader.StdId = 0x0400 | 0x07;	// event
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 3;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x1F; // request not fragmented, eoid - 0x1F
			TxData[1] = 0x00; // module type
			TxData[2] = 0x01; // value
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 120:	// display tx mask digital i/p
			di_fitted = ai_type & 0x3FFF;
			di_fitted &= ~used_ai;
			TxHeader.StdId = 0x0400 | 0x06;	// action
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 5;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x0A; // tx mask, eoid - 0x0A
			TxData[1] = 0x00; // display tx mask
			TxData[2] = di_fitted & 0xFF; // value
			TxData[3] = di_fitted >> 8; // value
			TxData[4] = 0x01; // io type - digital i/p
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			break;
		case 130:	// display tx mask analogue i/p
			TxHeader.StdId = 0x0400 | 0x06;	// action
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 5;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x0A; // tx mask, eoid - 0x0A
			TxData[1] = 0x00; // display tx mask
			TxData[2] = used_ai & 0xFF; // value
			TxData[3] = used_ai >> 8; // value
			TxData[4] = 0x00; // io type - analogue i/p
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
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
	initCANFilter();
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	for(;;) {
		cnt++;
		if(cnt>=500) {
			cnt = 0;
			TxHeader.StdId = 0x0400 | 0x01;
			TxHeader.ExtId = 0;
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_STD;
			TxHeader.DLC = 2;
			TxHeader.TransmitGlobalTime = DISABLE;
			TxData[0] = 0x49;
			TxData[1] = heartbeat_value++;
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
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
		if(inp_tmr>=500) {
			inp_tmr = 0;
			update_di=0x3FFF;
			update_ai=0x3FFF;
		}
		osDelay(1);
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t srv = 0;
	uint8_t node = 0;
	//uint8_t ss = 0;
	//uint8_t eoid = 0;
	if(hcan==&hcan1) {
		if(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0)) {
			if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
				//HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin);
				srv = RxHeader.StdId & 0x07;
				node = (RxHeader.StdId>>3) & 0x0F;
				//eoid = RxData[0] & 0x1F;
				//ss = (RxData[0] >> 5) & 0x07;
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
