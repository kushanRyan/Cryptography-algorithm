#include <iostream>
#include<QString>
#include"CryptographicAlgorithmsH/RSA.h"
#include"CryptographicAlgorithmsH/PrimalityTesting.h"
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory.h>
#pragma warning(disable:4996)
using namespace std;
vector<long long> ciphertext,finciphertext;//密文
int prime[5000];
int n, e = 0, d;
//生成1000以内素数
int ProducePrimeNumber(int prime[]){
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= 1000; i++)if (!vis[i]){
        prime[c++] = i;
        for (int j = i * i; j <= 1000; j += i)
            vis[j] = 1;
    }

    return c;
}
//欧几里得扩展算法
int Exgcd(int m, int n, int& x){
    int x1, y1, x0, y0, y;
    x0 = 1; y0 = 0;
    x1 = 0; y1 = 1;
    x = 0; y = 1;
    int r = m % n;
    int q = (m - r) / n;
    while (r){
        x = x0 - q * x1; y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        m = n; n = r; r = m % n;
        q = (m - r) / n;
    }
    return n;
}
long long Exgcd(long long m, long long n, long long& x) {
    int x1, y1, x0, y0, y;
    x0 = 1; y0 = 0;
    x1 = 0; y1 = 1;
    x = 0; y = 1;
    int r = m % n;
    int q = (m - r) / n;
    while (r) {
        x = x0 - q * x1; y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        m = n; n = r; r = m % n;
        q = (m - r) / n;
    }
    return n;
}
//RSA初始化
//选择两个大素数p和q，计算p和q的乘积n，计算p - 1和q - 1的乘积，选择一个与p - 1和q - 1乘积互质的数e，计算出d
void RSA_Initialize(){
    //取出1000内素数保存在prime[]数组中
    int count_Prime = ProducePrimeNumber(prime);
    //随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand() % count_Prime;
    int ranNum2 = rand() % count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];
    n = p * q;
    int On = (p - 1) * (q - 1);
    //用欧几里德扩展算法求e,d
    for (int j = 3; j < On; j += 1331){
        int gcd = Exgcd(j, On, d);
        if (gcd == 1 && d > 0){
            e = j;
            break;
        }
    }
}
//RSA加密
//密文=m^e(mod n)
void RSA_Encrypt(int &e1,int &d1,int &n1){
    //读取明文
    string temp;
    ifstream in;
    in.open("D://tests//rsa//plaintext.txt", ios::binary);
    in>>temp;
    vector<long long> plaintext;//明文
    cout << "公钥(e, n) : e = " << e << " n = " << n << '\n';
    cout << "私钥(d, n) : d = " << d << " n = " << n << '\n' << '\n';
    e1=e;d1=d;n1=n;
    int i = 0;
    //将明文写入ll 向量，如果用string 会溢出
    for (int i = 0; i < temp.length(); i++) {
        plaintext.push_back(temp[i]);
    }
    //加密，并放入ll向量
    for (i = 0; i < plaintext.size(); i++) {
        long long temp = mod_pow(plaintext[i], e, n);
        ciphertext.push_back(temp);
    }
    cout << "加密结果:" << '\n';
    for (i = 0; i < plaintext.size(); i++) {
        cout << (char)ciphertext[i];
    }
    //输出密文
    ofstream out;
    out.open("D://tests//rsa//ciphertext.txt", ios::binary);
    for (auto a : ciphertext) {
        out<<(char*)&a;
    }
    cout << endl;
}
//RSA解密
//明文=c^d(mod n)
void RSA_Decrypt(){
    //在这里进行解密运算
    for (int i = 0; i < ciphertext.size(); i++) {
        long long temp = mod_pow(ciphertext[i], d, n);
        finciphertext.push_back(temp);
    }
    cout << "解密结果:" << '\n';
    for (int i = 0; i < finciphertext.size(); i++) {
        cout << (char)finciphertext[i];
    }
    //结果输入到文档
    ofstream out;
    out.open("D://tests//rsa//ciphertext.txt", ios::binary);
    for (auto a : finciphertext) {
        out << (char*)&a;
    }
    cout << endl;
}
//算法初始化
void Initialize(string message){
    string temp=message;
    ofstream out;
    out.open("D://tests//rsa//plaintext.txt", ios::binary );
    out << temp;
}
//RSA算法接口
void RSAInterface(QString message,int &e1,int &d1,int &n1){
    Initialize(message.toStdString());
    while (!e)
        RSA_Initialize();
    RSA_Encrypt(e1,d1,n1);
    RSA_Decrypt();
}
//总体的算法思想比较简单，主要的问题就在如何快速幂运算以及文件保存（这个是真的不好弄！）
