/*
 * scada.h
 *
 *  Created on: 16 ���. 2020 �.
 *      Author: User
 */

#ifndef SCADA_H_
#define SCADA_H_

// ����������� ������ �� net_bits � answer_96 ������� �� 2 �����
// ����� ��������� ������� �������� �� ����� ����������
// �� �� ����� �������� � ������� ���������

// ������ ����� ����������� ������ ��� � �����
void net_bits_to_scada_first();

// ������ ����� ����������� ������� ��� � �����
void net_bits_to_scada_second();

// ������ ����� ����������� ������� ��������� � �����
void net_regs_to_scada_first();

// ������ ����� ����������� ������� ��������� � �����
void net_regs_to_scada_second();

// ������������ ��� ����� ��������� ����� � ���������
void node_and_cluster_state_to_scada();

#endif /* SCADA_H_ */
