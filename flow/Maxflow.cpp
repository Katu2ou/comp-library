//辺を表す構造体(行き先、容量、逆辺)
struct edge{int to, cap, rev; };
vector<edge> G[500]; //(MAX_V)
bool used[500]; //(MAX_V)

//無向辺の場合は下。有向辺の場合は逆向きのcapを0にする
void add_edge(int from, int to, int cap){
G[from].pb((edge){to,cap,G[to].size()});
G[to].pb((edge){from,cap,G[from].size()-1});
}

//増加パスをdfsで探す
int dfs(int v, int t, int f){
	if(v==t) return f;
	used[v]=true;
	for(int i=0;i<G[v].size();i++){
		edge &e=G[v][i];
		if(!used[e.to] && e.cap >0){
			int d=dfs(e.to, t, min(f,e.cap));
			if(d>0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

//sからtへの最大流を求める(O(F|E|) Fは最大流の流量)
//1回しか流せないので注意（2回max_flowを書くと後の方の値が0になる)

int max_flow(int s,int t){
int flow=0;
for(;;){
	memset(used,0,sizeof(used));
	int f=dfs(s,t,inf);
	if(f==0) return flow;
	flow+=f;
}
}


int main() {
 ios::sync_with_stdio(false);

int n;
int ans;
cin>>n;

int red[n+1][2];
int blue[n+1][2];
for(int i=1;i<=n;i++){
	int a,b;
	cin>>a>>b;
	red[i][0]=a;
	red[i][1]=b;
}
for(int i=1;i<=n;i++){
	int a,b;
	cin>>a>>b;
	blue[i][0]=a;
	blue[i][1]=b;
}
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		if(red[i][0]<blue[j][0]&&red[i][1]<blue[j][1]){
			add_edge(i,n+j,1);
		}
	}
}
for(int i=1;i<=n;i++){
	add_edge(0,i,1);
	add_edge(n+i,2*n+1,1);
}


cout<<max_flow(0,2*n+1)<<endl;

return 0;
}



//Ford-Fullkerson(フォード・ファルカーソン)法
/*
1. BFS（幅優先探索）で、s(source) から t(sink) へ辿り着くことができるパスを探します。s(source)に近い順に level を記録しておきます。
2. 先ほど決定したlevel順に経路をもつパスについて、DFS（深さ優先探索）を行い、フローを流して、残余ネットワークを更新していきます。上階層から下階層へはこれまでの残余ネットワークの最小値を渡していき、一番下の階層から戻ってくるときに、残余ネットワークの更新を行っています。
3. 1に戻って、s(source) から t(sink)へ辿り着けるパスを探します。残余ネットワークが更新されているので、t(sink)に辿り着けるパスがもうないかもしれません。仮にパスがなければ終了となります。
O(maxflow*E)
*/

//Dinic(ディニッツ)法
/*
1. 距離が増加する向きの辺のみで構成されたグラフをbfsで取得する。
2. グラフにおける増加パスをdfsで求め、フローを流す。
3. 全ての増加パスにフローを流しおわったら1に戻り、これを増加パスが存在しなくなるまで繰り返す。

1,2でO(VE)回かかり、それをV-1回繰り返すので、全体でO(V^2E)となる。(実際はこれより軽く通りやすい)
*/


//AC Libraryによる実装
//Maxflow
mf_graph<Cap> graph(n); //Capは容量の型で、int 又は ll (O(n))
int graph.add_edge(int from, int to, Cap cap); //fromからtoへ最大容量cap,流量0の辺を追加する (ならしO(1))
Cap graph.flow(int s, int t); //頂点sからtへ流せるだけ流して、流せた量を返す (mを追加された辺数として、O(min(n^2/3m, m^3/2)) 辺の容量が全て1のとき)
Cap graph.flow(int s, int t, Cap flow_limit); //頂点sからtへ流量flow_limitに達するまで流せるだけ流して、流せた量を返す (O(n^2m))
vector<bool> graph.min_cut(int s); //長さnのベクトルを返す。i番目の要素は、頂点sから頂点iへ残余グラフで到達可能かどうかを返す。
//特に、flow(s,t)をflow_limitなしでちょうど一回呼んだ後に返すと、返り値はs,tのmincutに対応する。
//つまり、trueならmincutしたときのs側に入り、falseならt側に入る (O(n+m))
struct mf_graph<Cap>::edge {int from, to; Cap cap, flow;};
mf_graph<Cap>::edge graph.get_edge(int i); //今の内部の辺の状態を返す (O(1))
vector<mf_graph<Cap>::edge> graph.edges(); //同様を全ての辺に対してする。辺の順番はadd_edgeで追加された順。(O(m))
void graph.change_edge(int i, Cap new_cap, Cap new_flow);//i番目に追加された辺の容量、流量を変更する (O(1))


//使用例
//(1). 二部グラフの最大マッチング
/*
1. 二部グラフG=(L∪R,E)に対応するフローネットワークG'を作る
	- Gにソースsとシンクtを加える
	- sからLの全ての頂点に対して容量1の有向辺を張る
	- Rの全ての頂点からtに対して容量1の有向辺を張る
	- Lの頂点とRの頂点を結ぶ辺はLからRへの容量1の有向辺とする
2. G'の最大フローの流量は最大マッチングのサイズと一致する
*/


//(2)