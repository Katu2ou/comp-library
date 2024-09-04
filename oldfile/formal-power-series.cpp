//数え上げの計算を形式的冪級数(特に多項式)の積の計算に帰着させることで高速化する手法

//練習はhttps://kenkoooo.com/atcoder/#/contest/show/accf2cb4-2dc4-402e-994a-055fd9297203?activeTab=Standingsより

/*高速に計算できるもの

//inv, log, exp of FPS
A(x)=\sum_{i=0}^{\infty}a_i x^i に対して、
(1) 1/A(x) の前n項はO(nlogn)で求められる。
(2) log(A(x)) = -\sum_{k=1}^{\infty} (1-A(x))^k/k = \int A'(x)/A(x) 
	の前n項はO(nlogn)で求められる。
(3) exp(A(x))も同様

// pow
(A(x))^k = exp(klog(A(x))) の前n項も上よりO(nlogn)で求められる。

//FFT
M個の多項式f1,f2,...,fMの次数の合計がNのとき、これらの総積はO(nlognlogm)
で求まる(m個の多項式のうち最も次数が小さい2つを掛け合わせることを繰り返す)


(1) 1/(1-T)^k = sum_0^{\infty} (n+k-1,k-1)T^n
(2) fg O(nlogn FFTによる)
(3) 1/f (Newton法でO(nlogn))
(4) logf ([x^0]f=1, n<pを仮定する)
(5) expf ([x^0]f=0, n<pを仮定する)
(6) 多項式補間(平方分割でO(nlog^2n))


//基本手筋
- 無限和を有限の有理式の形に直す
- 得られた式を因数分解する
- (ax+bx^2)^n などの型の式のM次以下の係数は二項定理で全部合わせてO(M)で得られる
- F/(1-x)^n 型の式はFの係数に累積和をn回作用させることで求まる
- 2積FGの一つの次数の係数を知りたいだけならO(deg)で求まる
- (ax+bx^2)^(-n) などの型の式も、負の二項定理より求まる。
( (1-x)^(-n) = dsum_{i=0}^{\infty} C(n-1+i, n-1)x^i )
- 二項係数の和の形などが出てきたら、二項係数を(1+x)^nのある次数の係数としてみて、
多項式の和として見る

//二項係数に関する式の例
/*
( (1-x)^(-n) = dsum_{i=0}^{\infty} C(n-1+i, n-1)x^i )




*/



//基本ライブラリ
//atcoder/allとusing namespace atcoder;が必要
//ei13333氏
template<class T>
struct FormalPowerSeries : vector<T> {
  using vector<T>::vector;
  using vector<T>::operator=;
  using F = FormalPowerSeries;

