#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;

//逆行移位
//把4个元素的数组循环右移step位
void arrayRihgtMove(int array[4], int step) {
	int temp[4];
	int i;
	int index = step % 4;
	for (i = 0; i < 4; i++) {
		temp[i] = array[i];
	}
	//判断是第几回
	if (index == 0) {
		step = 0;
	}else {
		step %= 4;
	}
	//需要3-index，因为是逆行移位，需要倒着来
	index = 3 - index;
	for (i = 3; i >= 0; i--) {
		array[i] = temp[index];
		index--;
		if (index==-1) {
			index = 3;
		}
	}
}
//逆行移位函数
void deShiftRows(int array[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	//存储矩阵的2 3 4行，之后进行移动
	for (int i = 0; i < 4; i++) {
		rowTwo[i] = array[1][i];
		rowThree[i] = array[2][i];
		rowFour[i] = array[3][i];
	}
	//循环右移相应的位数
	arrayRihgtMove(rowTwo, 1);
	arrayRihgtMove(rowThree, 2);
	arrayRihgtMove(rowFour, 3);
	//把右移后的行复制回状态矩阵中
	for (int i = 0; i < 4; i++) {
		array[1][i] = rowTwo[i];
		array[2][i] = rowThree[i];
		array[3][i] = rowFour[i];
	}
}
