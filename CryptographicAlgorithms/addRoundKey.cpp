#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"

using namespace std;
//����Կ��----------------------------------------------------------------------------------------------------
//����Կ���ǽ�128λ����ԿKiͬ״̬�����е����ݽ�����λ������
void addRoundKey(int textContainer[4][4], int round) {
	int tempArray[4];
	for (int i = 0; i < 4; i++) {
		//����Ӧ�ֵ���Կ�ֽ��һ����СΪ4������
		splitIntToArray(keyMatrix[round * 4 + i], tempArray);
		for (int j = 0; j < 4; j++) {
			//�������Ӧ����Կ�����
			textContainer[j][i] ^= tempArray[j];
		}
	}
}
