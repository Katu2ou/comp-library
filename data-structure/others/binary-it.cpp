/*
BIT : セグ木の機能を制限した上で、実装を簡単にし、定数倍高速化と省メモリを施したもの
<機能> 長さNの配列に対し、要素の1点変更と区間和をそれぞれO(logN)で求める

AC Libraryのものは0-indexed
    fenwick_tree<T> fw(int n)   //長さnの配列a_0,...,a_{n-1}を作る(n<=10^8) ex)T=ll
    void fw.add(int p, T x)     //a_pにxを加算する O(logn)
    T fw.sum(int l, int r)    //[l,r)の区間和を求める O(logn)
*/


//(1) 転倒数を求める
struct fenwick_tree {
    typedef int T;
    T n;
    vector<T> bit;

    // 各要素の初期値は 0
    fenwick_tree(T num) : bit(num+1, 0) { n = num; }

    // a_i += w
    void add(T i, T w) {
        for (T x = i; x <= n; x += x & -x) {
            bit[x] += w;
        }
    }
    // [1, i] の和を計算.
    T sum(T i) {
        T ret = 0;
        for (T x = i; x > 0; x -= x & -x) {
            ret += bit[x];
        }
        return ret;
    }
    // [left+1, right] の和を計算.
    T sum(T left, T right) {
        return sum(right) - sum(left);
    }
};

fenwick_tree f_tree(n); //配列の長さを入れてBITを作る
ll ans=0;
vector<ll> a(n);
for (int j = 0; j < n; j++) {
    ans += j - f_tree.sum(a[j]);
    f_tree.add(a[j], 1);
}

//atcoder libraryを使った実装
ll ans=0;
vector<int>a(n);
	atcoder::fenwick_tree<ll> c(n);	
	rep(i,n){
		cin>>a[i];
		z+=c.sum(a[i],n);
		c.add(a[i]-1,1);
	}


//(2) BIT上の二分探索
// 𝑎0+𝑎1+…+𝑎𝑥>=w  となるような最小の x をO(logn)で取得する(ただしa_i>=0)
atcoder::fenwick_tree<ll> bit(n);

int lower_bound_BIT(T w){
     if (w <= 0) {
        return 0;
    } 
    else {
        int x = 0, r = 1;
        while (r < n) r = r << 1;
        for (int len = r; len > 0; len = len >> 1) { // 長さlenは1段下るごとに半分に
            if (x + len < n && bit[x + len] < w) { // 採用するとき
                w -= bit[x + len];
                x += len;
            }
        }
        return x ;
    }

}



//(3) w番目に小さい要素の取得
/*
(要素種類数が比較的少ないような)集合Sを管理して、
    - a が何番目に小さいか
    - w 番目に小さい要素 a は何か
をO(logn)で取得する

    - add(a,1): 集合への要素 a の追加(a 番目を 1 にする)
    - add(a,-1): 集合への要素 a の削除(a 番目を 1 から 0 にする)
    - sum(a): a が何番目に小さいか
    - lower_bound_BIT(w): w 番目に小さい要素 a は何か
値の範囲が N までとした時、消費メモリは 𝑂(𝑁), 計算量はそれぞれ 𝑂(𝑙𝑜𝑔𝑁) だけかかる

*/


//(4) 2次元BIT
/*
H*Wの二次元のBITは、要素数WのBITを縦にH個並べたBITとして管理する
加算,区間和(0<=i<h)かつ0<=j<wの部分)をそれぞれO(logHlogW)で求めることができる
*/

