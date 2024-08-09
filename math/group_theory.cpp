/*
偶置換と奇置換の判定
→転倒数の偶奇と一致する
*/
//(1) BITで偶奇を求める
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


//atcoder-libraryを用いた実装
ll ans=0;
vector<int>a(n);
	atcoder::fenwick_tree<ll> c(n);	
	rep(i,n){
		cin>>a[i];
		z+=c.sum(a[i],n);
		c.add(a[i]-1,1);
	}


//(2) 置換 i↦P i ​ が偶置換であるかは、 P P i ​ −1 ​ =i なる逆置換 P −1 を持ちながらソートを行うことで Θ(N) 時間で判定できます。
//（置換を disjoint な巡回に分解することでも、線形時間で置換の偶奇を判定することができます。）
//abc296F解説を参照


/*
Burnsideの補題(Cauchy-Frobeniusの定理)
 - Gを有限群として、集合XにGが作用するとする。このとき、
    |X| = \dsum{g \in G} fix(g) /|G|
 が成立する(ただし、fix(g)はgによって不変なXの元の数)

 -> 対称的な対象の数え上げに役に立つ
*/