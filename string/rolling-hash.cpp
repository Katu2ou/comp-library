//Rolling Hash
/*
高速に文字列検索を行うための方法(O(n+m))
任意のa,b(a<=b)について、hash([a,b])をO(1)で求められる(ハッシュの作り方より[0,b],[0,a-1]から[a,b]が)

m文字の文字列Aに対し、互いに素な基数(base = b)とmod p を取って、
hash(A) = (A_0*b^(m-1) + A_1*b^(m-2) + ... + A_(m-1)*b^0) mod p
とする。(ここでA_iは、Aのi文字目に対応したある値とする 例えばA_i-'a'など)

hが十分に大きい時はハッシュ値の衝突はほとんど起こりにくいと考えられる。
→文字列の一致検証がO(n)からO(1)に高速化できる

- pは2^61-1を用いると安全らしい
- 

*/
//実装例
//baseはstruct内で決める
//modはusingに書いてある
class RollingHash {
    static const uint64_t mod = (1ull << 61ull) - 1;
    vector<uint64_t> power;
    const uint64_t base;

    //1以上mod - 1以下のランダムなbaseを生成
    static inline uint64_t generate_base() {
        mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint64_t> rand((uint64_t)1,(uint64_t)mod - 1);
        return rand(engine);
    }

    //足し算
    static inline uint64_t add(uint64_t a, uint64_t b) {
        if((a += b) >= mod) a -= mod;
        return a;
    }

    //掛け算（__uint128_tを使用）
    static inline uint64_t mul(uint64_t a, uint64_t b) {
        __uint128_t c = (__uint128_t) a * b;
        return add(c >> 61,c & mod);
    }

    inline void expand(size_t sz) {
        if(power.size() < sz + 1) {
            int pre_sz = (int)power.size();
            power.resize(sz + 1);
            for(int i = pre_sz - 1;i < sz;i++) {
                power.at(i + 1) = mul(power.at(i),base);
            }
        }
    }

public:

    explicit RollingHash(uint64_t base = generate_base()) : base(base),power{1} {}

    //文字列Sのハッシュを返す
    vector<uint64_t> build(string S) {
        vector<uint64_t> hash(S.size() + 1);
        for (int i = 0; i < S.size(); i++) {
            hash.at(i + 1) = add(mul(hash.at(i),base),S.at(i));
        }
        return hash;
    }

    //hashの[l,r)のハッシュ値を返す
    uint64_t get(vector<uint64_t> &hash,int l,int r) {
        expand(r - l);
        return add(hash.at(r),mod - mul(hash.at(l),power.at(r - l)));
    }

    //ハッシュ値h1と長さh2lenのハッシュ値h2を結合
    uint64_t connect(uint64_t h1, uint64_t h2, size_t h2len) {
        expand(h2len);
        return add(mul(h1, power.at(h2len)), h2);
    }

