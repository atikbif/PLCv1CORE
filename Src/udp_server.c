/*
 * udp_server.c
 *
 *  Created on: 14 ���. 2020 �.
 *      Author: User
 */

#include "udp_server.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "crc.h"
#include <string.h>
#include "eeprom.h"

#define UDP_SERVER_PORT    12146
#define INCORRECT_PAGE_NUM	1
#define READ_ERROR		2
#define PAGE_BUSY		3
#define BAD_BLOCK		4

static char answer[1324];
static unsigned short reqID = 0;

extern uint8_t jump_flag;
extern uint16_t VirtAddVarTab[NB_OF_VAR];

static void udp_server_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
static void inline send_udp_data(struct udp_pcb *upcb,const ip_addr_t *addr,u16_t port,u16_t length);

void udp_server_init(void) {
	struct udp_pcb *upcb;
	err_t err;

	/* Create a new UDP control block  */
	upcb = udp_new();

	if (upcb)
	{
	 /* Bind the upcb to the UDP_PORT port */
	 /* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
	  err = udp_bind(upcb, IP_ADDR_ANY, UDP_SERVER_PORT);

	  if(err == ERR_OK)
	  {

		/* Set a receive callback for the upcb */
		udp_recv(upcb, udp_server_receive_callback, NULL);
	  }
	  else
	  {
		udp_remove(upcb);
	  }
	}
}

void udp_server_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
	unsigned char *data;

	uint16_t crc=0;

	data = (unsigned char*)(p->payload);
	crc = GetCRC16(data,p->len);


	if(crc==0)
	{
	  //udp_tmr = 0;
	  reqID = (unsigned short)data[0]<<8;
	  reqID |= data[1];
	  switch(data[2]){
		case 0xA0:
		  answer[0] = data[0];
		  answer[1] = data[1];
		  answer[2] = 0xA0;
		  answer[3] = 0x01;	// type of device identificator
		  answer[4] = 0xC4;
		  answer[5] = 0x00;
		  answer[6] = 0x01;
		  crc = GetCRC16((unsigned char*)answer,7);
		  answer[7]=crc>>8;
		  answer[8]=crc&0xFF;
		  send_udp_data(upcb, addr, port,9);
		  break;
		case 0xEC:// restart in boot mode
		  answer[0] = data[0];
		  answer[1] = data[1];
		  answer[2] = 0xEC;
		  crc = GetCRC16((unsigned char*)answer,3);
		  answer[3]=crc>>8;
		  answer[4]=crc&0xFF;
		  send_udp_data(upcb, addr, port,5);
		  EE_WriteVariable(VirtAddVarTab[1],0);
		  HAL_Delay(50);
		  NVIC_SystemReset();
		  break;
	  }
	}

	pbuf_free(p);
}

void inline send_udp_data(struct udp_pcb *upcb,const ip_addr_t *addr,u16_t port,u16_t length) {
	struct pbuf *p_answer;
	udp_connect(upcb, addr, port);
	p_answer = pbuf_alloc(PBUF_TRANSPORT,length, PBUF_POOL);
	if (p_answer != NULL)
	{
	  pbuf_take(p_answer, answer, length);
	  udp_send(upcb, p_answer);
	  pbuf_free(p_answer);
	}
	udp_disconnect(upcb);
}
