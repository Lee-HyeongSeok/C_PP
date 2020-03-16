#include <iostream>
#include "Statistics.h"
using namespace std;

#define SWAP(a, b){int t=a; a=b; b=t;}

int Statistics::sum(Account * pArray, int size) {
	int total_b = 0;
	for (int i = 0; i < size; i++) {
		total_b += pArray[i].GetBalance();
	}
	return total_b;
}
int Statistics::average(Account* pArray, int size) {
	int total_b = 0;
	for (int i = 0; i < size; i++) {
		total_b += pArray[i].GetBalance();
	}
	if (total_b == 0) {
		return 0;
	}
	return total_b / size;
}
int Statistics::max(Account* pArray, int size) {
	int *temp = new int[size];

	for (int i = 0; i < size; i++) {
		temp[i] = pArray[i].GetBalance();
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (temp[j] < temp[j+1]) {
				SWAP(temp[j], temp[j + 1]);
			}
		}
	}
	if (size == 0) {
		temp[0] = 0;
	}

	return temp[0];
	delete[]temp;
}