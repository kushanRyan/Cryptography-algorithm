#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//行移位------------------------------------------------------------------------------------------------------
//行移位是一个简单的左循环移位操作。当密钥长度为128比特时，状态矩阵的第0行左移0字节，
//第1行左移1字节，第2行左移2字节，第3行左移3字节
void arrayLeftMove(int array[4], int step) {
	int temp[4];
	//数组导入
	for (int i = 0; i < 4; i++) {
		temp[i] = array[i];
	}
	int index = step % 4;
	//判断是第几回
	if (index == 0) {
		step = 0;
	}
	else {
		step %= 4;
	}
	//导出数据
	for (int i = 0; i < 4; i++) {
		array[i] = temp[index];
		index++;
		index = index % 4;
	}
}
void shiftRow(int textContainer[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	//存储矩阵的2 3 4行，之后进行移动
	for (int i = 0; i < 4; i++) {
		rowTwo[i] = textContainer[1][i];
		rowThree[i] = textContainer[2][i];
		rowFour[i] = textContainer[3][i];
	}
	//循环左移相应的位数
	arrayLeftMove(rowTwo, 1);
	arrayLeftMove(rowThree, 2);
	arrayLeftMove(rowFour, 3);
	//把左移后的行复制回状态矩阵中
	for (int i = 0; i < 4; i++) {
		textContainer[1][i] = rowTwo[i];
		textContainer[2][i] = rowThree[i];
		textContainer[3][i] = rowFour[i];
	}
}
