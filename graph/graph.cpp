//目次
/*
01bfs
最短パスの個数
閉路検出(有向辺/無向辺)
DSU(UnionFind)
強連結成分分解
ベルマンフォード法
ワーシャルフロイド法
経路復元
最小全域木
2部グラフ判定と彩色
関節点
*/

//Edgeの例
struct Edge{
    int from, to;
    ll cost;
    int index;
    bool operator<(const Edge& o) const{
        //return cost<o.cost; 
    }
}


//01bfs
/*
全ての辺の長さが0or1であるような(有向)グラフが与えられた時、このグラフの頂点Sから各頂点への最短距離を求めるアルゴリズム。
dijkstra法がO(ElogV)であるのに対し、01bfsはdequeがpriority_queueの働きをしてO(E)で解ける。

1. まず空のdequeを用意する
2. 最初の(最短)距離を、d[S]=0,d[otherwise]=inf とする
3. dequeにSのみを入れる
4. dequeが空になるまで次を繰り返す
    - dequeの先頭から元Vを取り出して削除する
    - Vが未探索(d[V]==inf)なら、次の操作を行った上でVを探索済みにする
        Vに隣接する全ての頂点Wに対して以下を行う
        -VとWを結ぶ長さが0であり、D[W]>D[V]なら、dequeの先頭にWを入れて、D[W]=D[V]とする。
        -VとWを結ぶ長さが0であり、D[W]>D[V]+1なら、dequeの末尾にWを入れて、D[W]=D[V]+1とする。

この操作において、dequeが常に昇順となることが保証される
*/


//最短パスの個数
/*
sからtへの最短パスの個数を求める
1. sから幅全探索で各点への最短距離を求める
2. 「 s から t へのパスであって、パス上の全ての辺 u→v が dist[u]+1=dist[v] を満たすもの」の本数を数える。
これは、 s から各頂点 v への条件を満たすパスの本数 dp[v] を、 dist[v] の昇順に求めていく動的計画法によって、dp[t] として求められる。
(つまり、最短距離d’の頂点v'に対するdp[v']の値を求めるには、最短距離d'-1の頂点u'であってu'→v'の辺があるもの全てのdp[u']の和を取れば良い)
*/

/*
連結成分の個数
入力: グラフG
出力: Gの連結成分の個数
*/
int connection_count(vector<vector<int>>& G){
    int n=G.size();
    queue<int> q;
    vector<int> seen(n,-1);
    int ans=0;
    for(int i=0;i<n;i++){
        if(seen[i]==1) {continue;}
        q.push(i);
        while(!q.empty()){
            int s=q.front();
            q.pop();
            for(auto u:G[s]){
                if(seen[u]==-1){
                    seen[u]=1;
                    q.push(u);
                }
            }
        }
        ans++;
    }
    return ans;
}



//連結とは限らない無向グラフに対し、それを連結成分ごとに分解してそれぞれの頂点集合を返す
    //入力: 無向グラフG
    //出力: 各連結成分ごとの頂点集合のvector

vector<vector<int>> partitioned_graph(vector<vector<int>>& g){
    int n=g.size();
    vector<int> memo(n,-1);
    vector<vector<int>> ans;
    int ind=0;
    for(int i=0;i<n;i++){
        if(memo[i]!=-1)continue;
        ans.pb(vector<int>());
        queue<int> que;
        que.push(i);
        memo[i]=ind;
        while(que.size()){
            int s=que.front();
            que.pop();
            ans[ind].pb(s);
            for(auto u:g[s]){
                if(memo[u]==-1){
                    que.push(u);
                    memo[u]=ind;
                }
            }
        }
        ind++;
    }
    return ans;
}


/*閉路検出
(1) 有向辺(自己ループを含まないもの)
グラフGに対して、「ある」Gの閉路を構成する点をパス順にvectorに入れて返す
入力: グラフG
出力: 閉路がなければ空のvectorを返す
*/
void dfs_forloop(int s, int& van, vi& seen, vi& finished, vi& ans, stack<int>& history, vvi& G){
    if(van==1) return;
    seen[s]=1;
    history.push(s);
    for(auto to:G[s]){
      if(van==1) return;
        if(seen[to]==-1){
            dfs_forloop(to, van, seen, finished, ans, history, G);
        }
        else if(seen[to]==1 && finished[to]==-1){
            ans.push_back(to);
            while(history.top()!=to){
                ans.push_back(history.top());
                history.pop();
                /*
                if(ans.size()==2){
                  if(history.top()==to){
                    history.push(ans[1]);
                    ans.clear();
                    break;
                  }
                } //無向辺グラフの時は書く
                */
            }
            if(ans.empty()) continue;
            reverse(all(ans));
            van=1;
        }
    }
        finished[s]=1;
        if(van==1)return;
        history.pop();
        return;
    }

  
