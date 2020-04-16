/*
 * scada.h
 *
 *  Created on: 16 апр. 2020 г.
 *      Author: User
 */

#ifndef SCADA_H_
#define SCADA_H_

// копирование данных из net_bits в answer_96 разбито на 2 части
// чтобы уменьшить пиковую нагрузку во время выполнения
// то же самое касается и сетевых регистров

void net_bits_to_scada_first();
void net_bits_to_scada_second();
void net_regs_to_scada_first();
void net_regs_to_scada_second();

#endif /* SCADA_H_ */
