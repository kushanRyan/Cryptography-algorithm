#pragma once
#include <iostream>
#include "AES.h"
#include "deAES.h"
using namespace std;
//uint8_t实际上是一个char。所以输出uint8_t类型的变量实际上输出其对应的字符，而不是数值
//GF(2^8)的多项式乘法
uint16_t polynomialMutil(uint8_t a, uint8_t b);
//GF(2^8)的多项式除法-------------------------------------------------------------------------------------------------------
uint8_t gf28_div(uint16_t div_ed, uint16_t div, uint16_t* remainder);
//找到最高位
uint8_t findHigherBit(uint16_t val);

//GF(2^8)多项式的扩展欧几里得算法-------------------------------------------------------------------------------------------
//和书上的例子类似，但它用的是基于GF（2^8的乘法）
uint8_t extEuclidPolynomial(uint8_t a, uint16_t m);
//S盒字节变换---------------------------------------------------------------------------------------------------------------
uint8_t byteTransformation(uint8_t a, uint8_t x);
//逆S盒字节变换-------------------------------------------------------------------------------------------------------------
uint8_t invByteTransformation(uint8_t a, uint8_t x);
//S盒产生-------------------------------------------------------------------------------------------------------------------
void spwanSbox(int S[16][16]);
//逆S盒产生
void spwanInvSbox(int S1[16][16]);