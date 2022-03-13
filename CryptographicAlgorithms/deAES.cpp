#include <iostream>
#include <fstream>
#include <string.h>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
//AES���ܺ���
void deAES(char* container, char* keys,int S1[16][16]) {
	int cipherArray[4][4];
	int tempArray[4][4];
	for (int z = 0; z < strlen(container); z += 16) {
		//������ת��Ϊ4*4����
		convertToIntArray(container + z, cipherArray);
		//�ͼ���һ��ÿ�ο�ʼʱҪ����һ������Կ��
		addRoundKey(cipherArray, 10);
		//��ʼ�����
		for (int i = 9; i >= 1; i--) {
			deSubBytes(cipherArray, S1);
			deShiftRows(cipherArray);
			//------------------------------------------
			//���л��
			deMixColumns(cipherArray);
			//��keyMartix��ȡ���ݣ�����!��!��!Կ!��!������(��Ϊ�����ǵ�������)
			getArrayFromKeyMartix(i, tempArray);
			//------------------------------------------
			addRoundTowArray(cipherArray, tempArray);
		}
		deSubBytes(cipherArray, S1);
		deShiftRows(cipherArray);
		addRoundKey(cipherArray, 0);
		//�������
		convertArrayToStr(cipherArray, container + z);
	}
	ofstream outter; 
	outter.open("D://tests//aes//ciphertext.txt", ios::binary);
	outter<<container;
	outter.close();

	cout << "������:" << container << endl;
	cout << "�����AES�����㷨" << endl;
}
