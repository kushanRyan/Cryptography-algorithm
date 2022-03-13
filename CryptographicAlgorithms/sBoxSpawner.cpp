#include <iostream>
#include "CryptographicAlgorithmsH/AES.h"
#include "CryptographicAlgorithmsH/deAES.h"
using namespace std;
//uint8_tʵ������һ��char���������uint8_t���͵ı���ʵ����������Ӧ���ַ�����������ֵ
//GF(2^8)�Ķ���ʽ�˷�
uint16_t polynomialMutil(uint8_t a, uint8_t b) {
    uint16_t tmp[8] = { 0 };
    uint8_t i;

    //��ÿ����Ӧλ�õ�
    for (i = 0; i < 8; i++){
        //a��iλ*(b������iλ������λ)
        tmp[i] = (a << i) * ((b >> i) & 0x1);
    }
    //��ÿλ�Ľ���������֮����ܹ��õ�GF(2^8)�Ķ���ʽ�˷��Ľ��
    tmp[0] = tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3] ^ tmp[4] ^ tmp[5] ^ tmp[6] ^ tmp[7];

    return tmp[0];
}
//GF(2^8)�Ķ���ʽ����-------------------------------------------------------------------------------------------------------
uint8_t gf28_div(uint16_t div_ed, uint16_t div, uint16_t* remainder) {
    uint16_t r0 = 0;
    uint8_t  qn = 0;
    int bitCnt = 0;

    r0 = div_ed;

    bitCnt = findHigherBit(r0) - findHigherBit(div);
    while (bitCnt >= 0){
        //����
        qn = qn | (1 << bitCnt);
        //������
        r0 = r0 ^ (div << bitCnt);
        bitCnt = findHigherBit(r0) - findHigherBit(div);
    }
    *remainder = r0;
    return qn;
}
//�ҵ����λ
uint8_t findHigherBit(uint16_t val) {
    int i = 0;
    //ÿ����λ��ֱ���Ƶ����λ
    while (val){
        i++;
        val = val >> 1;
    }
    return i;
}

//GF(2^8)����ʽ����չŷ������㷨-------------------------------------------------------------------------------------------
//�����ϵ��������ƣ������õ��ǻ���GF��2^8�ĳ�/������
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
        //���㷨��Ψһ�����������ط�
        //qn�� 169 = 1*121+48 121 = 2*48+25 ��1 2
        qn = gf28_div(A, B, &r2);
        //GF�ļӼ�����һ�����������
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
//S���ֽڱ任---------------------------------------------------------------------------------------------------------------
uint8_t byteTransformation(uint8_t a, uint8_t x) {
    uint8_t tmp[8] = { 0 };

    for (uint8_t i = 0; i < 8; i++) {
        tmp[i] = (((a >> i) & 0x1) ^ ((a >> ((i + 4) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 6) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
    }
    tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
    return tmp[0];
}
//��S���ֽڱ任-------------------------------------------------------------------------------------------------------------
uint8_t invByteTransformation(uint8_t a, uint8_t x) {
    uint8_t tmp[8] = { 0 };

    for (uint8_t i = 0; i < 8; i++) {
        tmp[i] = (((a >> ((i + 2) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
    }
    tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
    return tmp[0];
}
//S�в���-------------------------------------------------------------------------------------------------------------------
void spwanSbox(int S[16][16]) {
    uint8_t i, j;

    //��ʼ��S��
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
        }
    }
    //����GF(2^8)���ϵ��棬0ӳ�䵽����
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            if (S[i][j] != 0) {
                S[i][j] = extEuclidPolynomial(S[i][j], 0x11B);
            }
        }
    }
    //��ÿ���ֽ����任
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S[i][j] = byteTransformation(S[i][j], 0x63);
        }
    }
}
//��S�в���
void spwanInvSbox(int S1[16][16]){
    uint8_t i, j;
    uint8_t b = 0, bb = 0;

    //��ʼ��S��
    for (i = 0; i < 0x10; i++){
        for (j = 0; j < 0x10; j++){
            S1[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
        }
    }
    //��ÿ���ֽ����任
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            S1[i][j] = invByteTransformation(S1[i][j], 0x05);
        }
    }
    //����GF(2^8)���ϵ��棬0ӳ�䵽����
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            if (S1[i][j] != 0) {
                S1[i][j] = extEuclidPolynomial(S1[i][j], 0x11B);
            }
        }
    }
}
