#include <iostream>
#include <bitset>
using namespace std;

void generateKeys();
bitset<28> leftShift(bitset<28> k, int shift);
bitset<32> f(bitset<32> R, bitset<48> k);
bitset<64> encrypt(bitset<64>& plain);
bitset<64> decrypt(bitset<64>& cipher);
void DESInterface(string mes,string key);
