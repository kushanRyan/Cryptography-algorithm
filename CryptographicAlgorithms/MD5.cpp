#include<iostream>
#include<fstream>
#include"CryptographicAlgorithmsH/PrimalityTesting.h"
#include"CryptographicAlgorithmsH/MD5.h"
using namespace std;
//(M)message(D)摘要 算法
unsigned char encrypt[10000000];
//MD5算法过程：
//对MD5算法简要的叙述可以为：MD5以512位分组来处理输入的信息，且每一分组又被划分为16个32位子分组，经过了一系列的处理后，
//算法的输出由四个32位分组组成，将这四个32位分组级联后将生成一个128位散列值。
//第一步、填充：如果输入信息的长度(bit)对512求余的结果不等于448，就需要填充使得对512求余的结果等于448。填充的方法是填充一个1和n个0。
//填充完后，信息的长度就为N * 512 + 448(bit)；
//第二步、记录信息长度：用64位来存储填充前信息长度。这64位加在第一步结果的后面，这样信息长度就变为N * 512 + 448 + 64 = (N + 1) * 512位。
//第三步、装入标准的幻数（四个整数）：标准的幻数（物理顺序）是（A = (01234567) 16 ，B = (89ABCDEF) 16 ，C = (FEDCBA98)16 ，D = (76543210) 16 ）。
//如果在程序中定义应该是（A = 0X67452301L，B = 0XEFCDAB89L，C = 0X98BADCFEL，D = 0X10325476L）
//第四步、四轮循环运算：循环的次数是分组的个数（N + 1）
unsigned char PADDING[] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//定义4个辅助函数，每个函数的输入是三个32位的字，输出是一个32位的字
unsigned int F(unsigned int x, unsigned int y, unsigned int z) {
    return ((x & y) | (~x & z));
} 
unsigned int G(unsigned int x, unsigned int y, unsigned int z) {
    return ((x & z) | (y & ~z));
}
unsigned int H(unsigned int x, unsigned int y, unsigned int z) {
    return (x ^ y ^ z);
}
unsigned int I(unsigned int x, unsigned int y, unsigned int z) {
    return (y ^ (x | ~z));
}
//将x左移n位的结果和x右移(32-n)的结果进行或运算
unsigned int ROTATE_LEFT(unsigned int x, unsigned int n) {
    return ((x << n) | (x >> (32 - n)));
}
//表示a = b + ((a + F(b, c, d) + Mj + ti) << < s)
void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) { 
    a+=F(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;
}
//表示a = b + ((a + G(b, c, d) + Mj + ti) << < s)
void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) { 
    a+=G(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;
}
//表示a = b + ((a + H(b, c, d) + Mj + ti) << < s)
void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) { 
    a+=H(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;
}
//表示a = b + ((a + I(b, c, d) + Mj + ti) << < s)
void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) { 
    a+=I(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;
}

//对缓冲区进行初始化
void MD5Init(MD5_CTX* context) {
    //用一个四个字的缓冲器(A，B，C，D)来计算报文摘要，A, B, C, D分别是32位的寄存器，初始化使用的是十六进制表示的数字(小端序)
    context->count[0] = 0;
    context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
}

void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen) {
    unsigned int i = 0, index = 0, partlen = 0;
    index = (context->count[0] >> 3) & 0x3F;//模64字节的余数，第一次调用为0
    partlen = 64 - index;//第一次partlen为64
    //预留最前面的64位存放数据长度(这个地方没看懂，/(ㄒoㄒ)/~~)
    context->count[0] += inputlen << 3;//文本总的位数,低32位
    if (context->count[0] < (inputlen << 3)) 
        context->count[1]++;
    context->count[1] += inputlen >> 29;//先左移3,求出位数,再右移32位，求出左32位
    //如果输入的长度大于64位
    if (inputlen >= partlen) {
        //将第一个512进行变形
        memcpy(&context->buffer[index], input, partlen);
        MD5Transform(context->state, context->buffer);
        //接下来的依旧以512位为1组
        for (i = partlen; i + 64 <= inputlen; i += 64) 
            MD5Transform(context->state, &input[i]);
        index = 0;
    }else i = 0;
    //将最后剩的那点截下来处理（可能不到512位）
    memcpy(&context->buffer[index], &input[i], inputlen - i);//最后剩下的一部分
}
//32位md5
void MD5Final(MD5_CTX* context, unsigned char digest[16]) {
    unsigned int index = 0, padlen = 0;
    unsigned char bits[8];
    index = (context->count[0] >> 3) & 0x3F;//模64字节的余数
    if (index < 56) {//需要填充的长度，注意长度占8字节
        padlen = (56 - index);
    }else {
        padlen = (120 - index);
    }
    MD5Encode(bits, context->count, 8);
    MD5Update(context, PADDING, padlen);
    MD5Update(context, bits, 8);
    MD5Encode(digest, context->state, 16);
}
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len) {
    //len是char的长度
    for (unsigned int i = 0, j = 0; j < len; j += 4, i++) {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
    }
}
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len) {
    //将input每四位的数据搓到一个数字里面(移位并进行或运算)
    for (unsigned int i = 0, j = 0; j < len;j+=4,i++) {
        output[i] = (input[j]) | (input[j + 1] << 8) | (input[j + 2] << 16) | (input[j + 3] << 24);
    }
}

void MD5Transform(unsigned int state[4], unsigned char block[64]) {
    unsigned int a = state[0];
    unsigned int b = state[1];
    unsigned int c = state[2];
    unsigned int d = state[3];
    unsigned int x[16];

    MD5Decode(x, block, 64);
    FF(a, b, c, d, x[0], 7, 0xd76aa478);//32位运算
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);


    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);


    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);


    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
void MD5Excute(string a,string &b,string &c) {
    for(int i=0;i<a.length();i++){
        encrypt[i]=a[i];
    }
    unsigned char decrypt[16];
    MD5_CTX md5;
    //md5初始化
    MD5Init(&md5);
    //处理
    MD5Update(&md5, encrypt, (int)strlen((char*)encrypt));//只是个中间步骤
    MD5Final(&md5, decrypt);//32位
    for(int i=0;i<12;i++)b+=decrypt[i];
    for(int i=0;i<16;i++)c+=decrypt[i];
    ofstream out;out.open("D://tests//md5//digesttext.txt", ios::binary);
    out << decrypt;
}
void MD5Interface(string a,string &b,string &c) {
    MD5Excute(a,b,c);
    cout << endl;
}
