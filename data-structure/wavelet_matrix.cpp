//wavelet行列
/*
    - 文字列に対する定数時間のrank(文字列の先頭から位置kまでに文字xがいくつあるか)
    - 文字列の先頭から見て、n個目の文字xの次の位置はどこか
を定数時間で処理することができる。

内部で完備辞書が使われている

//完備辞書
    ビットベクトルBに対して以下の操作を提供する
    - access(B,i) B[i]を返す
    - rank_b(B,i) B[i,i]のbの数を返す
    - select_b(B,i) Bの先頭からi番目のbの位置を返す
//

//Wavelet行列
    整数列Tに対して以下の操作を提供する
    - access(T,i) T[i]を復元する(O(logn))
    - rank_c(T,i) T[1,i]中のcの出現回数を返す(O(logn))
    - select_c(T,i) T中のcのi番目の出現位置を返す(O(logn))
    - quantile(T,s,e,r) T[s,e]の中のr番目に小さい値を返す(O(logn))
    - topk(T,s,e,k) T[s,e]中で出現回数が多い順にその頻度とともにk個返す
    - sum(T,s,e) T[s,e]の合計を返す
    - rangefreq(T,s,e,x,y) T[s,e]中に出現するx<=c<yを満たす値の合計出現数を返す
    - rangelist(T,s,e,x,y) T[s,e]中に出現するx<=c<yを満たす値を頻度とともに列挙する
    - rangemaxk(T,s,e,k) T[s,e]中に出現する値を大きい順にその頻度とともにk個返す
    - rangemink(T,s,e,k) T[s,e]中に出現する値を小さい順にその頻度とともにk個返す
    - prevvalue(T,s,e,x,y) T[s,e]中にx<=c<yを満たす最大のcを返す
    - nextvalue(T,s,e,x,y) T[s,e]中にx<=c<yを満たす最小のcを返す
    - intersect(T,s1,e1,s2,e2) T[s1,e1]とT[s2,e2]の間で共通して出現する値と頻度を返す

/*
    - WaveletMatrix wv(n) 要素数nのWaveletMatrixを構築する(要素は0以上であることを仮定)
    - wv.set(i,x) i番目の要素にxを代入する
    - wv.build() データ構造を構築する(これ以降setは使えない)
    - wv.accsess(k) k番目の要素の値を得る
    - wv.kth_smallest(l,r,k) [l,r)の範囲でk(0-indexed)番目に小さい値を返す
    - wv.kth_largest(l, r, k)　[l, r)の範囲でk(0-indexed)番目に大きい値を返す
    - wv.range_freq(l, r, upper) [l, r)の範囲でupper未満の要素の個数を返す
    - wv.prev_value(l, r, lower) l, rの範囲でupper未満の最後の値を返す
    - wv.next_value(l, r, lower): l, rの範囲でlower以上の最初の値を返す

*/


// 参照:https://miti-7.hatenablog.com/entry/2018/04/28/152259#%E3%81%84%E3%82%8D%E3%81%84%E3%82%8D%E3%81%AA%E4%BA%BA%E3%81%AE%E5%AE%9F%E8%A3%85



//実装例(Nyaan's library)

struct bit_vector {
  using u32 = uint32_t;
  using i64 = int64_t;
  using u64 = uint64_t;

  static constexpr u32 w = 64;
  vector<u64> block;
  vector<u32> count;
  u32 n, zeros;

  inline u32 get(u32 i) const { return u32(block[i / w] >> (i % w)) & 1u; }
  inline void set(u32 i) { block[i / w] |= 1LL << (i % w); }

  bit_vector() {}
  bit_vector(int _n) { init(_n); }
  __attribute__((optimize("O3", "unroll-loops"))) void init(int _n) {
    n = zeros = _n;
    block.resize(n / w + 1, 0);
    count.resize(block.size(), 0);
  }

  //__attribute__((target("popcnt"))) 
  void build() {
    for (u32 i = 1; i < block.size(); ++i)
      count[i] = count[i - 1] + __builtin_popcountll(block[i - 1]);
    zeros = rank0(n);
  }

