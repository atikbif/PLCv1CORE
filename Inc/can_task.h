/*
 * can_task.h
 *
 *  Created on: 22 ���. 2020 �.
 *      Author: User
 */

#ifndef CAN_TASK_H_
#define CAN_TASK_H_

#include <stdint.h>

void canTask(void const * argument);
void sendIOName(uint8_t ioNum, uint8_t type, uint8_t req_node, uint8_t req_num);

#endif /* CAN_TASK_H_ */
