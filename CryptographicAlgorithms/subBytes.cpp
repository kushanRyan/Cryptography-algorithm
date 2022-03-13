#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//�ֽڴ���----------------------------------------------------------------------------------------------------
//��ȡ�������ݵĵ�8λ����4��λ
int getLeft4Bit(int num) {
	int left = num & 0x000000f0;
	return left >> 4;
}
//��ȡ�������ݵĵ�8λ����4��λ
int getRight4Bit(int num) {
	return num & 0x0000000f;
}
//һ���ܼ򵥵Ĳ�����
void subBytes(int textContainer[4][4],int S[16][16]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			textContainer[i][j] = getNumFromSBox(textContainer[i][j],S);
		}
	}
}