  inline u32 rank0(u32 i) const { return i - rank1(i); }
  //__attribute__((target("bmi2,popcnt"))) 
  inline u32 rank1(u32 i) const {
    //return count[i / w] +__builtin_popcountll(__builtin_ia32_bzhi_u64(block[i / w], i % w));
    u64 x = block[i / w] & ((1LL << (i % w)) - 1);
    return count[i / w] + __builtin_popcountll(x);
  }
};

template <typename T>
struct WaveletMatrix {
  using u32 = uint32_t;
  using i64 = int64_t;
  using u64 = uint64_t;

  int n, lg;
  vector<T> a;
  vector<bit_vector> bv;

  WaveletMatrix(u32 _n) : n(max<u32>(_n, 1)), a(n) {}
  WaveletMatrix(const vector<T>& _a) : n(_a.size()), a(_a) { build(); }

  __attribute__((optimize("O3"))) void build() {
    lg = __lg(max<T>(*max_element(begin(a), end(a)), 1)) + 1;
    bv.assign(lg, n);
    vector<T> cur = a, nxt(n);
    for (int h = lg - 1; h >= 0; --h) {
      for (int i = 0; i < n; ++i)
        if ((cur[i] >> h) & 1) bv[h].set(i);
      bv[h].build();
      array<decltype(begin(nxt)), 2> it{begin(nxt), begin(nxt) + bv[h].zeros};
      for (int i = 0; i < n; ++i) *it[bv[h].get(i)]++ = cur[i];
      swap(cur, nxt);
    }
    return;
  }

  void set(u32 i, const T& x) { 
    assert(x >= 0);
    a[i] = x; 
  }

  inline pair<u32, u32> succ0(int l, int r, int h) const {
    return make_pair(bv[h].rank0(l), bv[h].rank0(r));
  }

  inline pair<u32, u32> succ1(int l, int r, int h) const {
    u32 l0 = bv[h].rank0(l);
    u32 r0 = bv[h].rank0(r);
    u32 zeros = bv[h].zeros;
    return make_pair(l + zeros - l0, r + zeros - r0);
  }

  // return a[k]
  T access(u32 k) const {
    T ret = 0;
    for (int h = lg - 1; h >= 0; --h) {
      u32 f = bv[h].get(k);
      ret |= f ? T(1) << h : 0;
      k = f ? bv[h].rank1(k) + bv[h].zeros : bv[h].rank0(k);
    }
    return ret;
  }

  // k-th (0-indexed) smallest number in a[l, r)
  T kth_smallest(u32 l, u32 r, u32 k) const {
    T res = 0;
    for (int h = lg - 1; h >= 0; --h) {
      u32 l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (k < r0 - l0)
        l = l0, r = r0;
      else {
        k -= r0 - l0;
        res |= (T)1 << h;
        l += bv[h].zeros - l0;
        r += bv[h].zeros - r0;
      }
    }
    return res;
  }

  // k-th (0-indexed) largest number in a[l, r)
  T kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }

  // count i s.t. (l <= i < r) && (v[i] < upper)
  int range_freq(int l, int r, T upper) {
    if (upper >= (T(1) << lg)) return r - l;
    int ret = 0;
    for (int h = lg - 1; h >= 0; --h) {
      bool f = (upper >> h) & 1;
      u32 l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (f) {
        ret += r0 - l0;
        l += bv[h].zeros - l0;
        r += bv[h].zeros - r0;
      } else {
        l = l0;
        r = r0;
      }
    }
    return ret;
  }

  int range_freq(int l, int r, T lower, T upper) {
    return range_freq(l, r, upper) - range_freq(l, r, lower);
  }

  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  T prev_value(int l, int r, T upper) {
    int cnt = range_freq(l, r, upper);
    return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
  }

  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  T next_value(int l, int r, T lower) {
    int cnt = range_freq(l, r, lower);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }
};


