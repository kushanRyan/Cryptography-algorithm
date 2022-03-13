#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "CryptographicAlgorithmsH/deAES.h"
#include "CryptographicAlgorithmsH/sBoxSpawner.h"
#include <string>
#include <string.h>
using namespace std;
//AES����
//S��
static int S[16][16] = { 0 };
//��S��
static int S1[16][16] = { 0 };
//�ַ����������
//��������AES�㷨
void AES(char* container, char* keys, int S[16][16]) {
	int textContainer[4][4];
	//����/���ĵ�����ת��Ϊ4*4�ľ���
	for (int z = 0; z < strlen(container);z+=16) {
		convertToIntArray(container+z, textContainer);
        cout<<1<<endl;
		//������Կ��չ
		expandedKey(keys, S);
        cout<<2<<endl;
		//�״ε�����Կ��
		addRoundKey(textContainer, 0);
        cout<<3<<endl;
		int i = 1;
		for (i = 1; i < 10; i++) {
			subBytes(textContainer, S);
			shiftRow(textContainer);
			mixColumn(textContainer);
			addRoundKey(textContainer, i);
		}
        cout<<4<<endl;
		//���һ�δ���ʱ������Ҫ�����л��
		subBytes(textContainer, S);
		shiftRow(textContainer);
		addRoundKey(textContainer, 10);
		convertArrayToStr(textContainer, container+z);
        cout<<5<<endl;
	}
	cout << "������:";
	cout << container << endl;
	cout << "�����AES�����㷨" << endl;
    cout<<6<<endl;
	ofstream out;out.open("D://tests//aes//plaintext.txt", ios::binary);
	out.write((char*)&container, sizeof(container));
	out.close();
    cout<<7<<endl;
}
//ִ��AES
void excuteAES(string a,string keys) {
	//����S�к���S��
	spwanSbox(S);
	spwanInvSbox(S1);
	//��/���� ��Կ
    char* textContainer,*textContainer2;
	//������Կ������
    string tempTc=a;
	while (1) {
		while (tempTc.length() % 16 != 0) {
            tempTc += "_";
		}
		if (tempTc.length() % 16 == 0)break;
	}
	textContainer = (char*)tempTc.c_str();
	textContainer2 = (char*)tempTc.c_str();
	//��ʼִ��AES�ӽ����㷨
    AES(textContainer, (char*)keys.c_str(), S);
    ifstream in;in.open("D://tests//aes//plaintext.txt", ios::binary);
	in.read((char*)&textContainer2, sizeof(textContainer2));
    deAES(textContainer2, (char*)keys.c_str(), S1);
}