  F operator-() const {
    F res(*this);
    for (auto &e : res) e = -e;
    return res;
  }
  F &operator*=(const T &g) {
    for (auto &e : *this) e *= g;
    return *this;
  }
  F &operator/=(const T &g) {
    assert(g != T(0));
    *this *= g.inv();
    return *this;
  }
  F &operator+=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] += g[i];
    return *this;
  }
  F &operator-=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] -= g[i];
    return *this;
  }
  F &operator<<=(const int d) {
    int n = (*this).size();
    (*this).insert((*this).begin(), d, 0);
    (*this).resize(n);
    return *this;
  }
  F &operator>>=(const int d) {
    int n = (*this).size();
    (*this).erase((*this).begin(), (*this).begin() + min(n, d));
    (*this).resize(n);
    return *this;
  }
  F inv(int d = -1) const {
    int n = (*this).size();
    assert(n != 0 && (*this)[0] != 0);
    if (d == -1) d = n;
    assert(d > 0);
    F res{(*this)[0].inv()};
    while (res.size() < d) {
      int m = size(res);
      F f(begin(*this), begin(*this) + min(n, 2*m));
      F r(res);
      f.resize(2*m), internal::butterfly(f);
      r.resize(2*m), internal::butterfly(r);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      f.erase(f.begin(), f.begin() + m);
      f.resize(2*m), internal::butterfly(f);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      T iz = T(2*m).inv(); iz *= -iz;
      rep(i, m) f[i] *= iz;
      res.insert(res.end(), f.begin(), f.begin() + m);
    }
    return {res.begin(), res.begin() + d};
  }

  // fast: FMT-friendly modulus only
  F &operator*=(const F &g) {
    int n = (*this).size();
    *this = convolution(*this, g);
    (*this).resize(n);
    return *this;
  }
  F &operator/=(const F &g) {
    int n = (*this).size();
    *this = convolution(*this, g.inv(n));
    (*this).resize(n);
    return *this;
  }

  // // naive
  // F &operator*=(const F &g) {
  //   int n = (*this).size(), m = g.size();
  //   drep(i, n) {
  //     (*this)[i] *= g[0];
  //     rep2(j, 1, min(i+1, m)) (*this)[i] += (*this)[i-j] * g[j];
  //   }
  //   return *this;
  // }
  // F &operator/=(const F &g) {
  //   assert(g[0] != T(0));
  //   T ig0 = g[0].inv();
  //   int n = (*this).size(), m = g.size();
  //   rep(i, n) {
  //     rep2(j, 1, min(i+1, m)) (*this)[i] -= (*this)[i-j] * g[j];
  //     (*this)[i] *= ig0;
  //   }
  //   return *this;
  // }

  // sparse
  F &operator*=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    if (d == 0) g.erase(g.begin());
    else c = 0;
    drep(i, n) {
      (*this)[i] *= c;
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] += (*this)[i-j] * b;
      }
    }
    return *this;
  }
  F &operator/=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    assert(d == 0 && c != T(0));
    T ic = c.inv();
    g.erase(g.begin());
    rep(i, n) {
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] -= (*this)[i-j] * b;
      }
      (*this)[i] *= ic;
    }
    return *this;
  }

  // multiply and divide (1 + cz^d)
  void multiply(const int d, const T c) { 
    int n = (*this).size();
    if (c == T(1)) drep(i, n-d) (*this)[i+d] += (*this)[i];
    else if (c == T(-1)) drep(i, n-d) (*this)[i+d] -= (*this)[i];
    else drep(i, n-d) (*this)[i+d] += (*this)[i] * c;
  }
  void divide(const int d, const T c) {
    int n = (*this).size();
    if (c == T(1)) rep(i, n-d) (*this)[i+d] -= (*this)[i];
    else if (c == T(-1)) rep(i, n-d) (*this)[i+d] += (*this)[i];
    else rep(i, n-d) (*this)[i+d] -= (*this)[i] * c;
  }

  T eval(const T &a) const {
    T x(1), res(0);
    for (auto e : *this) res += e * x, x *= a;
    return res;
  }

  F operator*(const T &g) const { return F(*this) *= g; }
  F operator/(const T &g) const { return F(*this) /= g; }
  F operator+(const F &g) const { return F(*this) += g; }
  F operator-(const F &g) const { return F(*this) -= g; }
  F operator<<(const int d) const { return F(*this) <<= d; }
  F operator>>(const int d) const { return F(*this) >>= d; }
  F operator*(const F &g) const { return F(*this) *= g; }
  F operator/(const F &g) const { return F(*this) /= g; }
  F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
  F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};

using fps = FormalPowerSeries<mint>;



//opt氏
/*#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) rep2(i, 0, n)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)*/

#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) rep2(i, 0, n)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)

template<class T>
struct FormalPowerSeries : vector<T> {
  using vector<T>::vector;
  using vector<T>::operator=;
  using F = FormalPowerSeries;

