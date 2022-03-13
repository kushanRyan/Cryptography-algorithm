#include<iostream>
#include<fstream>
#include"CryptographicAlgorithmsH/PrimalityTesting.h"
#include"CryptographicAlgorithmsH/SHA1.h"
#include<string.h>
using namespace std;
int shaSuccess = 0;
// ��ָʾ����
int shaNull = 1;
// ��������̫��
int shaInputTooLong = 2;
// ������������
int shaStateError = 3;
//SHA1��ϣ��Ĵ�С

//SHA1���F�㷨����
//�������ⳤ�ȵ����ģ�SHA1���ȶ�����з��飬ʹ��ÿһ��ĳ���Ϊ512λ��Ȼ�����Щ���ķ��鷴���ظ�����
//����ÿ�����ķ����ժҪ���ɹ������£�
//��512λ�����ķ��黮��Ϊ16�������ķ��飬ÿ�������ķ���Ϊ32λ��(���鷽ʽ��MD5��һ���ģ�����MD5��ͬ����SHA1��ԭʼ���ĳ��Ȳ��ܳ���2��64�η�������SHA1�����ĳ��ȴӵ�λ��ʼ��䡣)
//����5��32λ�����ӱ�������ΪA��B��C��D��E��
//16�������ķ�����չΪ80�ݡ�
//80�������ķ������4�����㡣
//���ӱ������ʼ���ӱ�������������㡣
//���ӱ�����Ϊ��һ�����ķ���������ظ��������ϲ�����
//���5�����ӱ�����������ݾ���SHA1ժҪ��
uint32_t SHA1CircularShift(uint32_t bits, uint32_t word) {
	return (((word) << (bits)) | ((word) >> (32 - (bits))));
}
void SHA1ProcessMessageBlock(SHA1Context* context) {
	/* ��MD5���Ķ��� SHA-1   */
	const uint32_t K[] = {0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};
	uint32_t temp, W[80], A, B, C, D, E;//��ʱ����,��˳��,�����

	//����Ϊ��ʼ����W�����е�ͷ16������
	for (int t = 0; t < 16; t++){
		W[t] = context->Message_Block[t * 4] << 24;
		W[t] |= context->Message_Block[t * 4 + 1] << 16;
		W[t] |= context->Message_Block[t * 4 + 2] << 8;
		W[t] |= context->Message_Block[t * 4 + 3];
	}

	for (int t = 16; t < 80; t++){
		W[t] = SHA1CircularShift(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);
	}

	A = context->Intermediate_Hash[0];
	B = context->Intermediate_Hash[1];
	C = context->Intermediate_Hash[2];
	D = context->Intermediate_Hash[3];
	E = context->Intermediate_Hash[4];
	//����Ϊ�����㷨����֮��ѧ������������㷨����
	for (int t = 0; t < 20; t++){
		temp = SHA1CircularShift(5, A) +
			((B & C) | ((~B) & D)) + E + W[t] + K[0];
		E = D;
		D = C;
		C = SHA1CircularShift(30, B);
		B = A;
		A = temp;
	}

	for (int t = 20; t < 40; t++){
		temp = SHA1CircularShift(5, A) + (B ^ C ^ D) + E + W[t] + K[1];
		E = D;
		D = C;
		C = SHA1CircularShift(30, B);
		B = A;
		A = temp;
	}


	for (int t = 40; t < 60; t++){
		temp = SHA1CircularShift(5, A) +
			((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
		E = D;
		D = C;
		C = SHA1CircularShift(30, B);
		B = A;
		A = temp;
	}

	for (int t = 60; t < 80; t++){
		temp = SHA1CircularShift(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
		E = D;
		D = C;
		C = SHA1CircularShift(30, B);
		B = A;
		A = temp;
	}
	//����Ϊ�����㷨��80�������һ��������
	context->Intermediate_Hash[0] += A;
	context->Intermediate_Hash[1] += B;
	context->Intermediate_Hash[2] += C;
	context->Intermediate_Hash[3] += D;
	context->Intermediate_Hash[4] += E;
	context->Message_Block_Index = 0;
}
//�������ģ��
void SHA1PadMessage(SHA1Context* context){
	if (context->Message_Block_Index > 55){
		context->Message_Block[context->Message_Block_Index++] = 0x80;
		while (context->Message_Block_Index < 64){
			context->Message_Block[context->Message_Block_Index++] = 0;
		}
		SHA1ProcessMessageBlock(context);
		while (context->Message_Block_Index < 56){
			context->Message_Block[context->Message_Block_Index++] = 0;
		}
	}else{
		context->Message_Block[context->Message_Block_Index++] = 0x80;
		while (context->Message_Block_Index < 56){
			context->Message_Block[context->Message_Block_Index++] = 0;
		}
	}

	//�����64λ����Ϊ���ݳ���
	context->Message_Block[56] = context->Length_High >> 24;
	context->Message_Block[57] = context->Length_High >> 16;
	context->Message_Block[58] = context->Length_High >> 8;
	context->Message_Block[59] = context->Length_High;
	context->Message_Block[60] = context->Length_Low >> 24;
	context->Message_Block[61] = context->Length_Low >> 16;
	context->Message_Block[62] = context->Length_Low >> 8;
	context->Message_Block[63] = context->Length_Low;
	SHA1ProcessMessageBlock(context);
}
//����Ϊ���ݳ�ʼ��֮����
int SHA1Reset(SHA1Context* context){
	if (!context){
		return shaNull;
	}

	context->Length_Low = 0;
	context->Length_High = 0;
	context->Message_Block_Index = 0;

	context->Intermediate_Hash[0] = 0x67452301;
	context->Intermediate_Hash[1] = 0xEFCDAB89;
	context->Intermediate_Hash[2] = 0x98BADCFE;
	context->Intermediate_Hash[3] = 0x10325476;
	context->Intermediate_Hash[4] = 0xC3D2E1F0;

	context->Computed = 0;
	context->Corrupted = 0;
	return shaSuccess;
}
//����һ��160���ص���ϢժҪ����,��������������
int SHA1Result(SHA1Context* context,uint8_t Message_Digest[SHA1HashSize]){
	if (!context || !Message_Digest)return shaNull;
	if (context->Corrupted)return context->Corrupted;
	
	if (!context->Computed){
		SHA1PadMessage(context);
		for (int i = 0; i < 64; ++i){
			// ��Ϣ���� 
			context->Message_Block[i] = 0;
		}
		context->Length_Low = 0;// ��������
		context->Length_High = 0;
		context->Computed = 1;
	}
	for (int i = 0; i < SHA1HashSize; ++i){
		Message_Digest[i] = context->Intermediate_Hash[i >> 2]>> 8 * (3 - (i & 0x03));
	}
	return shaSuccess;
}
//���뵥λ����Ϊ8�ֽڱ�������Ϣ
int SHA1Input(SHA1Context* context,const uint8_t* message_array,unsigned length){
	if (!length)return shaSuccess;
	if (!context || !message_array)return shaNull;
	if (context->Computed){
		context->Corrupted = shaStateError;
		return shaStateError;
	}
	if (context->Corrupted){
		return context->Corrupted;
	}
	while (length-- && !context->Corrupted){
		context->Message_Block[context->Message_Block_Index++] =(*message_array & 0xFF);

		context->Length_Low += 8;
		if (context->Length_Low == 0) {
			context->Length_High++;
			if (context->Length_High == 0) {
				//�����޶�����
				context->Corrupted = 1;
			}
		}
		if (context->Message_Block_Index == 64){
			SHA1ProcessMessageBlock(context);
		}
		message_array++;
	}
	return shaSuccess;
}

void SHA1Interface(string a) {
	cout << "SHA1�㷨:" << endl;
	SHA1Context* context=new SHA1Context();
	uint8_t Message_Digest[SHA1HashSize];
    uint8_t* message_array = new uint8_t();
    for(int i=0;i<a.length();i++){
        message_array[i]=a[i];
    }
	SHA1Reset(context);
	SHA1Input(context, message_array, strlen((const char*)message_array));
	SHA1Result(context, Message_Digest);
	cout << "���ɵ�ժҪ:" << endl;
	cout << Message_Digest << endl;
    string tis((char *)Message_Digest);
	ofstream out; out.open("D://tests//sha1//digesttext.txt", ios::binary);
	out << Message_Digest;
}
