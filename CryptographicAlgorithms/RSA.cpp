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
vector<long long> ciphertext,finciphertext;//����
int prime[5000];
int n, e = 0, d;
//����1000��������
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
//ŷ�������չ�㷨
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
//RSA��ʼ��
//ѡ������������p��q������p��q�ĳ˻�n������p - 1��q - 1�ĳ˻���ѡ��һ����p - 1��q - 1�˻����ʵ���e�������d
void RSA_Initialize(){
    //ȡ��1000������������prime[]������
    int count_Prime = ProducePrimeNumber(prime);
    //���ȡ��������p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand() % count_Prime;
    int ranNum2 = rand() % count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];
    n = p * q;
    int On = (p - 1) * (q - 1);
    //��ŷ�������չ�㷨��e,d
    for (int j = 3; j < On; j += 1331){
        int gcd = Exgcd(j, On, d);
        if (gcd == 1 && d > 0){
            e = j;
            break;
        }
    }
}
//RSA����
//����=m^e(mod n)
void RSA_Encrypt(int &e1,int &d1,int &n1){
    //��ȡ����
    string temp;
    ifstream in;
    in.open("D://tests//rsa//plaintext.txt", ios::binary);
    in>>temp;
    vector<long long> plaintext;//����
    cout << "��Կ(e, n) : e = " << e << " n = " << n << '\n';
    cout << "˽Կ(d, n) : d = " << d << " n = " << n << '\n' << '\n';
    e1=e;d1=d;n1=n;
    int i = 0;
    //������д��ll �����������string �����
    for (int i = 0; i < temp.length(); i++) {
        plaintext.push_back(temp[i]);
    }
    //���ܣ�������ll����
    for (i = 0; i < plaintext.size(); i++) {
        long long temp = mod_pow(plaintext[i], e, n);
        ciphertext.push_back(temp);
    }
    cout << "���ܽ��:" << '\n';
    for (i = 0; i < plaintext.size(); i++) {
        cout << (char)ciphertext[i];
    }
    //�������
    ofstream out;
    out.open("D://tests//rsa//ciphertext.txt", ios::binary);
    for (auto a : ciphertext) {
        out<<(char*)&a;
    }
    cout << endl;
}
//RSA����
//����=c^d(mod n)
void RSA_Decrypt(){
    //��������н�������
    for (int i = 0; i < ciphertext.size(); i++) {
        long long temp = mod_pow(ciphertext[i], d, n);
        finciphertext.push_back(temp);
    }
    cout << "���ܽ��:" << '\n';
    for (int i = 0; i < finciphertext.size(); i++) {
        cout << (char)finciphertext[i];
    }
    //������뵽�ĵ�
    ofstream out;
    out.open("D://tests//rsa//ciphertext.txt", ios::binary);
    for (auto a : finciphertext) {
        out << (char*)&a;
    }
    cout << endl;
}
//�㷨��ʼ��
void Initialize(string message){
    string temp=message;
    ofstream out;
    out.open("D://tests//rsa//plaintext.txt", ios::binary );
    out << temp;
}
//RSA�㷨�ӿ�
void RSAInterface(QString message,int &e1,int &d1,int &n1){
    Initialize(message.toStdString());
    while (!e)
        RSA_Initialize();
    RSA_Encrypt(e1,d1,n1);
    RSA_Decrypt();
}
//������㷨˼��Ƚϼ򵥣���Ҫ�����������ο����������Լ��ļ����棨�������Ĳ���Ū����
