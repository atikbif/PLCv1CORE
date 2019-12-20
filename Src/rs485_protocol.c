/*
 * rs485_protocol.c
 *
 *  Created on: 14 ����. 2019 �.
 *      Author: User
 */

#include "rs485_protocol.h"
#include "rs485.h"
#include <string.h>
#include "main.h"
#include "crc.h"
#include "eeprom.h"

static uint8_t tmp_rx1_buf[UART_BUF_SISE];
static uint8_t tmp_rx2_buf[UART_BUF_SISE];
static uint8_t tx1_buf[UART_BUF_SISE];
static uint8_t tx2_buf[UART_BUF_SISE];
extern uint16_t VirtAddVarTab[NB_OF_VAR];

uint8_t net_address = 0x01;

void rx_callback(uint8_t* rx_ptr,uint16_t rx_cnt, uint8_t * tx_ptr, void (*send)(uint8_t*,uint16_t)) {
	uint16_t crc=0;
	uint16_t cnt=0;
	if((rx_cnt>=4) && ((rx_ptr[0]==net_address) || (rx_ptr[0]==0x00)) && (GetCRC16(rx_ptr,rx_cnt)==0)) {
		switch(rx_ptr[1]) {
			case 0xA0:
				tx_ptr[0] = rx_ptr[0];
				tx_ptr[1] = 0xA0;
				// request id
				tx_ptr[2] = rx_ptr[2];
				tx_ptr[3] = rx_ptr[3];
				// device id
				tx_ptr[4] = 0x00;
				tx_ptr[5] = 0x00;
				tx_ptr[6] = 0x00;
				tx_ptr[7] = 0x04;

				crc = GetCRC16((unsigned char*)tx_ptr,8);
				tx_ptr[8]=crc>>8;
				tx_ptr[9]=crc&0xFF;
				send(tx_ptr,10);
				break;
			case 0xEB:	// ������� ����� �������� ��� ��������
				tx_ptr[0] = rx_ptr[0];
				tx_ptr[1] = 0xEB;
				// request id
				tx_ptr[2] = rx_ptr[2];
				tx_ptr[3] = rx_ptr[3];
				cnt = rx_ptr[4];
				cnt = cnt<<8; cnt|=rx_ptr[5]; // ������ ��������� � ����������
				if(cnt%128==0) {
					cnt=cnt/128;
					tx_ptr[4] = cnt>>8;
					tx_ptr[5] = cnt & 0xFF;
					crc = GetCRC16((unsigned char*)tx_ptr,6);
					tx_ptr[6]=crc>>8;
					tx_ptr[7]=crc&0xFF;
					send(tx_ptr,8);
				}
				break;
			case 0xEC:// restart in boot mode
				tx_ptr[0] = rx_ptr[0];
				tx_ptr[1] = 0xEC;
				// request id
				tx_ptr[2] = rx_ptr[2];
				tx_ptr[3] = rx_ptr[3];
				crc = GetCRC16((unsigned char*)tx_ptr,4);
				tx_ptr[4]=crc>>8;
				tx_ptr[5]=crc&0xFF;
				send(tx_ptr,6);
				EE_WriteVariable(VirtAddVarTab[1],0);
				HAL_Delay(50);
				NVIC_SystemReset();
				break;
			default:
				tx_ptr[0] = rx_ptr[0];
				tx_ptr[1] = 0xA0;
				// request id
				tx_ptr[2] = rx_ptr[2];
				tx_ptr[3] = rx_ptr[3];
				// device id
				tx_ptr[4] = 0x04;
				tx_ptr[5] = 0x00;
				tx_ptr[6] = 0x00;
				tx_ptr[7] = 0x01;

				crc = GetCRC16((unsigned char*)tx_ptr,8);
				tx_ptr[8]=crc>>8;
				tx_ptr[9]=crc&0xFF;
				send(tx_ptr,10);
		}
	}
}

void rx1_callback(uint8_t* rx_ptr,uint16_t rx_cnt) {
	if(rx_cnt<=UART_BUF_SISE) {
		memcpy(tmp_rx1_buf,rx_ptr,rx_cnt);
		rx_callback(tmp_rx1_buf, rx_cnt, tx1_buf, send_data_to_uart1);
	}
}

void rx2_callback(uint8_t* rx_ptr,uint16_t rx_cnt) {
	if(rx_cnt<=UART_BUF_SISE) {
		memcpy(tmp_rx2_buf,rx_ptr,rx_cnt);
		rx_callback(tmp_rx2_buf, rx_cnt, tx2_buf, send_data_to_uart2);
	}
}