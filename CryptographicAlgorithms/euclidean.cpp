#include <iostream>
#include <QString>
#include <QTextStream>
using namespace std;
string qstr2str(const QString qstr){
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}
//计算欧几里得算法
int normalGcd(int M,int N) {
    int tmp;
    //辗转相除法
    while (N > 0) {
        tmp = M % N;
        M = N;
        N = tmp;
    }
    return M;
}
//拓展欧几里得的执行体，递归调用，看着要方便些
//ax1 + by1 = gcd(a, b);
//bx2 + (a mod b)y2 = gcd(b, a mod b);
//根据朴素的欧几里德原理有 gcd(a, b) = gcd(b, a mod b);
//则:ax1 + by1 = bx2 + (a mod b)y2;
//即:ax1 + by1 = bx2 + (a - (a / b) * b)y2 = ay2 + bx2 - (a / b) * by2;
//根据恒等定理得：x1 = y2; y1 = x2 - (a / b) * y2;
int exGcdRecursive(int a, int b, int& x, int& y) {
    //如果b除完之后返回
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    //递归调用欧几里得算法
    int r = exGcdRecursive(b, a % b, x, y);
    //返回之后按上面的方法进行赋值
    int t = x;
    x = y;
    y = t - a / b * y;
    return r;
}
//扩展欧几里得:存在 x, y 使得 gcd(a, b) = ax + by
void exGcd(int a,int b,int& c,int& d) {
    //x,y用来保存结果，这玩意后面可以用来求逆元
    cout<<a<<" "<<b;
    int x = 0; int y = 0;
    //执行函数
    exGcdRecursive(a, b, x, y);
    cout<<x<<" "<<y<<endl;
    c=x;
    d=y;
}