    //hash1の区間[l1,r1)とhash2の区間[l2,r2)のlcp（最長共通接頭辞）の長さを返す
    int LCP(vector<uint64_t> &hash1,int l1,int r1,vector<uint64_t> &hash2,int l2,int r2) {
        int len = min(r1 - l1,r2 - l2);
        int ok = 0;
        int ng = len + 1;
        int mid;
        while(ng - ok > 1) {
            mid = (ok + ng) / 2;
            if(get(hash1,l1,l1 + mid) == get(hash2,l2,l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

string T,P;
    cin >> T >> P;
    if(T.size() < P.size()) return 0;
    RollingHash rh; 
    vector<uint64_t> t = rh.build(T); //ハッシュテーブルを作って返す
    vector<uint64_t> p = rh.build(P);
    uint64_t cnt = rh.get(p,0,P.size()); //
    for(int i = 0;i < T.size() - P.size() + 1;i++) {
        if(rh.get(t,i,i + P.size()) == cnt) cout << i << endl;
            }


string s="strangeorange";
string t="strongrange";
RollingHash rh; //準備
vector<uint64_t> t = rh.build(T); //ハッシュテーブルを作って返す(rhは他の文字列に対しても繰り返し使う)
rh.get(p,l,r) //ハッシュテーブルpに対して、区間[l,r)のハッシュ値を求めるO(N)
rh.connect(h1,h2,h2len) //ハッシュテーブルh1と、長さh2lenのハッシュテーブルh2を結合する(O(1))
LCP(h1,l1,r1,h2,l2,r2) //ハッシュテーブルh1の元の文字列の部分区間区間[l1,r1)と、ハッシュテーブルh2の元の文字列の部分区間区間[l2.r2)の最長共通接頭辞の長さを求める(O(logn))


////上で書いたものは壊れていそう??



//Nyaan's library


namespace internal1 {
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <int BASE_NUM = 2>
struct Hash : array<u64, BASE_NUM> {
  using array<u64, BASE_NUM>::operator[];
  static constexpr int n = BASE_NUM;

  Hash() : array<u64, BASE_NUM>() {}

  static constexpr u64 md = (1ull << 61) - 1;

  constexpr static Hash set(const i64 &a) {
    Hash res;
    fill(begin(res), end(res), cast(a));
    return res;
  }
  Hash &operator+=(const Hash &r) {
    for (int i = 0; i < n; i++)
      if (((*this)[i] += r[i]) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator+=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++)
      if (((*this)[i] += s) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator-=(const Hash &r) {
    for (int i = 0; i < n; i++)
      if (((*this)[i] += md - r[i]) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator-=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++)
      if (((*this)[i] += md - s) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator*=(const Hash &r) {
    for (int i = 0; i < n; i++) (*this)[i] = modmul((*this)[i], r[i]);
    return *this;
  }
  Hash &operator*=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++) (*this)[i] = modmul((*this)[i], s);
    return *this;
  }

  Hash operator+(const Hash &r) { return Hash(*this) += r; }
  Hash operator+(const i64 &r) { return Hash(*this) += r; }
  Hash operator-(const Hash &r) { return Hash(*this) -= r; }
  Hash operator-(const i64 &r) { return Hash(*this) -= r; }
  Hash operator*(const Hash &r) { return Hash(*this) *= r; }
  Hash operator*(const i64 &r) { return Hash(*this) *= r; }
  Hash operator-() const {
    Hash res;
    for (int i = 0; i < n; i++) res[i] = (*this)[i] == 0 ? 0 : md - (*this)[i];
    return res;
  }
  friend Hash pfma(const Hash &a, const Hash &b, const Hash &c) {
    Hash res;
    for (int i = 0; i < n; i++) res[i] = modfma(a[i], b[i], c[i]);
    return res;
  }
  friend Hash pfma(const Hash &a, const Hash &b, const i64 &c) {
    Hash res;
    u64 s = cast(c);
    for (int i = 0; i < n; i++) res[i] = modfma(a[i], b[i], s);
    return res;
  }

  Hash pow(long long e) {
    Hash a{*this}, res{Hash::set(1)};
    for (; e; a *= a, e >>= 1) {
      if (e & 1) res *= a;
    }
    return res;
  }

  static Hash get_basis() {
    static auto rand_time =
        chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    static mt19937_64 rng(rand_time);
    Hash h;
    for (int i = 0; i < n; i++) {
      while (isPrimitive(h[i] = rng() % (md - 1) + 1) == false)
        ;
    }
    return h;
  }

 private:
  static u64 modpow(u64 a, u64 b) {
    u64 r = 1;
    for (a %= md; b; a = modmul(a, a), b >>= 1) r = modmul(r, a);
    return r;
  }
  static bool isPrimitive(u64 x) {
    for (auto &d : vector<u64>{2, 3, 5, 7, 11, 13, 31, 41, 61, 151, 331, 1321})
      if (modpow(x, (md - 1) / d) <= 1) return false;
    return true;
  }
  static inline constexpr u64 cast(const long long &a) {
    return a < 0 ? a + md : a;
  }
  static inline constexpr u64 modmul(const u64 &a, const u64 &b) { 
    u128 d = u128(a) * b;
    u64 ret = (u64(d) & md) + u64(d >> 61);
    return ret >= md ? ret - md : ret;
  }
  static inline constexpr u64 modfma(const u64 &a, const u64 &b, const u64 &c) {
    u128 d = u128(a) * b + c;
    u64 ret = (d >> 61) + (u64(d) & md);
    return ret >= md ? ret - md : ret;
  }
};

}  // namespace internal


template <typename Str, int BASE_NUM = 2>
struct RollingHash {
  using Hash = internal1::Hash<BASE_NUM>;
  Str data;
  vector<Hash> hs, pw;
  int s;
  inline static Hash basis = Hash::get_basis(); //inlineが必要！！

  RollingHash(const Str &S = Str()) { build(S); }

  void build(const Str &S) {
    data = S;
    s = S.size();
    hs.resize(s + 1);
    pw.resize(s + 1);
    pw[0] = Hash::set(1);
    hs[0] = Hash::set(0);
    for (int i = 1; i <= s; i++) {
      pw[i] = pw[i - 1] * basis;
      hs[i] = pfma(hs[i - 1], basis, S[i - 1]);
    }
  }

  Hash get(int l, int r = -1) const {
    if (r == -1) r = s;
    return pfma(hs[l], -pw[r - l], hs[r]);
  }

  // T の hash を返す
  static Hash get_hash(const Str &T) {
    Hash ret = Hash::set(0);
    for (int i = 0; i < (int)T.size(); i++) ret = pfma(ret, basis, T[i]);
    return ret;
  }

  // a + b の hash を返す
  // 引数 : a, b, b の長さ
  static Hash unite(Hash a, Hash b, long long bsize) {
    return pfma(a, basis.pow(bsize), b);
  }

  int find(Str &T, int lower = 0) const {
    auto ths = get_hash(T);
    for (int i = lower; i <= s - (int)T.size(); i++)
      if (ths == get(i, i + (int)T.size())) return i;
    return -1;
  }

  static int lcp(const RollingHash &a, const RollingHash &b, int al, int bl) {
    int ok = 0, ng = min(a.size() - al, b.size() - bl) + 1;
    while (ok + 1 < ng) {
      int med = (ok + ng) / 2;
      (a.get(al, med + al) == b.get(bl, med + bl) ? ok : ng) = med;
    }
    return ok;
  }

  static int strcmp(const RollingHash &a, const RollingHash &b, int al, int bl,
                    int ar = -1, int br = -1) {
    if (ar == -1) ar = a.size();
    if (br == -1) br = b.size();
    int n = min<int>({lcp(a, b, al, bl), ar - al, br - bl});
    return al + n == ar                      ? bl + n == br ? 0 : -1
           : bl + n == br                    ? 1
           : a.data[al + n] < b.data[bl + n] ? -1
                                             : 1;
  }

  int size() const { return s; }
};

template <typename Str, int BASE_NUM>
typename RollingHash<Str, BASE_NUM>::Hash RollingHash<Str, BASE_NUM>::basis =
    internal1::Hash<BASE_NUM>::get_basis();
using roriha = RollingHash<string, 2>;

// RollingHash<string> rh(S): コンストラクタ。Sを対象としたRollingHashを構築する。
// build(S): Sを対象としたRollingHashを構築する。
// get(l, r): 区間[l, r)のハッシュを返す。 (0-indexed)
// get_hash(T): Tのハッシュ値を返す。
// find(T, lower = 0): Sのlower文字目以降で初めてTが出てくる位置を返す。(存在しない場合は-1を返す。)
// LCP(a, b, al, bl): aのal文字目から始まるsuffixとbのb文字目から始まるsuffixのLCPを返す。
// strcmp(a, b, al, bl, ar=-1, br=-1): a[al, ar)とb[bl, br)の大小を比較する。(返り値はstd::strcmpの仕様に準ずる。)
// size(): Sのサイズを返す。

