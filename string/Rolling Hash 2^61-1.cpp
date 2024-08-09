//Rolling Hash
/*
高速に文字列検索を行うための方法(O(n+m))
任意のa,b(a<=b)について、hash([a,b])をO(1)で求められる(ハッシュの作り方より[0,b],[0,a-1]から[a,b]が)

m文字の文字列Aに対し、互いに素な基数(base = b)とmod p を取って、
hash(A) = (A_0*b^(m-1) + A_1*b^(m-2) + ... + A_(m-1)*b^0) mod p
とする。(ここでA_iは、Aのi文字目に対応したある値とする 例えばA_i-'a'など)

hが十分に大きい時はハッシュ値の衝突はほとんど起こりにくいと考えられる。
→文字列の一致検証がO(n)からO(1)に高速化できる

//MOD2^61-1を用いる

*/
//単純な実装例

using ulong = unsigned long long; //これはatcoderのjudge環境では不要(CEが出る)

const ulong MASK30 = (1UL << 30) - 1;
const ulong MASK31 = (1UL << 31) - 1;
const ulong MOD = (1UL << 61) - 1; //使用の際はテンプレートのMODを消す
const ulong MASK61 = MOD;
const ulong Base = 27; //基数

//x mod 2^61-1を計算する
ulong CalcMod(ulong x) 
{
    ulong xu = x >> 61;
    ulong xd = x & MASK61;
    ulong res = xu + xd;
    if (res >= MOD) res -= MOD;
    return res;
}

//a*b mod 2^61-1を計算する
ulong Mul(ulong a, ulong b) 
{
    ulong au = a >> 31;
    ulong ad = a & MASK31;
    ulong bu = b >> 31;
    ulong bd = b & MASK31;
    ulong mid = ad * bu + au * bd;
    ulong midu = mid >> 30;
    ulong midd = mid & MASK30;
    return CalcMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
}

//文字列のハッシュ値vectorを作る
vector<ulong> Hashvec(string s){ 
    int n=s.size();
    vector<ulong> res(n);
    ulong prod = 1;
    for(int i=n-1;i>=0;i--){
        res[i]=Mul((ulong)(s-'a')+1,prod);
        prod = Mul(prod,Base);
    }
    return res;
}