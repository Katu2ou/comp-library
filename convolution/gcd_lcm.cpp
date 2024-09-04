//https://aprilganmo.hatenablog.com/entry/2020/07/24/190816

/*
<ゼータ変換>
    A -> B_i = \sum(A_j | i|j)
    (約数集合での上位集合に対するゼータ変換 : iの倍数全体に対する総和を保存する)

    - 倍数変換(自身の上位集合に対する)/約数変換(自身の下位集合に対する)とも言ったりする

    - メビウス変換はこの逆

     - 長さnの配列a,bがあったときに，これらをゼータ変換してA,Bを得た時，{A_iB_i}_iを
    メビウス変換すると配列CがC_i = \sum_{gcd(j,k)=i} A_j B_k として得られる
    (gcd畳み込み)

<実装>
    (1) f(i) (1<=i<=n)が与えられた時にg(j)(1<=j<=n)を求める
    (2) f(i) (i|nまたはn|i)が与えられた時にg(n)を求める
    ((1)がO(nloglogn), (2)がO((nの約数の個数)^2))

    - A,Bを0-indexedとして変換を行うので，A[0]=0としておく．(Aの中身はA[1]から書き始める)
*/

//前準備(エラトステネスの篩)
vector<int> prime_enumerate(int N) {
  vector<bool> sieve(N / 3 + 1, 1);
  for (int p = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn; p += d = 6 - d, i++) {
    if (!sieve[i]) continue;
    for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
             qe = sieve.size();
         q < qe; q += r = s - r)
      sieve[q] = 0;
  }
  vector<int> ret{2, 3};
  for (int p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
    if (sieve[i]) ret.push_back(p);
  while (!ret.empty() && ret.back() > N) ret.pop_back();
  return ret;
}


struct divisor_transform {
  template <typename T>
  static void zeta_transform(vector<T> &a) {
    int N = a.size() - 1;
    auto sieve = prime_enumerate(N);
    for (auto &p : sieve)
      for (int k = 1; k * p <= N; ++k) a[k * p] += a[k];
  }
  template <typename T>
  static void mobius_transform(vector<T> &a) {
    int N = a.size() - 1;
    auto sieve = prime_enumerate(N);
    for (auto &p : sieve)
      for (int k = N / p; k > 0; --k) a[k * p] -= a[k];
  }

  template <typename I, typename T>
  static void zeta_transform(map<I, T> &a) {
    for (auto p = rbegin(a); p != rend(a); p++)
      for (auto &x : a) {
        if (p->first == x.first) break;
        if (p->first % x.first == 0) p->second += x.second;
      }
  }
  template <typename I, typename T>
  static void mobius_transform(map<I, T> &a) {
    for (auto &x : a) {
      for (auto p = rbegin(a); p != rend(a); p++) {
        if (x.first == p->first) break;
        if (p->first % x.first == 0) p->second -= x.second;
      }
    }
  }
};

struct multiple_transform {
  template <typename T>
  static void zeta_transform(vector<T> &a) {
    int N = a.size() - 1;
    auto sieve = prime_enumerate(N);
    for (auto &p : sieve)
      for (int k = N / p; k > 0; --k) a[k] += a[k * p];
  }
  template <typename T>
  static void mobius_transform(vector<T> &a) {
    int N = a.size() - 1;
    auto sieve = prime_enumerate(N);
    for (auto &p : sieve)
      for (int k = 1; k * p <= N; ++k) a[k] -= a[k * p];
  }

  template <typename I, typename T>
  static void zeta_transform(map<I, T> &a) {
    for (auto &x : a)
      for (auto p = rbegin(a); p->first != x.first; p++)
        if (p->first % x.first == 0) x.second += p->second;
  }
  template <typename I, typename T>
  static void mobius_transform(map<I, T> &a) {
    for (auto p1 = rbegin(a); p1 != rend(a); p1++)
      for (auto p2 = rbegin(a); p2 != p1; p2++)
        if (p2->first % p1->first == 0) p1->second -= p2->second;
  }
};

template <typename mint>
vector<mint> gcd_convolution(const vector<mint>& a, const vector<mint>& b) {
  assert(a.size() == b.size());
  auto s = a, t = b;
  multiple_transform::zeta_transform(s);
  multiple_transform::zeta_transform(t);
  for (int i = 0; i < (int)a.size(); i++) s[i] *= t[i];
  multiple_transform::mobius_transform(s);
  return s;
}

template <typename mint>
vector<mint> lcm_convolution(const vector<mint>& a, const vector<mint>& b) {
  assert(a.size() == b.size());
  auto s = a, t = b;
  divisor_transform::zeta_transform(s);
  divisor_transform::zeta_transform(t);
  for (int i = 0; i < (int)a.size(); i++) s[i] *= t[i];
  divisor_transform::mobius_transform(s);
  return s;
}


