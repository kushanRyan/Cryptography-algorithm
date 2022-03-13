#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//�������ߺ���----------------------------------------------------------------------------------------------------
//���ַ���ת��Ϊ4*4������
void convertToIntArray(char* str, int pa[4][4]) {
	int k = 0;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			//���ַ���ת��Ϊ���֣���������
			pa[j][i] = getIntFromChar(str[k]);
			k++;
		}
	}
}
//����/������ĵ��������ַ���
void convertArrayToStr(int array[4][4], char* str) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			//ǿ������ת����++�����ƶ�����һ���ַ�
			*str++ = (char)array[j][i];
		}
	}

}
// ��һ��4�ֽڵ����ĵ�һ�����������ĸ��ֽ�ȡ�������һ��4��Ԫ�ص������������档
void splitIntToArray(int num, int array[4]) {
	int one, two, three;
	one = num >> 24;
	array[0] = one & 0x000000ff;
	two = num >> 16;
	array[1] = two & 0x000000ff;
	three = num >> 8;
	array[2] = three & 0x000000ff;
	array[3] = num & 0x000000ff;
}
//���е����ֽڴ���
int getNumFromSBox(int index, int S[16][16]) {
	//��ȡ�������ݵĵ�8λ����4��λ
	int row = getLeft4Bit(index);
	//��ȡ�������ݵĵ�8λ����4��λ
	int col = getRight4Bit(index);
	//���ز���ֵ
	return S[row][col];
}
