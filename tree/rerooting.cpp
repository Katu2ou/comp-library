
//実装例(struct) 下は、全ての頂点について、それを根とした時の最も遠い頂点までの距離を求めるコード

/* Rerooting: 全方位木 DP
    問題ごとに以下を書き換える
    - 型DPと単位元 (計算に必要な情報をDPの中に入れておく 初期値設定も忘れず const DP identity も合わせて設定)
    - identityは合成mergeに対する単位元である
    - 型DPに対する二項演算 merge (DP(~,~,...,~)としてreturn)
    - まとめたDPを用いて新たな部分木のDPを計算する add_root (子を1つになるまでmergeしたDp dから作る)
    計算量: O(N)

    1. Rerooting reroot(n); n頂点の木を作成
    2. reroot.add_edge(a,b); 辺を追加
    3. reroot.build(); 
    4. reroot.ans[i].dp; 頂点iを値とした時の答え
*/


struct Rerooting {
    //ここから書き換える//
    struct DP { 
        long long dp;
        DP(long long dp_) : dp(dp_) {} 
    };
    const DP identity = DP(-1);  
    function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
        return DP(max(dp_cum.dp, d.dp));
    };
    function<DP(DP)> add_root = [](DP d) -> DP {
        return DP(d.dp + 1);
    };
    //ここまで書き換え//
    struct REdge {
        int to;
    };
    using Graph = vector<vector<REdge>>;
    vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
    vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
    Graph G;
    Rerooting(int N) : G(N) {
        dp.resize(N);
        ans.assign(N, identity);
    }
    void add_edge(int a, int b) {
        G[a].push_back({b});
    }
    void build() {
        dfs(0);            
        bfs(0, identity); 
    }
    DP dfs(int v, int p = -1) {  
        DP dp_cum = identity;
        int deg = G[v].size();
        dp[v] = vector<DP>(deg, identity);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dp_cum = merge(dp_cum, dp[v][i]);
        }
        return add_root(dp_cum);
    }
    void bfs(int v, const DP& dp_p, int p = -1) {  // bfs だが、実装が楽なので中身は dfs になっている
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
            if (G[v][i].to == p) dp[v][i] = dp_p;
        }
        vector<DP> dp_l(deg + 1, identity), dp_r(deg + 1, identity);  // 累積merge
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = merge(dp_l[i], dp[v][i]);
        }
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = merge(dp_r[i + 1], dp[v][i]);
        }
        ans[v] = add_root(dp_l[deg]);  // 頂点 v の答え
        for (int i = 0; i < deg; i++) {  // 一つ隣の頂点に対しても同様に計算
            int u = G[v][i].to;
            if (u == p) continue;
            bfs(u, add_root(merge(dp_l[i], dp_r[i + 1])), v);
        }
    }
};