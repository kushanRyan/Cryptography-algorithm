#ifndef AES_H
#define AES_H
#include "sBoxSpawner.h"
//��Կ��չ����
static int keyMatrix[44];
//����
static int cipherTest[4][4] = {};
//AES����
//�������ߺ���----------------------------------------------------------------------------------------------------
void convertToIntArray(char* str, int pa[4][4]);
void convertArrayToStr(int array[4][4], char* str);
//��Կ��չ----------------------------------------------------------------------------------------------------
int getIntFromChar(char c);
int getWordFromStr(char* str);
int mergeArrayToInt(int array[4]);
int T(int num, int round, int S[16][16]);
void expandedKey(char* cipher, int S[16][16]);
//�ֽڴ���----------------------------------------------------------------------------------------------------
int getLeft4Bit(int num);
int getRight4Bit(int num);
int getNumFromSBox(int index, int S[16][16]);
void subBytes(int textContainer[4][4],int S[16][16]);
//����λ------------------------------------------------------------------------------------------------------
void arrayLeftMove(int array[4], int step);
void shiftRow(int textContainer[4][4]);
//�л���------------------------------------------------------------------------------------------------------
int GFNo2(int s);
int GFNo3(int s);
int GFNo4(int s);
int GFNo5(int s);
int GFNo6(int s);
int GFNo7(int s);
int GFNo8(int s); 
int GFNo9(int s);
int GFNo10(int s);
int GFNo11(int s);
int GFNo12(int s);
int GFNo13(int s);
int GFNo14(int s);
int GFNo15(int s);
int GFMain(int n, int s);
void mixColumn(int textContainer[4][4]);
//����Կ��----------------------------------------------------------------------------------------------------
void splitIntToArray(int num, int array[4]);
void addRoundKey(int textContainer[4][4], int round);
//��������AES�㷨
void AES(char* container, char* cipher,int S[16][16]);
void excuteAES(string a,string key);
#endif
