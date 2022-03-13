#include <iostream>
#include <fstream>
#include <string.h>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
//AES解密函数
void deAES(char* container, char* keys,int S1[16][16]) {
	int cipherArray[4][4];
	int tempArray[4][4];
	for (int z = 0; z < strlen(container); z += 16) {
		//将密文转化为4*4数组
		convertToIntArray(container + z, cipherArray);
		//和加密一样每次开始时要进行一次轮密钥加
		addRoundKey(cipherArray, 10);
		//开始逆加密
		for (int i = 9; i >= 1; i--) {
			deSubBytes(cipherArray, S1);
			deShiftRows(cipherArray);
			//------------------------------------------
			//逆列混合
			deMixColumns(cipherArray);
			//从keyMartix获取数据，方便!轮!密!钥!加!的运算(因为后面是倒着来的)
			getArrayFromKeyMartix(i, tempArray);
			//------------------------------------------
			addRoundTowArray(cipherArray, tempArray);
		}
		deSubBytes(cipherArray, S1);
		deShiftRows(cipherArray);
		addRoundKey(cipherArray, 0);
		//导出结果
		convertArrayToStr(cipherArray, container + z);
	}
	ofstream outter; 
	outter.open("D://tests//aes//ciphertext.txt", ios::binary);
	outter<<container;
	outter.close();

	cout << "明文是:" << container << endl;
	cout << "已完成AES解密算法" << endl;
}