vector<int> loop_finder(vvi& G){
    int Gsz=G.size();
    vector<int> ans;
    vector<int> seen(Gsz,-1);
    vector<int> finished(Gsz,-1);
    for(int i=0;i<Gsz;i++){
        if(seen[i]==-1){
            stack<int> history;
            int van=0;
            dfs_forloop(i, van, seen, finished, ans, history, G);
            if(!ans.empty()) return ans;
        }
    }
    return ans;
}


//各連結部分ごとに一つまで閉路を検出するもの
void dfs_forloop(int s, int& van, vi& seen, vi& finished, vvi& ans, stack<int>& history, vvi& G, int& anscnt){
    if(van==1) return;
    seen[s]=1;
    history.push(s);
    for(auto to:G[s]){
      if(van==1) return;
        if(seen[to]==-1){
            dfs_forloop(to, van, seen, finished, ans, history, G,anscnt);
        }
        else if(seen[to]==1 && finished[to]==-1){
            ans[anscnt].push_back(toas);
            while(history.top()!=to){
                ans[anscnt].push_back(history.top());
                history.pop();
                /*
                if(ans.size()==2){
                  if(history.top()==to){
                    history.push(ans[anscnt][1]); //多分anscntだと思う
                    ans.clear();
                    break;
                  }
                } //無向辺グラフの時は書く
                */
            }
            if(ans.empty()) continue;
            reverse(all(ans[anscnt]));
            van=1;
        }
    }
        finished[s]=1;
        if(van==1)return;
        history.pop();
        return;
    }

  
vvi loop_finder(vvi& G){
    int Gsz=G.size();
    vvi ans(Gsz);
    vector<int> seen(Gsz,-1);
    vector<int> finished(Gsz,-1);
    int anscnt=0;
    for(int i=0;i<Gsz;i++){
        if(seen[i]==-1){
            stack<int> history;
            int van=0;
            dfs_forloop(i, van, seen, finished, ans, history, G, anscnt);
            if(ans[anscnt].size()) anscnt++;
        }
    }
    return ans;
}

/*
(2) 無向辺(単純なもの)
同様(Gに両方向の辺を張るだけ この辺によるループを例外処理で除く)上の一部処理を変えるだけ
*/


//DSU(union-findのこと?)
/* 無向グラフに対しての連結判定を行う 辺の更新と連結判定がほぼO(1) (正確にはならしO(α(n))でできる)
*/
// atcoder-allによる実装
dsu d(int n); //n個の頂点を持つグラフを作る
int d.merge(int a, int b)
bool d.same(int a, int b)
int d.leader(int a) //aの属する連結成分の代表元を返す
int d.size(int a)
vector<vector<int>> d.groups() // グラフを連結成分に分け、その情報を返す。
//返り値は「「一つの連結成分の頂点番号のリスト」のリスト」 (内側外側限らず)vector内でどの順番で頂点が格納されているかは未定義


//強連結成分分解(SCC(Strongly Connected Component))
/*
有向グラフにおいて、互いに行き来が可能(連結)な頂点の集合を調べたい時に考える。Union-findが無向グラフでの連結判定に使えるのに
対して、有向グラフでは強連結成分分解を用いる。

1. 深さ優先探索（再帰）で有向グラフを走査し、閉路によって戻れる頂点を特定する
2. 奥から強連結成分のIDを振ることで、トポロジカルソート（の降順）が成立します
*/
//atcoder-libraryによる使用
scc_graph graph(int n); //n個の頂点を持つグラフを作る
void graph.add_edge(int from, int to) //fromからtoへの有向辺を追加する
vector<vector<int>> graph.scc()
//次の条件を満たす「頂点のリスト」のリストを返す(O(n+m))
/*
全ての頂点がちょうど1つずつどれかのリストに含まれる
内側のリストと強連結成分が一対一に対応。リスト内での頂点の順序は未定義
リストは(異なる強連結成分の間で)トポロジカルソートされている。
*/

