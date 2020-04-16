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

// первая часть копирования сетвых бит в скаду
void net_bits_to_scada_first();

// вторая часть копирования сетевых бит в скаду
void net_bits_to_scada_second();

// первая часть копирования сетевых регистров в скаду
void net_regs_to_scada_first();

// вторая часть копирования сетевых регистров в скаду
void net_regs_to_scada_second();

// формирование для скады состояния узлов и кластеров
void node_and_cluster_state_to_scada();

#endif /* SCADA_H_ */
