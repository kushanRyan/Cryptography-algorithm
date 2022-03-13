#include<iostream>
#include<fstream>
#include <math.h>
#include"CryptographicAlgorithmsH/PrimalityTesting.h"
#define ll long long
using namespace std;
//密钥对生成
//随机选择一个满足安全要求的大素数p，并生成有限域Zp的一个生成元g
//选择一个随机数x(1 < x < p - 1)，计算y = g^x mod p
//用户的公钥为（y, g, p），私钥为x
//假设A使用B的公钥yB对消息m <= p - 1进行加密后将对应的密文c发给B，A的加密如下：

//A在[1, p - 1]上选随机数k
//计算c1 = g^k mod p，c2 = yB^k ∙ m mod p
//密文c = (c1, c2)
//加密算法
void encryption(int m, int pub, int p, int g, int* c1, int* c2) {
    int k = 5;
    *c1 = mod_pow(g, k, p);
    *c2 = m * mod_pow(pub, k, p) % p;
}
//B收到密文c后，使用自己的私钥xB解密如下：
//计算 m = (c1^xB)-1 ∙ c2 mod p
//解密算法
int decryption(int c1, int c2, int pri, int p, int g) {
    int m;
    int c1_ = mod_pow(c1, p - 2, p);
    m = c2 * mod_pow(c1_, pri, p) % p;
    return m;
}
//判断是否为素数
int isPrime(int p) {
    int i;
    for (i = 2; i <= sqrt(p); i++) {
        if (p % i == 0)
            return 0;
    }
    return 1;
}
void Elgamalexcute(int& c11,int& c22,int& message,int& plain,int& priavteKey,int& publicKey) {
    int p;//素数
    int g = 2;
    //随机选择一个满足安全要求的素数p，并生成有限域Zp的一个生成元g
    //选择一个随机数x(1 < x < p - 1)，计算y = g^x mod p
    while (1) {//产生随机素数p
        p = 1453 + (rand() % 2048);//控制产生的随机数在1453~11455之间
        if (isPrime(p)) {
            cout << "随机生成的素数p=" << p << endl;
            break;
        }
        else continue;
    }
    cout << endl;

    int pri = 2 + (rand() % 1145);
    cout << "随机生成A的私钥:p=" << pri << endl;
    int pub; pub = mod_pow(g, pri, p);
    cout << "A的公钥是:" << endl << pub << endl;
    int c1, c2;
    char m=(char)message;
    encryption(m, pub, p, g, &c1, &c2);
    cout << "密文对是" << endl << "(" << c1 << "," << c2<<")" << endl;;

    char m_ = decryption(c1, c2, pri, p, g);
    cout << "输入的明文字符串是:" << m_<<endl;
    //每次加解密很麻烦，密文对存在文本里更麻烦，这大概就是效率低的原因罢
    priavteKey=pri;publicKey=pub;
    c11=c1;c22=c2;
    message=(int)m_;
}
void ElgamalInterface(int& c1,int& c2,int& message,int& plain,int& priavteKey,int& publicKey) {
    cout << "Elgamal算法" << endl;
    Elgamalexcute(c1,c2,message,plain,priavteKey,publicKey);
}
