//分割統治による静的列の区間積クエリ

/*
次のような問題を考える

 -- Xをモノイドとして、(x0, ... ,xn-1)をXの元の列とする。
 区間[a,b)(b-a>=2)がQ個オフラインで与えられるので、総積xa*...*x(b-1)を求めよ。

*/

//[a,b) \in [L,R)となるすべてのクエリ(a,b)に答える関数dfsの実装
//土台
vector<int> A(N); //列x_0,...,xN-1を表す
vector<int> ANS(Q);

auto calc = [&](int L, int M, int R, vector<T>& query) -> void {
    static vector<int> dp(N + 1);
    //枝刈り(クエリがくる場所だけを前計算するようにする)
    int min_a = M, max_b = M;
    for (auto&& [q, a, b]: query) min_a = min(min_a, a), max_b = max(max_b, b);
    // 累積積の計算
    dp[M] = unit;
    for (int i = M; i > L; --i) dp[i - 1] = op(A[i - 1], dp[i]);
    for (int i = M; i < R; ++i) dp[i + 1] = op(dp[i], A[i]);
    // 答の計算
    for (auto [q, a, b]: query) ANS[q] = op(dp[a], dp[b]);
  };

  auto dfs = [&](auto& dfs, int L, int R, vector<T>& query) -> void {
    if (R - L <= 1) {//ここを問題ごとに書き換える(L+1=Rのときどのような値を返すか)
      for (auto&& [q, a, b]: query) ANS[q] = A[a];
      return;
    }
    int M = (L + R) / 2;
    vector<T> query_L, query_R, other;
    for (auto&& [q, a, b]: query) {
      if (b <= M) query_L.emplace_back(q, a, b);
      if (M <= a) query_R.emplace_back(q, a, b);
      if (a < M && M < b) other.emplace_back(q, a, b);
    }
    calc(L, M, R, other), dfs(dfs, L, M, query_L), dfs(dfs, M, R, query_R);
  };
  dfs(dfs, 0, N, query);
  //これで各クエリの答えが順番にANSに入る

  //演算opの例(minはモノイドをなす)
  int op(int a, int b){
    return min(a,b);
  }

  //型Tの例
  using T = tuple<int,int,int>;
  vector<T> query(Q);
  rep(i,Q){
    int a,b;
    cin>>a>>b;
    query[i] = {i,a,b};
  }
  for(auto [q,a,b]: query){ //tupleの要素はこう取り出すと楽

  }


//セグ木との比較
/*
            モノイド積の回数  空間計算量
分割統治      O(NlogN + Q)    O(N+Q)
セグメント木   O(N + QlogN)    O(N)

分割統治では、あらかじめ「モノイドの元とxiの積」というのをO(NlogN)だけ
計算しておくことで、各queryに対して(対応するMを見つける部分を除くと)1回の
モノイド積の計算で求まる。
セグメント木では、あらかじめ「モノイドの元2つの積」というものをO(N)(~2N)回
計算しておくことで、各queryに対してO(logN)回のモノイド積の計算で求まる。

→ 分割統治は、「モノイドの元2つの積」よりも、「モノイドの元とxiの積」の方が
高速に計算できる場合に有効

枝刈を行った上で、特殊な制約(クエリ[a,b)に対してb-a=Kなど)があると、
モノイド積の計算回数はO(N+Q)となり、セグメント木やDSUよりも高速になる。
この制約とは、b-aの最大値と最小値の比が定数で抑えられている時(b-aが定数
という制約があれば、比は1)

クエリ区間列が単調であればやはりO(N+Q)



*/