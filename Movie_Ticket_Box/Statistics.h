#pragma once

#ifndef STATISTCIS_H
#define STATISTCIS_H
// ��ũ�� �� �� Ƽ�� ���� �ݾ� �Ѿ�
// ��ũ�� �� �� Ƽ�� �Ǹŷ�
// ������ ����ó��
#include "TicketBox.h"
#include "Ticket.h"
#include "Screen.h"

class Statistcis {
public : 
	Statistcis();
	~Statistcis();
	// �󿵰��� Ƽ�� �Ǹ� �Ѿ�
	int sum(Ticket ** pTicket, int nRow, int nCol);
	void ShowReservedStatus(Ticket **pTicket, int nRow, int nCol);
};
#endif