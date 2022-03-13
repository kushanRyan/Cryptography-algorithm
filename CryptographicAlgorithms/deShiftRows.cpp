#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;

//������λ
//��4��Ԫ�ص�����ѭ������stepλ
void arrayRihgtMove(int array[4], int step) {
	int temp[4];
	int i;
	int index = step % 4;
	for (i = 0; i < 4; i++) {
		temp[i] = array[i];
	}
	//�ж��ǵڼ���
	if (index == 0) {
		step = 0;
	}else {
		step %= 4;
	}
	//��Ҫ3-index����Ϊ��������λ����Ҫ������
	index = 3 - index;
	for (i = 3; i >= 0; i--) {
		array[i] = temp[index];
		index--;
		if (index==-1) {
			index = 3;
		}
	}
}
//������λ����
void deShiftRows(int array[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	//�洢�����2 3 4�У�֮������ƶ�
	for (int i = 0; i < 4; i++) {
		rowTwo[i] = array[1][i];
		rowThree[i] = array[2][i];
		rowFour[i] = array[3][i];
	}
	//ѭ��������Ӧ��λ��
	arrayRihgtMove(rowTwo, 1);
	arrayRihgtMove(rowThree, 2);
	arrayRihgtMove(rowFour, 3);
	//�����ƺ���и��ƻ�״̬������
	for (int i = 0; i < 4; i++) {
		array[1][i] = rowTwo[i];
		array[2][i] = rowThree[i];
		array[3][i] = rowFour[i];
	}
}
