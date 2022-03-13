#pragma once
#include "stdint.h"  
//按照posix标准，一般整形对应的* _t类型为：
//1字节     uint8_t
//2字节     uint16_t
//4字节     uint32_t
//8字节     uint64_t
#include<iostream>
#define SHA1HashSize 20
using namespace std;
typedef struct SHA1Context {
	uint32_t Intermediate_Hash[SHA1HashSize / 4]; /*! <Message Digest  */

	uint32_t Length_Low; //信息低位
	uint32_t Length_High;//信息高位 

	int_least16_t Message_Block_Index;
	uint8_t Message_Block[64];//512字节
	int Computed;//摘要是否生成
	int Corrupted;//摘要是否损坏
} SHA1Context;
uint32_t SHA1CircularShift(uint32_t bits, uint32_t word);
void SHA1PadMessage(SHA1Context*);
void SHA1ProcessMessageBlock(SHA1Context*);
int SHA1Reset(SHA1Context*);
int SHA1Input(SHA1Context* context, const uint8_t* message_array, unsigned length);
int SHA1Result(SHA1Context*, uint8_t Message_Digest[SHA1HashSize]);
void SHA1Interface(string a);
