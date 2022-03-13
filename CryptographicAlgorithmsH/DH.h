#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

bool is_prime(int number);
int isPrime(int a, int b);
void Euler(int n, int* s, int& sum);
void root(int n, int sum, int s[]);
void choose(int p, int& a);
void summonX(int& Xa, int& Xb);
void summonY(int& Ya, int& Yb, int a, int Xa, int Xb, int p);
void summonK(int& Ya, int& Yb, int a, int Xa, int Xb, int p);
void DHInterface(int &p,int &a,int &b,int &xa,int &xb,int &ka,int &kb);
