#pragma once

#ifndef STATISTCIS_H
#define STATISTCIS_H
// 스크린 관 별 티켓 결제 금액 총액
// 스크린 관 별 티켓 판매량
// 관리자 인증처리
#include "TicketBox.h"
#include "Ticket.h"
#include "Screen.h"

class Statistcis {
public : 
	Statistcis();
	~Statistcis();
	// 상영관별 티켓 판매 총액
	int sum(Ticket ** pTicket, int nRow, int nCol);
	void ShowReservedStatus(Ticket **pTicket, int nRow, int nCol);
};
#endif