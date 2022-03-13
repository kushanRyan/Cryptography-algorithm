#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <vector>
#include "CryptographicAlgorithmsH/PrimalityTesting.h"
using namespace std;
#define ll long long
int s[10000000], flag[10000000];
vector<int> nums;
//双方协商用同一个大素数p和素数的原根g, 各自生成随机数XA, XB。请求方将g的xA次方mod p产生数值发送给接收方，
//接收方再将g的XB次方mod p产生的数值发送给请求方，请求方再对接收的数值做XA次方并对p求余运算，接收方对接收
//的数值做XB次方并对p求余运算，最终形成共同的密钥K，以达到密钥的交换。

//假如用户A和用户B希望交换一个密钥；
//取素数p和整数g，g是p的一个原根，公开g和p
//A选择随机数XA < p，并计算YA = g ^ XA mod p
//B选择随机数XB < p，并计算YB = g ^ XB mod p
//每一方都将X保密而将Y公开让另一方得到
//A计算密钥的方式是：K = (YB) ^ XA modp
//B计算密钥的方式是：K = (YA) ^ XB modp
//A和B的K是相同的，K是共享秘钥
//判断素数
bool is_prime(int number){
	int i;
	for (i = 2; i <= sqrt(number); i++){
		if (number % i == 0)
			return false;
	}
	if (i > sqrt(number))
		return true;
}
int isPrime(int a, int b){
	int temp;
	while (b != 0){
		temp = b;
		b = a % b;
		a = temp;
	}
	if (a == 1) return 1;
	else return 0;
}
//得到欧拉函数的值和取值集合
void Euler(int n, int* s, int& sum){
	int i, flag;
	for (i = 1; i < n; i++){
		flag = isPrime(i, n);{
			s[sum] = i;
			sum++;
		}
	}
}
//根据互素集合利用遍历的方法求原根
void root(int n, int sum, int s[]){
	int i, j;
	int k;
	for (i = 0; i < sum; i++){
		k = 0;
		for (j = 1; j < sum + 1; j++){
			//这里要利用快速幂取余，否则数值太大会溢出
			flag[j - 1] = mod_pow(s[i], j, n);
		}
		sort(flag, flag+sum);
		for (j = 0; j < sum; j++){
			if (flag[j] != s[j])
				k = 1;
		}
		if (k == 0)
            nums.push_back(s[i]);
	}
}
void choose(int p,int &a) {
	int sum = 0;
	Euler(p, s, sum);
	root(p, sum, s);//得到p的所有本原根
	int temp;
    temp=rand() % nums.size();
    a = nums[temp];
}
void summonX(int &Xa,int &Xb) {//产生随机数
	while (1) {
		Xa = 2 + rand() % 30;//控制产生的随机数在2~29之间
		Xb = 2 + rand() % 30;//控制产生的随机数在2~29之间
		if (Xa != Xb){
			cout << "随机生成的数a=" << Xa << endl;
			cout << "随机生成的数b=" << Xb << endl;
			break;
		} else continue;
	}
}
void summonY(int& Ya, int& Yb,int a,int Xa,int Xb,int p) {
	Ya = a; for (int i = 0; i < Xa; i++)Ya = (Ya % p) * a;
	Ya = Ya % p;
	Yb = a; for (int i = 0; i < Xb; i++)Yb = (Yb % p) * a;
	Yb = Yb % p;
	cout << "YA=" << Ya << " YB=" << Yb << endl;
}
void summonK(int& Ya, int& Yb, int a, int Xa, int Xb, int p,int &KeyA,int &KeyB) {
	KeyA = Yb; for (int i = 0; i < Xa; i++) KeyA = (KeyA % p) * Yb;
	KeyA = KeyA % p;
	KeyB = Ya; for (int i = 0; i < Xb; i++) KeyB = (KeyB % p) * Ya;
	KeyB = KeyB % p;
}
void DHInterface(int &p,int &Xa,int &Xb,int &Ya,int &Yb,int &ka,int &kb) {
    int g;
	srand((unsigned)time(NULL));//随机时间定义种子
	while (1){//产生随机素数p
		p = 2 + (rand() % 1145);//控制产生的随机数在2~97之间
		if (is_prime(p)){
			cout << "随机生成的素数p=" << p << endl;
			break;
		}
		else continue;
	}
    choose(p,g);
	summonX(Xa, Xb);
    summonY(Ya,Yb,g,Xa,Xb,p);
    summonK(Ya, Yb, g, Xa, Xb, p,ka,kb);
}
