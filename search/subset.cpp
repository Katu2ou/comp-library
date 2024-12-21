/*
    - 部分集合走査 (https://noshi91.hatenablog.com/entry/2021/04/01/213231)
        - for(auto t: subsets(s)) で，sのbit列を集合と解釈した時の部分集合を走査する
            - s自身や0も値として取るので注意
            - u64を返している
        - sに対して，tをsの部分集合として， s -> s-1 -> s&=t とすることで
            部分集合を列挙することができ，s-1==-1(s=0)になったら終了する
            0 <= i < 2^nを満たす各iに対して列挙を行うとき，計算量はO(3^n)
*/

struct subsets {
  using u64 = std::uint64_t;

  u64 s;

  subsets(u64 s_) : s(s_) {}

  struct itr {
    u64 s;
    u64 t;

    bool operator!=(std::monostate) { return t != -1; }
    void operator++() { t -= 1; }
    u64 operator*() { return t &= s; }
  };

  itr begin() { return {s, s}; }
  std::monostate end() { return {}; }
};