#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;

//逆字节变换
// 根据索引从逆S盒中获取值
int getNumFromS1Box(int index, int S1[16][16]) {
	int row = getLeft4Bit(index);
	int col = getRight4Bit(index);
	return S1[row][col];
}
// 逆字节变换函数
void deSubBytes(int array[4][4],int S1[16][16]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			array[i][j] = getNumFromS1Box(array[i][j],S1);
		}
	}
}
