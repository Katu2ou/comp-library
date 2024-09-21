/*
Lazy Segment Tree
S: モノイド
f: S*S -> S 、Fはfの集合であり、
	f,g \in F -> g*f \in F
	id \in F (st: e*f = f*e = f)
	f(x*y) = f(x)*f(y)
を満たすもの。

遅延セグ木の作成時には、
<セグ木の元となるものの型T(Sの型) / Sの演算 / Sの単位元 / 関数の型(関数自身をどの形で表すか) / 
	f,xからf(x)を返す関数 / f,gからg*f(f*g?) を返す関数 / 関数の単位元>
を入力とする。
*/

//モノイドの型として構造体を渡す例 (abc322F)

#include <iostream>
#include <string>
using namespace std;

#include "atcoder/lazysegtree.hpp"

#define rep(i, n) for (int i = 0; i < (n); i++)

struct Data {
  int mx[2], l[2], r[2], len;

  Data() {
    rep(t, 2) mx[t] = l[t] = r[t] = 0;
    len = 0;
  }
  Data(char c) {
    rep(t, 2) mx[t] = l[t] = r[t] = (c == '0' + t);
    len = 1;
  }

  Data flip() const {
    Data res = *this;
    swap(res.mx[0], res.mx[1]);
    swap(res.l[0], res.l[1]);
    swap(res.r[0], res.r[1]);
    return res;
  }

  static Data merge(const Data& l, const Data& r) { //二つのDataに対して演算
    Data res;
    rep(t, 2) {
      res.l[t] = l.l[t] + (l.l[t] == l.len ? r.l[t] : 0);  //resは、遅延セグ木の上の方の元の場合は、幅が2冪(>1)の状態を持つ
      res.r[t] = r.r[t] + (r.r[t] == r.len ? l.r[t] : 0);
      res.mx[t] = max({l.mx[t], r.mx[t], l.r[t] + r.l[t]}); //二つを合成する時、maxの更新は二つの間で増える部分でしか起こらない
    }
    res.len = l.len + r.len;
    return res;
  }
}; //ここにセミコロンを忘れない

Data f(Data a, Data b) { return Data::merge(a, b); } //モノイドの演算
Data g(int a, Data b) { return a ? b.flip() : b; } //関数の適用
int h(int a, int b) { return a ^ b; } //関数の合成
Data ti() { return Data(); }
int ei() { return 0; }
//セグ木の作成時に入力に書くやつは構造体の外側に書く

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, Q;
  string S;
  cin >> N >> Q >> S;

  vector<Data> init(N);
  rep(i, N) init[i] = Data(S[i]);
  atcoder::lazy_segtree<Data, f, ti, int, g, h, ei> seg(init);

  while (Q--) {
    int c, l, r;
    cin >> c >> l >> r;
    --l;
    if (c == 1) {
      seg.apply(l, r, 1);
    } else {
      auto ans = seg.prod(l, r);
      cout << ans.mx[1] << endl;
    }
  }
}
