#include <iostream>
#include <QString>
#include <QTextStream>
using namespace std;
string qstr2str(const QString qstr){
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}
//����ŷ������㷨
int normalGcd(int M,int N) {
    int tmp;
    //շת�����
    while (N > 0) {
        tmp = M % N;
        M = N;
        N = tmp;
    }
    return M;
}
//��չŷ����õ�ִ���壬�ݹ���ã�����Ҫ����Щ
//ax1 + by1 = gcd(a, b);
//bx2 + (a mod b)y2 = gcd(b, a mod b);
//�������ص�ŷ�����ԭ���� gcd(a, b) = gcd(b, a mod b);
//��:ax1 + by1 = bx2 + (a mod b)y2;
//��:ax1 + by1 = bx2 + (a - (a / b) * b)y2 = ay2 + bx2 - (a / b) * by2;
//���ݺ�ȶ���ã�x1 = y2; y1 = x2 - (a / b) * y2;
int exGcdRecursive(int a, int b, int& x, int& y) {
    //���b����֮�󷵻�
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    //�ݹ����ŷ������㷨
    int r = exGcdRecursive(b, a % b, x, y);
    //����֮������ķ������и�ֵ
    int t = x;
    x = y;
    y = t - a / b * y;
    return r;
}
//��չŷ�����:���� x, y ʹ�� gcd(a, b) = ax + by
void exGcd(int a,int b,int& c,int& d) {
    //x,y��������������������������������Ԫ
    cout<<a<<" "<<b;
    int x = 0; int y = 0;
    //ִ�к���
    exGcdRecursive(a, b, x, y);
    cout<<x<<" "<<y<<endl;
    c=x;
    d=y;
}

