#pragma once
#include <iostream>
#include "Account.h"
#include "ATMachine.h"
using namespace std;

#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics {
public : 
	Statistics() {

	}
	int sum(Account * pArray, int size);
	int average(Account* pArray, int size);
	int max(Account* pArray, int size);
	~Statistics() {

	}
};
#endif