  F operator-() const {
    F res(*this);
    for (auto &e : res) e = -e;
    return res;
  }
  F &operator*=(const T &g) {
    for (auto &e : *this) e *= g;
    return *this;
  }
  F &operator/=(const T &g) {
    assert(g != T(0));
    *this *= g.inv();
    return *this;
  }
  F &operator+=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] += g[i];
    return *this;
  }
  F &operator-=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] -= g[i];
    return *this;
  }
  F &operator<<=(const int d) {
    int n = (*this).size();
    (*this).insert((*this).begin(), d, 0);
    (*this).resize(n);
    return *this;
  }
  F &operator>>=(const int d) {
    int n = (*this).size();
    (*this).erase((*this).begin(), (*this).begin() + min(n, d));
    (*this).resize(n);
    return *this;
  }
  F inv(int d = -1) const {
    int n = (*this).size();
    assert(n != 0 && (*this)[0] != 0);
    if (d == -1) d = n;
    assert(d > 0);
    F res{(*this)[0].inv()};
    while (res.size() < d) {
      int m = size(res);
      F f(begin(*this), begin(*this) + min(n, 2*m));
      F r(res);
      f.resize(2*m), internal::butterfly(f);
      r.resize(2*m), internal::butterfly(r);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      f.erase(f.begin(), f.begin() + m);
      f.resize(2*m), internal::butterfly(f);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      T iz = T(2*m).inv(); iz *= -iz;
      rep(i, m) f[i] *= iz;
      res.insert(res.end(), f.begin(), f.begin() + m);
    }
    return {res.begin(), res.begin() + d};
  }

  // // fast: FMT-friendly modulus only
   F &operator*=(const F &g) {
     int n = (*this).size();
     *this = convolution(*this, g);
     (*this).resize(n);
     return *this;
   }
   F &operator/=(const F &g) {
     int n = (*this).size();
     *this = convolution(*this, g.inv(n));
     (*this).resize(n);
     return *this;
   }

  // // naive
  /*
   F &operator*=(const F &g) {
     int n = (*this).size(), m = g.size();
     drep(i, n) {
       (*this)[i] *= g[0];
       rep2(j, 1, min(i+1, m)) (*this)[i] += (*this)[i-j] * g[j];
     }
     return *this;
   }
   F &operator/=(const F &g) {
     assert(g[0] != T(0));
     T ig0 = g[0].inv();
     int n = (*this).size(), m = g.size();
     rep(i, n) {
       rep2(j, 1, min(i+1, m)) (*this)[i] -= (*this)[i-j] * g[j];
       (*this)[i] *= ig0;
     }
     return *this;
   }
   */

  // sparse
  F &operator*=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    if (d == 0) g.erase(g.begin());
    else c = 0;
    drep(i, n) {
      (*this)[i] *= c;
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] += (*this)[i-j] * b;
      }
    }
    return *this;
  }
  F &operator/=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    assert(d == 0 && c != T(0));
    T ic = c.inv();
    g.erase(g.begin());
    rep(i, n) {
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] -= (*this)[i-j] * b;
      }
      (*this)[i] *= ic;
    }
    return *this;
  }


  // multiply and divide (1 + cz^d)
  void multiply(const int d, const T c) { 
    int n = (*this).size();
    if (c == T(1)) drep(i, n-d) (*this)[i+d] += (*this)[i];
    else if (c == T(-1)) drep(i, n-d) (*this)[i+d] -= (*this)[i];
    else drep(i, n-d) (*this)[i+d] += (*this)[i] * c;
  }
  void divide(const int d, const T c) {
    int n = (*this).size();
    if (c == T(1)) rep(i, n-d) (*this)[i+d] -= (*this)[i];
    else if (c == T(-1)) rep(i, n-d) (*this)[i+d] += (*this)[i];
    else rep(i, n-d) (*this)[i+d] -= (*this)[i] * c;
  }

  T eval(const T &a) const {
    T x(1), res(0);
    for (auto e : *this) res += e * x, x *= a;
    return res;
  }

  F operator*(const T &g) const { return F(*this) *= g; }
  F operator/(const T &g) const { return F(*this) /= g; }
  F operator+(const F &g) const { return F(*this) += g; }
  F operator-(const F &g) const { return F(*this) -= g; }
  F operator<<(const int d) const { return F(*this) <<= d; }
  F operator>>(const int d) const { return F(*this) >>= d; }
  F operator*(const F &g) const { return F(*this) *= g; }
  F operator/(const F &g) const { return F(*this) /= g; }
  F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
  F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};

using mint = modint998244353;
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>;

