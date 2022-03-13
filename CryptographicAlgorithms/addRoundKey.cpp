#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"

using namespace std;
//轮密钥加----------------------------------------------------------------------------------------------------
//轮密钥加是将128位轮密钥Ki同状态矩阵中的数据进行逐位异或操作
void addRoundKey(int textContainer[4][4], int round) {
	int tempArray[4];
	for (int i = 0; i < 4; i++) {
		//将对应轮的密钥分解成一个大小为4的数组
		splitIntToArray(keyMatrix[round * 4 + i], tempArray);
		for (int j = 0; j < 4; j++) {
			//明文与对应的密钥行异或
			textContainer[j][i] ^= tempArray[j];
		}
	}
}
