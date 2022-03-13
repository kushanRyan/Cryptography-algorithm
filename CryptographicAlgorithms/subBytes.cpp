#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//字节代换----------------------------------------------------------------------------------------------------
//获取整形数据的低8位的左4个位
int getLeft4Bit(int num) {
	int left = num & 0x000000f0;
	return left >> 4;
}
//获取整形数据的低8位的右4个位
int getRight4Bit(int num) {
	return num & 0x0000000f;
}
//一个很简单的查表操作
void subBytes(int textContainer[4][4],int S[16][16]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			textContainer[i][j] = getNumFromSBox(textContainer[i][j],S);
		}
	}
}
