#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//����λ------------------------------------------------------------------------------------------------------
//����λ��һ���򵥵���ѭ����λ����������Կ����Ϊ128����ʱ��״̬����ĵ�0������0�ֽڣ�
//��1������1�ֽڣ���2������2�ֽڣ���3������3�ֽ�
void arrayLeftMove(int array[4], int step) {
	int temp[4];
	//���鵼��
	for (int i = 0; i < 4; i++) {
		temp[i] = array[i];
	}
	int index = step % 4;
	//�ж��ǵڼ���
	if (index == 0) {
		step = 0;
	}
	else {
		step %= 4;
	}
	//��������
	for (int i = 0; i < 4; i++) {
		array[i] = temp[index];
		index++;
		index = index % 4;
	}
}
void shiftRow(int textContainer[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	//�洢�����2 3 4�У�֮������ƶ�
	for (int i = 0; i < 4; i++) {
		rowTwo[i] = textContainer[1][i];
		rowThree[i] = textContainer[2][i];
		rowFour[i] = textContainer[3][i];
	}
	//ѭ��������Ӧ��λ��
	arrayLeftMove(rowTwo, 1);
	arrayLeftMove(rowThree, 2);
	arrayLeftMove(rowFour, 3);
	//�����ƺ���и��ƻ�״̬������
	for (int i = 0; i < 4; i++) {
		textContainer[1][i] = rowTwo[i];
		textContainer[2][i] = rowThree[i];
		textContainer[3][i] = rowFour[i];
	}
}
