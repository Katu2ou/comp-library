#include<atcoder/all>

//UnionFind//
int n,x,y
dsu U(n); 
U.merge(x,y);
U.same(x,y);
U.groups(); //vector<vector<int>> Uの各連結成分のリストを返す
U.leader(x); //U上でのxの代表元を返す

//SCC
scc_graph graph(int n); //n頂点0辺の有向グラフを作る
void graph.add_edge(int from, int to); //fromからtoへの有向辺を追加する(ならしO(1))
vector<vector<int>> graph.scc(); 
//全ての頂点がちょうど1つずつどれかのリストに含まれる
//内側のリストと強連結成分が一対一に対応。リスト内での頂点の順序は未定義
//リストは(異なる強連結成分の間で)トポロジカルソートされている。(O(n+m))

//fenwick_tree(BIT)
int n,i,x,l,r;
fenwick_tree<int> A(n) //0 origin, 開区間である defaultはA[i]=0
A.add(i,x); //A[i]+=x
A.sum(l,r); //A[l]+A[l+1]+...+A[r-1]


//Segtree(n<=10^8)
int op(int x, int y){
   return x+y;
}
//モノイドである演算を定義する
int e() {
    return (int)(1e9);
} 
//eは単位元
vector<int> A(n);
segtree<int,op,e> S(A); //vector Aからsegtreeを作る
segtree<int,op,e> S2(int n); //サイズnのsegtree(各要素は単位元e)を作る
S.set(p,x); //s[p] にxを代入
S.get(p); //s[p]を返す
S.prod(l,r); //S[l]*S[l+1]*...*S[r-1]を返す(*はopの演算)
S.all_prod(); //S[0]*S[1]*...*S[n-1]を返す。n=0ならe()を返す

S.max_right<f>(int l); 
/*関数 bool f(int x)を用意する。
r = l もしくは f(op(a[l], a[l + 1], ..., a[r - 1])) = true
r = n もしくは f(op(a[l], a[l + 1], ..., a[r])) = false
の両方を満たすrをいずれか一つ返す(seg木上の二分探索)
ここでf(e())=true,0<=l<=nが制約
*/

S.max_left<f>(int r); 
/*関数 bool f(int x)を用意する。
l = r もしくは f(op(a[l], a[l + 1], ..., a[r - 1])) = true
l = 0 もしくは f(op(a[l - 1], a[l], ..., a[r - 1])) = false
の両方を満たすrをいずれか一つ返す
ここでf(e())=true,0<=r<=nが制約
*/


//Lazysegtree
/*
モノイド(S*S→S, e \in S)と、SからSへの写像の集合Fであって、
Fがidを含み、Fが写像の合成について閉じており、しかも
f(x*y)=f(x)*f(y)を満たすものに使える。
*/
using S = int;
using F = int;
//(予めこのように型指定をしておく)

S op(S x, S y){
   return x+y;
}

//何も足さないことは0を足すことと同値(モノイドSの単位元)
S e(){
	return 0;
}

//fとxの型は同じでなくても良い(f(S[i])の結果を書く)
S mapping(F f, S x){
	if(f == 1){
		if(x == 1) return -inf;
		else return 1;
	}
	else return x;
}

//複数の関数を合成するための関数
F composition(F f, F g){
   return (f+g)%2;
}

//関数集合Fの単位元id
F id(){
   return 0;
}

vector<ll> A(n);
lazy_segtree<S,op,e,F,mapping,composition,id> S(A);

S.set(p,x); //S[p]にxを代入
S.get(p); //S[p]を求める
S.prod(l,r); //S[l]*S[l+1]*...*S[r-1]を求める
S.apply(l,r,f); //S[l],S[l+1],...,S[r-1]のそれぞれにfを作用させる


//Math
ll x,n,p;
ll ans=pow_mod(x,n,p); 
ll ans=inv_mod(x,p); 

//xをm_iで割った余りがr_i を満たすとき、(満たす値, mの最小公倍数)を返し、
//満たさない時は(0,0)を返す。
pair<ll,ll> ans=crt(vector<ll>,r,vector<ll>,m);

ll ans=floor_sum(n,m,a,b); //floor((ai+b)/m) sum(i=0,n-1)を求める


