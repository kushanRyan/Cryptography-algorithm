#pragma once
#include "stdint.h"  
//����posix��׼��һ�����ζ�Ӧ��* _t����Ϊ��
//1�ֽ�     uint8_t
//2�ֽ�     uint16_t
//4�ֽ�     uint32_t
//8�ֽ�     uint64_t
#include<iostream>
#define SHA1HashSize 20
using namespace std;
typedef struct SHA1Context {
	uint32_t Intermediate_Hash[SHA1HashSize / 4]; /*! <Message Digest  */

	uint32_t Length_Low; //��Ϣ��λ
	uint32_t Length_High;//��Ϣ��λ 

	int_least16_t Message_Block_Index;
	uint8_t Message_Block[64];//512�ֽ�
	int Computed;//ժҪ�Ƿ�����
	int Corrupted;//ժҪ�Ƿ���
} SHA1Context;
uint32_t SHA1CircularShift(uint32_t bits, uint32_t word);
void SHA1PadMessage(SHA1Context*);
void SHA1ProcessMessageBlock(SHA1Context*);
int SHA1Reset(SHA1Context*);
int SHA1Input(SHA1Context* context, const uint8_t* message_array, unsigned length);
int SHA1Result(SHA1Context*, uint8_t Message_Digest[SHA1HashSize]);
void SHA1Interface(string a);
