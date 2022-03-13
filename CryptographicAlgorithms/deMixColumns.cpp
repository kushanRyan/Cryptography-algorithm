#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
// 逆列混合
//从4个32位的密钥字中获得4X4数组，用于进行逆列混合
void getArrayFromKeyMartix(int i, int array[4][4]) {
	int index, j;
	int colOne[4], colTwo[4], colThree[4], colFour[4];
	index = i * 4;
	splitIntToArray(keyMatrix[index], colOne);
	splitIntToArray(keyMatrix[index + 1], colTwo);
	splitIntToArray(keyMatrix[index + 2], colThree);
	splitIntToArray(keyMatrix[index + 3], colFour);

	for (j = 0; j < 4; j++) {
		array[j][0] = colOne[j];
		array[j][1] = colTwo[j];
		array[j][2] = colThree[j];
		array[j][3] = colFour[j];
	}
}
// 逆列混合函数
void deMixColumns(int array[4][4]) {
	int tempArray[4][4];
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tempArray[i][j] = array[i][j];
		}
	}
	//矩阵的乘法运算
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			array[i][j] =
				GFMain(deColM[i][0], tempArray[0][j]) ^
				GFMain(deColM[i][1], tempArray[1][j]) ^
				GFMain(deColM[i][2], tempArray[2][j]) ^
				GFMain(deColM[i][3], tempArray[3][j]);
		}
	}

}
