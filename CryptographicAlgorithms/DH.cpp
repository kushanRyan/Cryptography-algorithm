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
//˫��Э����ͬһ��������p��������ԭ��g, �������������XA, XB�����󷽽�g��xA�η�mod p������ֵ���͸����շ���
//���շ��ٽ�g��XB�η�mod p��������ֵ���͸����󷽣������ٶԽ��յ���ֵ��XA�η�����p�������㣬���շ��Խ���
//����ֵ��XB�η�����p�������㣬�����γɹ�ͬ����ԿK���Դﵽ��Կ�Ľ�����

//�����û�A���û�Bϣ������һ����Կ��
//ȡ����p������g��g��p��һ��ԭ��������g��p
//Aѡ�������XA < p��������YA = g ^ XA mod p
//Bѡ�������XB < p��������YB = g ^ XB mod p
//ÿһ������X���ܶ���Y��������һ���õ�
//A������Կ�ķ�ʽ�ǣ�K = (YB) ^ XA modp
//B������Կ�ķ�ʽ�ǣ�K = (YA) ^ XB modp
//A��B��K����ͬ�ģ�K�ǹ�����Կ
//�ж�����
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
//�õ�ŷ��������ֵ��ȡֵ����
void Euler(int n, int* s, int& sum){
	int i, flag;
	for (i = 1; i < n; i++){
		flag = isPrime(i, n);{
			s[sum] = i;
			sum++;
		}
	}
}
//���ݻ��ؼ������ñ����ķ�����ԭ��
void root(int n, int sum, int s[]){
	int i, j;
	int k;
	for (i = 0; i < sum; i++){
		k = 0;
		for (j = 1; j < sum + 1; j++){
			//����Ҫ���ÿ�����ȡ�࣬������ֵ̫������
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
	root(p, sum, s);//�õ�p�����б�ԭ��
	int temp;
    temp=rand() % nums.size();
    a = nums[temp];
}
void summonX(int &Xa,int &Xb) {//���������
	while (1) {
		Xa = 2 + rand() % 30;//���Ʋ������������2~29֮��
		Xb = 2 + rand() % 30;//���Ʋ������������2~29֮��
		if (Xa != Xb){
			cout << "������ɵ���a=" << Xa << endl;
			cout << "������ɵ���b=" << Xb << endl;
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
	srand((unsigned)time(NULL));//���ʱ�䶨������
	while (1){//�����������p
		p = 2 + (rand() % 1145);//���Ʋ������������2~97֮��
		if (is_prime(p)){
			cout << "������ɵ�����p=" << p << endl;
			break;
		}
		else continue;
	}
    choose(p,g);
	summonX(Xa, Xb);
    summonY(Ya,Yb,g,Xa,Xb,p);
    summonK(Ya, Yb, g, Xa, Xb, p,ka,kb);
}
