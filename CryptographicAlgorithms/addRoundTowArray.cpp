#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
//������4X4����������
void addRoundTowArray(int aArray[4][4], int bArray[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			aArray[i][j] = aArray[i][j] ^ bArray[i][j];
		}
	}
}
