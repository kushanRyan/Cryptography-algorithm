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
//AES加密
//S盒
static int S[16][16] = { 0 };
//逆S盒
static int S1[16][16] = { 0 };
//字符串随机生成
//用来调用AES算法
void AES(char* container, char* keys, int S[16][16]) {
	int textContainer[4][4];
	//将明/密文的内容转化为4*4的矩阵
	for (int z = 0; z < strlen(container);z+=16) {
		convertToIntArray(container+z, textContainer);
        cout<<1<<endl;
		//进行密钥拓展
		expandedKey(keys, S);
        cout<<2<<endl;
		//首次的轮密钥加
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
		//最后一次处理时，不需要进行列混合
		subBytes(textContainer, S);
		shiftRow(textContainer);
		addRoundKey(textContainer, 10);
		convertArrayToStr(textContainer, container+z);
        cout<<5<<endl;
	}
	cout << "密文是:";
	cout << container << endl;
	cout << "已完成AES加密算法" << endl;
    cout<<6<<endl;
	ofstream out;out.open("D://tests//aes//plaintext.txt", ios::binary);
	out.write((char*)&container, sizeof(container));
	out.close();
    cout<<7<<endl;
}
//执行AES
void excuteAES(string a,string keys) {
	//生成S盒和逆S盒
	spwanSbox(S);
	spwanInvSbox(S1);
	//明/密文 密钥
    char* textContainer,*textContainer2;
	//输入密钥和明文
    string tempTc=a;
	while (1) {
		while (tempTc.length() % 16 != 0) {
            tempTc += "_";
		}
		if (tempTc.length() % 16 == 0)break;
	}
	textContainer = (char*)tempTc.c_str();
	textContainer2 = (char*)tempTc.c_str();
	//开始执行AES加解密算法
    AES(textContainer, (char*)keys.c_str(), S);
    ifstream in;in.open("D://tests//aes//plaintext.txt", ios::binary);
	in.read((char*)&textContainer2, sizeof(textContainer2));
    deAES(textContainer2, (char*)keys.c_str(), S1);
}
