#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//几个工具函数----------------------------------------------------------------------------------------------------
//将字符串转化为4*4的数组
void convertToIntArray(char* str, int pa[4][4]) {
	int k = 0;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			//将字符串转化为数字，导入数组
			pa[j][i] = getIntFromChar(str[k]);
			k++;
		}
	}
}
//将加/解密完的的数组变回字符串
void convertArrayToStr(int array[4][4], char* str) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			//强制类型转换，++代表移动到下一个字符
			*str++ = (char)array[j][i];
		}
	}

}
// 把一个4字节的数的第一、二、三、四个字节取出，入进一个4个元素的整型数组里面。
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
//进行单个字节代换
int getNumFromSBox(int index, int S[16][16]) {
	//获取整形数据的低8位的左4个位
	int row = getLeft4Bit(index);
	//获取整形数据的低8位的右4个位
	int col = getRight4Bit(index);
	//返回查表的值
	return S[row][col];
}
