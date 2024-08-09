//木DP
/*
dp[ v ] := 頂点 v を根とする部分木についての何かしらの値
を考えるとうまくいくことが多い

手順
DFS の帰りがけ順
*/

//実装例(根付き木に対する実装 必要なパラメータや関数を問題によって加える)
//入力値は(childを表すvvi, vi(n,-1), 根の番号)

void dfs(vvi& child, vi& dp, int v){
	if(child[v].size()==0){
		/*
		葉に対するdpの値を計算
		*/
	return;
	}

	for(auto to:child[v]){
		dfs(child,dp,to);
	}
	/*
	子の全てのdpの値を用いてdp[v]を計算する
	*/
	return;
}


//全方位木DP
/*
dp[ v ][ i ] := 頂点 v を根とする部分木について、「v から出る i 番目の有向辺に対応する部分木」に関する何らかの値 
  を考えるとうまくいくことが多い

手順
1.DFS: ある一つの頂点 v を根として、普通の木DPを行う(O(N))
2.BFS: v から頂点を一つずつズラしていき、必要な dp の計算を行う(vから出る辺でない辺に対応する)
		ここで、次数がdの頂点vについて、vに入る有向辺に対する計算はd*(d-1)だけ必要(つまり一つの
		頂点あたりO(d^2))に思われるが、頂点vに対する左右からの累積mergeをあらかじめ求めておくことで、
		一つの部分木を求めるのにO(1)で済み、よって一つの頂点あたりO(d)でよくなる。
		→頂点の次数の総和は辺の数Eの2倍なので、結局O(N)で計算できる

		ここで、部分木のdpの値を累積mergeするためには、モノイド(結合則と単位元について成立)である必要がある
		2つの部分木のdpの値から、それを統合した部分のdpをうまく求める必要がある(mergeとadd_root)
*/


//実装例(struct) 下は、全ての頂点について、それを根とした時の最も遠い頂点までの距離を求めるコード

/* Rerooting: 全方位木 DP
    問題ごとに以下を書き換える
    - 型DPと単位元
    - 型DPに対する二項演算 merge
    - まとめたDPを用いて新たな部分木のDPを計算する add_root
    計算量: O(N)
*/
struct Rerooting {

	//structの中にstructを書くと、外側のstructのメンバ関数として、内側のstructを使える。
		//よって、外側の構造体のオブジェクトを介して、内側の構造体のオブジェクトにアクセスできる。

    /* start 問題ごとに書き換え */
	/*コンストラクタは、下のstruct DP の中でDP(){}　と書く(struct名と同じ名前を書く)ことで、
	オブジェクトが作られる時に初期化を行う。ここでは、dpメンバ関数をdp_で初期化している
	コンストラクタが引数をとる時は、オブジェクトの宣言の時に引数に対応する値を渡す必要がある
	*/
    struct DP {  // DP の型
        long long dp;
        DP(long long dp_) : dp(dp_) {} //dpメンバ関数をdp_で初期化 つまりll dp = dp_(外からの引数) とする。
    };

    const DP identity = DP(-1);  // 単位元(末端の値は add_root(identity) になるので注意)
	//size0の部分木とmergeするような時に整合性が取れるように設定する

    function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
        return DP(max(dp_cum.dp, d.dp));
    };
	// 型DPに対する二項演算 merge
	//2つのDPをマージする関数をmergeとして定義している。ここでは、dp_cumとdを比較して、大きい方を返すようにしている。
	// function<返り値の型(引数の型1, 引数の型2)> 関数名 = [](引数の型1, 引数名1, 引数の型2, 引数名2) -> 返り値の型 {return 返り値};

    function<DP(DP)> add_root = [](DP d) -> DP {
        return DP(d.dp + 1);
    };
	//まとめたDPを用いて新たな部分木のDPを計算する add_root
	//例の場合では、各部分木のdpのmax(merge)に1を足して自身のdpの値としている dはmergeした後のdpの値

    /* end 問題ごとに書き換え */

    // グラフの定義
    struct Edge {
        int to;
    };
    using Graph = vector<vector<Edge>>;
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
        dfs(0);            // 普通に木DP
        bfs(0, identity);  // 残りの部分木に対応するDPを計算
    }
    DP dfs(int v, int p = -1) {  // 頂点v, 親p
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
int main() {
    int N;
    cin >> N;
    Rerooting reroot(N); 
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        reroot.add_edge(u, v);
        reroot.add_edge(v, u);
    }
    reroot.build();
    for (int i = 0; i < N; i++) {
        cout << "頂点" << i + 1 << ": " << reroot.ans[i].dp << endl;
    }
}
//Retooting reroot(N): サイズNの木を作る準備
//reroot.add_edge(u,v): 辺(u,v)を追加
//reroot.build(): DPの実施(普通の木DPと他の部分木に対するDPの計算)
//reroot.ans[i]: 頂点iの答え

//ex) https://atcoder.jp/contests/abc160/submissions/11405183