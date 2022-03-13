#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
//uint8_t实际上是一个char。所以输出uint8_t类型的变量实际上输出其对应的字符，而不是数值
//GF(2^8)的多项式乘法
uint16_t polynomialMutil(uint8_t a, uint8_t b) {
    uint16_t tmp[8] = { 0 };
    uint8_t i;

    //将每个对应位置的
    for (i = 0; i < 8; i++){
        //a移i位*(b向右移i位的最后二位)
        tmp[i] = (a << i) * ((b >> i) & 0x1);
    }
    //将每位的结果进行异或之后就能够得到GF(2^8)的多项式乘法的结果
    tmp[0] = tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3] ^ tmp[4] ^ tmp[5] ^ tmp[6] ^ tmp[7];

    return tmp[0];
}
//GF(2^8)的多项式除法-------------------------------------------------------------------------------------------------------
uint8_t gf28_div(uint16_t div_ed, uint16_t div, uint16_t* remainder) {
    uint16_t r0 = 0;
    uint8_t  qn = 0;
    int bitCnt = 0;

    r0 = div_ed;

    bitCnt = findHigherBit(r0) - findHigherBit(div);
    while (bitCnt >= 0){
        //求余
        qn = qn | (1 << bitCnt);
        //求余数
        r0 = r0 ^ (div << bitCnt);
        bitCnt = findHigherBit(r0) - findHigherBit(div);
    }
    *remainder = r0;
    return qn;
}
//找到最高位
uint8_t findHigherBit(uint16_t val) {
    int i = 0;
    //每次移位，直到移到最高位
    while (val){
        i++;
        val = val >> 1;
    }
    return i;
}

//GF(2^8)多项式的扩展欧几里得算法-------------------------------------------------------------------------------------------
//和书上的例子类似，但它用的是基于GF（2^8的乘/除法）
uint8_t extEuclidPolynomial(uint8_t a, uint16_t m){
    uint16_t A, B, r2;
    uint8_t  qn, S0, S1, S2, T0, T1, T2;

    A = m;
    B = a;

    S0 = 1;
    S1 = 0;

    T0 = 0;
    T1 = 1;

    while (B != 1){
        //-----------------------------------
        //该算法的唯一区别就在这个地方
        //qn是 169 = 1*121+48 121 = 2*48+25 的1 2
        qn = gf28_div(A, B, &r2);
        //GF的加减法都一样，都是异或
        S2 = S0 ^ polynomialMutil(qn, S1);
        T2 = T0 ^ polynomialMutil(qn, T1);
        //----------------------------------
        A = B;
        B = r2;

        S0 = S1;
        S1 = S2;

        T0 = T1;
        T1 = T2;
    }
    return T1;
}
//S盒字节变换---------------------------------------------------------------------------------------------------------------
uint8_t byteTransformation(uint8_t a, uint8_t x) {
    uint8_t tmp[8] = { 0 };

    for (uint8_t i = 0; i < 8; i++) {
        tmp[i] = (((a >> i) & 0x1) ^ ((a >> ((i + 4) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 6) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
    }
    tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
    return tmp[0];
}
//逆S盒字节变换-------------------------------------------------------------------------------------------------------------
uint8_t invByteTransformation(uint8_t a, uint8_t x) {
    uint8_t tmp[8] = { 0 };

    for (uint8_t i = 0; i < 8; i++) {
        tmp[i] = (((a >> ((i + 2) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
    }
    tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
    return tmp[0];
}
//S盒产生-------------------------------------------------------------------------------------------------------------------
void spwanSbox(int S[16][16]) {
    uint8_t i, j;

    //初始化S盒
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
        }
    }
    //求在GF(2^8)域上的逆，0映射到自身
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            if (S[i][j] != 0) {
                S[i][j] = extEuclidPolynomial(S[i][j], 0x11B);
            }
        }
    }
    //对每个字节做变换
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S[i][j] = byteTransformation(S[i][j], 0x63);
        }
    }
}
//逆S盒产生
void spwanInvSbox(int S1[16][16]){
    uint8_t i, j;
    uint8_t b = 0, bb = 0;

    //初始化S盒
    for (i = 0; i < 0x10; i++){
        for (j = 0; j < 0x10; j++){
            S1[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
        }
    }
    //对每个字节做变换
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S1[i][j] = invByteTransformation(S1[i][j], 0x05);
        }
    }
    //求在GF(2^8)域上的逆，0映射到自身
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            if (S1[i][j] != 0) {
                S1[i][j] = extEuclidPolynomial(S1[i][j], 0x11B);
            }
        }
    }
}
