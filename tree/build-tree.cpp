//目次
/*
木の作成
根付き木の作成
木の直径
*/

//入力1,2,...,nに対して、木のindexは0-indexで管理!!
//これらはmain関数の外に書いて、あとで中で呼び出す

//辺の情報から普通の木Gをvector vector int で作る
vector<vector<int>> tree_in(int N){
	vector<vector<int>> G(N);
	for(int i=0;i<N-1;i++){
		int a;int b;
		cin>>a>>b; 
		a--,b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	return G;
}
// auto G=tree_in(N); などとして受け取る(Gはvvi)

//木の直径
int tree_diameter(vvi &G){
	int n=G.size();
	vi seen(n,0);
	queue<int> q;
	q.push(0);
	seen[0]=1;
	int lst=0;
	while(!q.empty()){
		int a=q.front();
		lst=a;
		q.pop();
		for(auto x:G[a]){
			if(seen[x]==0){
				q.push(x);
				seen[x]=1;
			}
		}
	}
	q.push(a);
	int d=0;
	vi dp(n,inf);
	dp[a]=0;
	while(!q.empty()){
		int a=q.front();
		q.pop();
		for(auto x:G[a]){
			if(dp[x]>dp[a]+1){
				dp[x]=dp[a]+1;
				chmax(d,dp[x]);
				q.push(x);
			}
		}
	}
	return d;
}



/*木Gを作った時にある頂点rootを根としてorder, 親, 子供集合 深さのvectorを返す
 (G, 頂点u) --> (order(親が確定していった順番),pare,child,depth) (vi*4) ただしvvi型 (v[0]がorderに対応など)
	- 根のparentは-2,深さは0となる。
	- orderは親が決まった順番だが、DFS木ではない

	(Graph / 全体の根)
 */

pair<vvi,vvi> tree_info(vvi &G, int root){
	int n=G.size();
	vi order={root},pare(n,-1),depth(n);
	vvi child(n);
	pare[root]=-2;
	for(int i=0;i<n;i++){
		int a=order[i];
		for(auto x:G[a]){
			if(pare[x]==-1){
				pare[x]=a;
				depth[x]=depth[a]+1;
				order.push_back(x);
			}
		}
	}
	for(int i=0;i<n;i++){
		if(pare[i]!=-2) child[pare[i]].push_back(i);
	}
	vector<vector<int>> info(3);
	info[0]=order;
	info[1]=pare;
	info[2]=depth;
	return {info,child};
}

//上において辺が情報を持っている時の実装



//DFS木の作成
/*
	- orderは親が確定していった順番であり、これはDFS木をなす。DFS木は、
	任意の頂点を親とする部分根付き木を構成する頂点のindexが連続になるという性質から、
	部分木に関する操作を区間の操作として扱えるようになり、セグ木を使ったアルゴリズム
	などに応用できる。
	(子の頂点集合vector/DFS木のindexを入れる(つまりi番目にはDFS木で頂点iである頂点の元の頂点番号が入る)/
	pos(その頂点の子孫(自分を含む)のDFSが終わった時のindex)/今見ている頂点番号(最初は根))/今のindex
	を入れる。order,posははじめ空のviとする。indexははじめ0とする。
	これによって、元の頂点番号uに対して、頂点uを根とする部分木のDFS木での頂点集合は(order[pos[u]],pos[u])となる。

	(取得したchild / vi{} / vi{} / 全体の根 / 0 )
*/

void tree_DFS(vvi& child, vi& order, vi& pos, int root, int ind){
	order.pb(root);
	ind++;
	for(auto x:G[root]){
		tree_DFS(G,order,pos,x);
	}
	pos[root]=ind;
	return;
}

//元の頂点番号iに対してDFS木での頂点番号v[i]を対応させる配列(i->v[i] / v[i]->i に該当するものは上のorder)
vi comp(vi& order){
	int n=order.size();
	vi v(n);
	for(int i=0;i<n;i++){
		v[order[i]]=i;
	}
	return v;
}

//これらを用いると、元のグラフからDFS木を作り、元のグラフの問題に対応したDFS木での問題に帰着できる


//Euler Tour
/*
頂点のDFSでの訪問順をvectorに持つことで、木を直線として扱える

vectorのETは最初空で、最終的にEulerTour順の頂点番号が入る
(子供のvector/ETのvector(初期は空)/今見ている頂点番号)
*/
//一番基本的なEulerTour(順番だけを取得) (取得したchild列 / vi{} / 全体の根)
void EulerTour(vvi& child, vi& ET, int v){
	ET.pb(v);
	for(auto to:child[v]){
		EulerTour(child,ET,to);
		ET.pb(v);
	}
}

	//LCA(Lowest Common Ancestor)
	//Euler Tour + Range Minimum Queryなどで解ける

	//(i番目に通りかかる頂点の(深さ,頂点番号)と、頂点がTour上に初めて現れるindexを記録 Tour上から完全に消えるindexも記録することが多い) ETとfirst_appearを得る。
	//(取得したchild, vpii{}, !!!vi(n,-1)!!!, 全体の根, 0)
	void EulerTour(vvi& child, vpii& ET, vi& first_appear, int root, int depth){
		int m=ET.size();
		ET.pb(mp(depth,root)); //ETに深さと頂点番号を記録
		if(first_appear[root]==-1) first_appear[root]=m;
		for(auto to:child[root]){
			EulerTour(child,ET,first_appear,to,depth+1);
			ET.pb(mp(depth,root));
			index++;
		}
	return;
	}

	//Tour上から最後に消えるindexも記録({-1,-1}で初期化 最後に消えるindexとは、要素がaであるindexの最大値のこと)
	void EulerTour(vvi& child, vpii& ET, vpii app, int root, int depth){
		int m=ET.size();
		ET.pb(mp(depth,root));
		if(app[root].fi==-1) app[root].fi=m;
		for(auto to:child[root]){
			EulerTour(child,ET,first_appear,to,depth+1);
			ET.pb(mp(depth,root));
			index++;
		}
	app[root].se=m;
	return;
	}


	/*上の後、頂点a,bのLCAは次のようにして求められる。
		- 各々がeuler_tour上で初めて現れるindex:(pa,pb)をとり、pa<pbと仮定する(これはfirst appear)
		- euler_tour上で、区間[pa,pb]内から、depthが最小となる頂点を取得すると、そいつがLCA
	これは、区間最小を求めれば良いので、セグ木やsparse tableなどで解ける(特にsparse tableはクエリがO(1)
	でできるので早い 数値が変わる場合はセグ木で)

	ここで、任意の二点a,b間の距離は、a,bのLCAをcとすると、d(a,root)+d(b,root)-2d(c,root)で求められる。
	また、n点のLCAは、euler_tour順において最初と最後に出てくる2頂点のLCAと一致する

	他に詳しくは(https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7)を参照
	*/


//入出を管理するEuler-Tour(Gと根のみでOK Gは普通に双方向に辺を張る無向グラフ)
//in[i] -> p[i]
//out[i] -> p[i+N]
std::vector<int> Euler_Tour(std::vector<std::vector<int>> &G,int root){
	std::stack<int> s;
	int n=G.size();
	std::vector<int> p(n*2),seen(n);
	s.push(root);
	seen[root]=1;
	for(int i=0;i<2*n;i++){
		int a=s.top();
		p[a]=i;
		s.pop();
		if(a<n){
			s.push(a+n);
			for(auto x:G[a]){
				if(seen[x]==0){
					s.push(x);
					seen[x]=1;
				}
			}
		}
	}
	return p;
}

//////////////////////////////////////////////////////////




//HL分解(Heavy-Light Decomposition)
/*
高さの低い木に元の木を圧縮することで、値の変更に対して強くする

<方法>
1.まず、根付き木に対して、それぞれの頂点を根とする部分木のサイズをメモする(これは木DPやオイラーツアーなどでできる)
2.各頂点について、その頂点の子のうちそれを根とする部分木のサイズが大きいものへの辺をHeavyな辺とする(最大が複数ある時は
どれを選んでも良い) このとき、Heavyな辺だけからなるパスは列になる
3.これによって、列ごとに見ると、深さが高々O(logN)の、ノードが列を表す木に分解できる
*/

/*各頂点の直径?
std::vector<int> tree_diameter_path(std::vector<std::vector<int>> &G){
	int n=G.size();
	auto r=(tree_order_pare_depth(G,0))[0][n-1];
	std::vector<int> order,pare,depth,ans;
	tie(order,pare,depth)=tree_order_pare_depth(G,r);
	int ind=order[n-1];
	while(ind!=-2){
		ans.push_back(ind);
		ind=pare[ind];
	}
	return ans;
}
*/




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