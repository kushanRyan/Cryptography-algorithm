#pragma once
#include <string>
#include <QString>
using namespace std;
int ProducePrimeNumber(int prime[]);
int Exgcd(int m, int n, int& x);
long long Exgcd(long long m, long long n, long long& x);
void RSA_Initialize(int &a,int &b,int &c);
void RSA_Encrypt();
void RSA_Decrypt();
void Initialize();
void RSAInterface(QString message,int &a,int &b,int &c);