//概要
/*
FormalPowerSeries構造体は、fのz^0からz^nまでの係数のみ保持するため、
演算によってvectorの大きさは変わらない

F operator-() :-fを返す
F &operator+=(const F &g) : fをf+gに更新
F &operator-=(const F &g) : fをf-gに更新
F &operator*=(const T &c) : fをcfに更新(cは定数)
F &operator/=(const T &c) : fをf/cに更新(cは定数)
F &operator<<=(const int d) : fをfz^dに更新
F &operator>>=(const int d) : fをf/z^dに更新
(計算量はO(N))

F inv(int d = -1) : 1/fを返す(d-1次の項で打ち切る。デフォルトはn次の項で打ち切る)
(計算量はO(NlogN))
atcoder::convolutionを使っているため、modがNTT-friendlyでないといけない

F &operator*=(const F &g) : fをfgに更新
F &operator/=(const F &g) : fをf/gに更新
fast版とnaive版の2種類ある(上のコードでは共にコメントアウトされている)
fast版はmodがNTT-friendlyでないと使えない
(計算量はfast版がO((N+M)log(N+M)), naive版がO(NM))
これを使うだけではmodを取らずに純粋に多項式の割り算をすることはできない(.inv()をとるので)

--sparseな乗除算--
F &operator*=(vector<pair<int, T>> g) : fをfgに更新
F &operator/=(vector<pair<int, T>> g) : fをf/gに更新
sparseな計算をする場合、gは{{0,1},{4,1},{5,-1}}などのような形({{次数,係数(≠0)}})で与える
(計算量はO(NK),但しKはgの非ゼロ項の数)

void multiply(const int d, const T c) : fをf(1+cz^d)に更新
void divide(const int d, const T c) : fをf/(1+cz^d)に更新
sparceな乗除算の特別な場合
(計算量はO(N))


T eval(const T &a) : fにz=aを代入した時の値を返す
(計算量はO(N))

F operator+(const F &g) 等: F &operator+=(const F &g) などの結果を返す

<使い方>
(<atcoder/all>とusing namespace atcoder;が必要)
using mint = modint998244353;
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>;

fps f = {3,1,4,2,5}; //f=3+z+4z^2+z^3+5z^4とする(次数の小さい方から入れる)
fps g = {2,7,1}; 
fps h = f * g; //hの4次の項までをvectorで返す(これはfの次数に等しい 十分桁数計算したいなら
最初からvector fのsizeを大きくとっておき、左から演算するようにする)

fps h = (f - (f<<2) + fps{2}) / g;
 f<<2は上例では{0,0,4,2,5}を表す(z^2倍する)
 f>>2は上例では{4,2,5,0,0}を表す(z^-2倍のイメージ)
 定数項のfps(fps{2})などは演算の右側に書く(左側に書くとvectorのサイズが小さくなってしまう)、もしくは
 定数項のvectorをn+1項にまで広げて書く (fps const1(n+1,0) const1[0]=1 など)

fとg=1-zに対してf/gを計算する場合、
sfps g={{0,1},{1,-1}}としてもよい (これは非ゼロ項の(次数,係数)の組を並べたvector 特にsparseな場合)
f.divide(1,-1);でも可

<注意>
template TのTにはatcoder libraryのmodintを渡すことを想定している
NTT-friendlyなmodとは、p=u*2^e+1 (eはある程度大きい整数)と表される素数modのこと。
(ここで2^e+1項までのvectorでの演算が高速にできることになる)
ex) 998244353=119*2^23+1
ex) 1000000007は1を引くと4の倍数でないことからnot NTT-friendlyといえる

*/

//ex) 多項式を受け取ってその積を返すコード
int main(){
	int n,m;
	cin>>n>>m;
	fps a(n+m,0);//vectorと同じような初期化ができる
	fps b(n+m,0);
	rep(i,n){
		int y; //mintの変数に直接cinはできない
		cin>>y;
		a[i]=y;
	}
	rep(i,m){
		int y;
		cin>>y;
		b[i]=y;
	}
	fps c = a*b;
	rep(i,n+m-1){
		cout<<c[i].val()<<" "; //mintの値の配列なので.val()で取り出す
	}
	cout<<endl;
	return 0;
}

