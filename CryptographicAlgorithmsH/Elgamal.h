#pragma once

void encryption(int m, int pub, int p, int g, int* c1, int* c2);
int decryption(int c1, int c2, int pri, int p, int g);
void ElgamalInterface(int& c1,int& c2,int& message,int& plain,int& priavteKey,int& publicKey);
int isPrime(int p);
