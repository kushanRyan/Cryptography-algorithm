#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//密钥拓展----------------------------------------------------------------------------------------------------
int Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 }; // 常量轮值表 
//将字符转化为16进制的数字
int getIntFromChar(char c) {
	//字符强制转换
	int result = (int)c;
	//将其和0x000000ff进行和运算
	//&0x000000ff直接作用就是只保留最后8位(一个16进制位是4个2进制位)
	return result & 0x000000ff;
}
// 把连续的4个字符合并成一个4字节的整型
int getWordFromStr(char* str) {
	int one, two, three, four;
	//将第一个字符串移动到第一个字节
	//xxxxxxxx000000000000000000000000
	one = getIntFromChar(str[0]);
	one = one << 24;
	//将第二个字符串移动到第二个字节
	//00000000xxxxxxxx0000000000000000
	two = getIntFromChar(str[1]);
	two = two << 16;
	//将第三个字符串移动到第三个字节
	//0000000000000000xxxxxxxx00000000
	three = getIntFromChar(str[2]);
	three = three << 8;
	//000000000000000000000000xxxxxxxx
	four = getIntFromChar(str[3]);
	//将这几个数字进行或运算（0|1=1）
	return one | two | three | four;
}
//密钥扩展中的T函数
//将数组序列转化为一个整数
int mergeArrayToInt(int array[4]) {
	int one = array[0] << 24;
	int two = array[1] << 16;
	int three = array[2] << 8;
	int four = array[3];
	return one | two | three | four;
}
//T函数主体
int T(int num, int round,int S[16][16]) {
	int numArray[4];
	int i;
	int result;
	// 把一个4字节的数的第一、二、三、四个字节取出，入进一个4个元素的整型数组里面
	splitIntToArray(num, numArray);
	//将1个字中的4个字节循环左移1个字节。即将输入字[1,2,3,4]变换成[2,3,4,1]。
	arrayLeftMove(numArray, 1);

	//字节代换
	for (i = 0; i < 4; i++) {
		numArray[i] = getNumFromSBox(numArray[i],S);
	}
	//将数组组装，之后返回值
	result = mergeArrayToInt(numArray);
	return result ^ Rcon[round];
}
//密钥拓展函数主体
//cipher是密钥！！
void expandedKey(char* cipher,int S[16][16]) {
	for (int i = 0; i < 4; i++) {
		//将密钥导入密钥矩阵（转化为整型）
		keyMatrix[i] = getWordFromStr(cipher + i * 4);
	}
    cout<<11<<endl;
	//合成所有的密钥矩阵，roundeCounter代表的是第几轮合成
	for (int i = 4, roundCouter = 0; i < 44; i++) {
		//在第四轮的时候将keyMatrix[i-4]与T(keyMatrix[i-1])进行异或运算（二进制模加）
		if (i % 4 == 0) {
			keyMatrix[i] = keyMatrix[i - 4] ^ T(keyMatrix[i - 1], roundCouter,S);
			roundCouter++;
		}
		else {//非第四轮就直接异或运算
			keyMatrix[i] = keyMatrix[i - 4] ^ keyMatrix[i - 1];
		}
	}
    cout<<22<<endl;
}