//最大流
mf_graph<Cap> graph(int n); //n頂点0辺のグラフを作る(Capは容量の型(int,ll)) O(n)
int graph.add_edge(int from, int to, Cap cap); // fromからtoへ最大容量cap、流量0の辺を追加し、何番目に追加された辺かを返す。(ならしO(1))
Cap graph.flow(int s, int t); //sからtへ流せる限り流し、流せた量を返す。
Cap graph.flow(int s, int t, Cap flow_limit); //sからtへflow_limitまで流せる限り流し、流せた量を返す。
//計算量: 上はO(min(mn^2/3,m^3/2))(辺の容量が全て1のとき)  下はO(n^2m)
//(特に、最大流がFのときO(FE),辺の容量が高々CのときO(CE^3/2)でかつ多重辺がない時O(CV^2/3E))
//各頂点を流れるフローが高々FのときO(FV^1/2E),特に二部マッチングはO(EV^1/2)
vector<bool> graph.min_cut(int s); // 長さnのvectorを返す。i番目の要素には、sからiへ残余グラフで到達可能な時のみtrueで返す。
//flow(s,t)を「flow_limitなしで」ちょうど一回呼んだ後に呼ぶと、返り値はs,t間のmincutに対応する。 (O(n+m))
struct mf_graph<Cap>::edge {
    int from, to;
    Cap cap, flow;
};
(1) mf_graph<Cap>::edge graph.get_edge(int i); //i番目の辺を返す
(2) vector<mf_graph<Cap>::edge> graph.edges();
//今の内部の辺の状態を返す。辺の順番はadd_edgeで追加された順番と同一
void graph.change_edge(int i, Cap new_cap, Cap new_flow); //i番目の辺の容量と流量を変更する。他の辺は変更しない。O(1)

//最小費用流
mcf_graph<Cap,Cost> g(int n); //n頂点0辺のグラフを作る(Capは容量の型、Costはコストの型(int,llなど))
int graph.add_edge g.add_edge(int from, int to, Cap cap, Cost cost); //fromからtoに流量nの辺を張る 何番目に追加された辺であるかを返す
pair<Cap, Cost> g.flow(int s, int t);; //stからtvにできるだけ流し、その流量とコストを返す
pair<Cap, Cost> g.flow(int s, int t, Cap flow_limit); //sからtへ流量flow_limitまで流せるだけ流し、同様
vector<pair<Cap, Cost>> g.slope(int s, int t);
vector<pair<Cap, Cost>> g.slope(int s, int t, Cap flow_limit);
//全ての流量xにおける(x,mincost)のvectorを返す((0,0), ..., (F,mincost))
//ここでslopeはpairの両方に対して単調増加であることが保証されており、どの3点も同一直線上にない
//よって、(0,0),(1,a),(2,b)....というの形とは限らない ((0,0),(3,a),(7,b)...かもしれない mincostの勾配が更新された時だけ追加される)
//ex) (0,0),(1,5),(2,10)(ここでは流量に対する勾配が5で一定),(3,14)...のときは(0,0),(1,5),(3,14)...を含み、(2,10)を含まない
//これら四つを複数回呼んだときの動作は未定義 これらはO(F(n+m)logn) (Fは流量)
struct edge<Cap, Cost> {
    int from, to;
    Cap cap, flow;
    Cost cost;
};
 mcf_graph<Cap, Cost>::edge g.get_edge(int i);
 vector<mcf_graph<Cap, Cost>::edge> g.edges();
//今の内部の辺の状態を返す(辺の順番は追加順と同じ)

//畳み込み
convolution_ll(vector<ll>,vector<ll>); 
//mod 998244353で畳み込みを行う, vector<ll>(係数行列)が返る


//floor sum
ll floor_sum(ll n, ll m, ll a, ll b)
//floor((ai+b)/m)のi=0...n-1までの和を求める


//modint
using mint = atcoder::modint998244353;
//mint型で定義すれば勝手にmodをとってくれる
using mint = atcoder::modint1000000007;
//modが可変なときは以下のようにする
using mint = modint;
int mod=10007;
mint set_mod(mod);
// set_modのmodの値の範囲は1以上2000000000+1000以下
//定数をmodintにしたいときは下のように書く(単に3とかいてもmint型として正しく計算してくれるかも)
sum += sum + mint(3);
/*
演算としては、加減乗除と==,!=が使える 冪乗や逆元は以下のようにする
*/
modint x.pow(ll n);
modint x.inv(ll n);
modint modint::raw(int x);
//xに対してmodを取らずにmodint(x)を返す。高速化。
//出力の時は下のようにする
mint a=21;
cout<<a.val()<<endl;
//
int a;
cin>>>a;
mint b=a;
//cin>>bのように直接mint型に入力を入れることはできないので、一度intなどで
//受け取ってからmint型の変数に入れる

