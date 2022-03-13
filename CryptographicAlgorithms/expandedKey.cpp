#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
using namespace std;
//��Կ��չ----------------------------------------------------------------------------------------------------
int Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 }; // ������ֵ�� 
//���ַ�ת��Ϊ16���Ƶ�����
int getIntFromChar(char c) {
	//�ַ�ǿ��ת��
	int result = (int)c;
	//�����0x000000ff���к�����
	//&0x000000ffֱ�����þ���ֻ�������8λ(һ��16����λ��4��2����λ)
	return result & 0x000000ff;
}
// ��������4���ַ��ϲ���һ��4�ֽڵ�����
int getWordFromStr(char* str) {
	int one, two, three, four;
	//����һ���ַ����ƶ�����һ���ֽ�
	//xxxxxxxx000000000000000000000000
	one = getIntFromChar(str[0]);
	one = one << 24;
	//���ڶ����ַ����ƶ����ڶ����ֽ�
	//00000000xxxxxxxx0000000000000000
	two = getIntFromChar(str[1]);
	two = two << 16;
	//���������ַ����ƶ����������ֽ�
	//0000000000000000xxxxxxxx00000000
	three = getIntFromChar(str[2]);
	three = three << 8;
	//000000000000000000000000xxxxxxxx
	four = getIntFromChar(str[3]);
	//���⼸�����ֽ��л����㣨0|1=1��
	return one | two | three | four;
}
//��Կ��չ�е�T����
//����������ת��Ϊһ������
int mergeArrayToInt(int array[4]) {
	int one = array[0] << 24;
	int two = array[1] << 16;
	int three = array[2] << 8;
	int four = array[3];
	return one | two | three | four;
}
//T��������
int T(int num, int round,int S[16][16]) {
	int numArray[4];
	int i;
	int result;
	// ��һ��4�ֽڵ����ĵ�һ�����������ĸ��ֽ�ȡ�������һ��4��Ԫ�ص�������������
	splitIntToArray(num, numArray);
	//��1�����е�4���ֽ�ѭ������1���ֽڡ�����������[1,2,3,4]�任��[2,3,4,1]��
	arrayLeftMove(numArray, 1);

	//�ֽڴ���
	for (i = 0; i < 4; i++) {
		numArray[i] = getNumFromSBox(numArray[i],S);
	}
	//��������װ��֮�󷵻�ֵ
	result = mergeArrayToInt(numArray);
	return result ^ Rcon[round];
}
//��Կ��չ��������
//cipher����Կ����
void expandedKey(char* cipher,int S[16][16]) {
	for (int i = 0; i < 4; i++) {
		//����Կ������Կ����ת��Ϊ���ͣ�
		keyMatrix[i] = getWordFromStr(cipher + i * 4);
	}
    cout<<11<<endl;
	//�ϳ����е���Կ����roundeCounter������ǵڼ��ֺϳ�
	for (int i = 4, roundCouter = 0; i < 44; i++) {
		//�ڵ����ֵ�ʱ��keyMatrix[i-4]��T(keyMatrix[i-1])����������㣨������ģ�ӣ�
		if (i % 4 == 0) {
			keyMatrix[i] = keyMatrix[i - 4] ^ T(keyMatrix[i - 1], roundCouter,S);
			roundCouter++;
		}
		else {//�ǵ����־�ֱ���������
			keyMatrix[i] = keyMatrix[i - 4] ^ keyMatrix[i - 1];
		}
	}
    cout<<22<<endl;
}
