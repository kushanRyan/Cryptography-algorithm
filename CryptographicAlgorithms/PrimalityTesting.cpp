#include <iostream>
using namespace std;
//unsigned int_64的范围0~18446744073709551615(10^20)
typedef long long int ll;

ll mod_mul(ll a, ll b, ll mod){//快速积运算，快速求出a^m^*a^m^并且能防止爆掉
    ll res = 0;
    while (b){
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}
ll mod_pow(ll a, ll n, ll mod){//快速幂计算快速求出a^m^的值
    ll res = 1;
    //while (a < 0)a += mod;
    while (n){
        if (n & 1)
            res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}

// Miller-Rabin随机算法检测n是否为素数
//二次探测定理：如果p是一个素数，那么使得x^2 ≡ 1 (mod p)的 x的解只有两种可能，就是x = 1 或者 x = p-1
//Miller-Rabin算法正确率为75%，所以要进行大约4~8次来提高正确率

//假设n为奇素数，那么满足方程x^2≡1（mod n）的解为x = 1 或者 x = n-1。
//又已知费马小定理 an - 1≡1（mod n）
//已知n为奇数，那么n - 1一定为偶数，我们可以设n - 1 = m * 2t。其中m一定为奇数，否则就可以并到2t里面。其实原本是n - 1 = m * qt。(为了计算,q特殊化为2)
//求m和t:m一定是奇数，所以只要给n - 1不断地除2，直到n - 1变为奇数，那么m就是这个奇数，设初始t为0，每次(n - 1)除以2后，t都加一。这样t和m都求出来了。
//接下来我们从[1, n - 1]里面随机取一个a，容易得到an - 1 = a ^ (m * (2 ^ t)), 又由二次探索可知不断的递归下去，不断的用二次探索定理，
//直到最后am = 1(mod n) 或者am = n-1(mod n)，中间只要有一个不满足二次测试定理，那么这个数就一定是合数，否则就有3/4的概率为质数。
bool PTMiller_Rabin(ll n){//首先对于要判断的数n，先判断是不是2，是就直接返回true。
    if (n == 2)
        return true;
    if (n < 2 || !(n & 1))//判断是不是小于2或者为偶数，是就返回false.
        return false;
    ll m = n - 1, t = 0;
    //求出n-1 = m*2^t的m和t。
    while (!(m & 1)){
        t++;
        m >>= 1;
    }
    for (int i = 1; i <= 20; i++){// 20为Miller-Rabin测试的迭代次数
        ll a = rand() % (n - 1) + 1;//利用rand随机找一个a， a属于[1， n - 1]
        ll x = mod_pow(a, m, n); // 令x = (a^m) % n, 然后进行t次循环, 在循环中每次都进行 y = （x * x） % n， x = y 的操作
        ll y;
        for (int j = 1; j <= t; j++){
            y = mod_mul(x, x, n);//又因为x在循环时是一定小于n的，所以可以用二次探测定理
            if (y == 1 && x != 1 && x != n - 1)//运算过程中如果(x2) % n = 1, 也就是y = 1，假如n是素数，那么x == 1 或者x == n - 1，否则n就一定不是素数，直接返回false
                return false;
            x = y;
        }
        if (x != 1)//整个循环结束后，程序运行到最后x = an-1, 根据费马小定理，如果x还是不等于1，那么肯定不是素数，直接返回false
            return false;
    }
    return true;
}

int PrimalityTestingInterface(ll n) {
    if (PTMiller_Rabin(n)) {
        return 1;
    }
    return 0;
}
