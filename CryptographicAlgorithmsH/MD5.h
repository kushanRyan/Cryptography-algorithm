#pragma once
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cmath>
using namespace std;
//这玩意是初始化缓冲器
typedef struct {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX; 
unsigned int F(unsigned int x, unsigned int y, unsigned int z);
unsigned int G(unsigned int x, unsigned int y, unsigned int z);
unsigned int H(unsigned int x, unsigned int y, unsigned int z);
unsigned int I(unsigned int x, unsigned int y, unsigned int z);
unsigned int ROTATE_LEFT(unsigned int x, unsigned int n);
void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
void MD5Init(MD5_CTX* context);
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);
void MD5Final(MD5_CTX* context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);
void MD5Interface(string a,string &b,string &c);