//実装




/*ベルマンフォード
G: edge属性のグラフ(2次元)
d: 各点への最短距離(1次元 最初はinfで埋める)

点sから各点への最小距離を求めて配列dで返す O(VE)
(負の長さの辺を持つ場合は検出できる)

1. 全ての辺(u,v)に対して、d[v] = min{ d[u] + ( u から v への距離 )} の形で更新を行う
    (1回の1の操作で最低1つの頂点の最短距離が確定する)
2. 1においてどの頂点の最短距離も更新されなくなった時に終了できる。
    |V|回目の1の後も更新が行われるなら、負の閉路が存在することがわかる。
*/




/*ワーシャルフロイド

任意の二頂点間の最短距離を求める O(V^3)
負の辺にも対応できる とくにdp[i][i]が負となるiがあれば負の閉路が存在することがわかる
*/
for(int k=0;k<V;k++){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    }
}

//実装
//入力は、点(i,j)にパスがあれば(i,j)をその長さの最小値、なければinfとし、(i,i)を0とした行列dist
void warshall_floyd(vector<vector<long long>> &dist) {
    int V = dist.size();
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}



/*経路復元
汎用的な方法
    prev(n,-2)という配列を作り、各頂点iに対してprev[i]をiに至る一つ前の頂点として記録する。(-2:未処理, -1:一つ前の頂点がない)
    (最短距離が更新された時にprev[i]を埋めれば良い)
*/

//ex dijkstra法での実装

//ex ワーシャルフロイド法での実装

/*
最長経路
DAGについてはトポソをしてからDPで線形でいける
一般の有向グラフについてはダイクストラは使えずベルマンフォードを使う必要がある
*/


/*最小全域木(MMinimum Spanning Tree)
最小全域木とは、グラフの全ての頂点を含む木のうち、辺の重みの総和が最小のものをいう
最小全域木の求め方2つ

1. クラスカル法  𝑂(|𝐸|log|𝑉|) (辺を加える)
    1 辺集合Eをコストの小さい順にソートする
    2 以下を 𝑉−1 個の辺を選ぶまで（最小全域木 𝑇 ができるまで）繰り返す
        残っている辺の中からコストが最小の辺 e を取り出す。現在構成中の 𝑇 に e を加えても閉路ができないなら 𝑇 に加える。
        (閉路ができないことは、unionfindでeの端点が同じ集合に属していない(=2点間で連結ではない)ことで判定できる)

2.プリム法  O(E log V) (頂点を加える)
    1 はじめに、適当に選んだ頂点1つのみをTに含めると確定させる
    2 以下をすべての頂点が 𝑇 に含まれるまで繰り返す
        全ての「既に確定した頂点」から「まだ確定していない（𝑇 に含まれていない）頂点 」へ伸びる辺を全て確認して、
        最小のコストの辺 e=(u,v) を選ぶ。そして v を 𝑇 に含めることにする。
   
*/


/*二部グラフ判定と彩色
単純連結無向グラフGに対して、Gが二部グラフであるかを判定し、そうである場合は頂点に0,1で彩色し、
各点に対する彩色を表すvectorを返す。
二部グラフでない場合は、空のvector配列を返す。
(ある一点から交互に色を塗り、最後まで塗れれば二部グラフである)
*/

void color_dfs(vvi& G, vi& coloring, int s, int color, int& imp){
    if(imp==1) return;
    coloring[s]=color;
    for(auto to:G[s]){
        if(coloring[to]==abs(1-color)) continue;
        else if(coloring[to]==-1) color_dfs(G, coloring, to, abs(1-color), imp);
        else{imp=1; return;}
    }
    return;
}

vi bipartite_coloring(vvi& G){
    int n=G.size();
    int imp=0;
    vi coloring(n,-1);
    vi emptyset;
    color_dfs(G,coloring,0,0,imp);
    if(imp==1)return emptyset;
    return coloring;
}





/*関節点:グラフから取り除くとグラフの連結成分の個数が増えるような頂点

*/


/*橋:無向連結グラフにおいて、グラフから取り除くとそのグラフが非連結になるような辺

*/