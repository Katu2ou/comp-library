/* 
<辺と頂点が情報を持っているEuler Tour>
.辺は{cost,to}のpair

.通った辺についても記録
.頂点iの値をv_i
.頂点iから伸びる辺の番号を[i+1]として、辺jの値をe_j
.辺を入ったり出たりした時に頂点と共に記録(入った時に辺の番号を記録し、出た時にその-1倍を記録 最初と最後は1,-1を記録)
.各頂点に最初に「辿り着く」indexと「抜けた」時の最初のindexを記録(in/out)

.頂点に初めてたどり着いた時にその頂点の値を記録(それ以外の時は頂点の値に関する演算の単位元を記録)
.辺を初めて通った時にその辺の値を記録(それ以外の時は辺の値に関する演算の単位元を記録)
.上二つによって部分木クエリに応えられるようになる
(Segで値の1点変更や部分木更新ができ、遅延セグ木で部分木更新にも対応)
.パスクエリに答えるには、単位元の代わりに対応する頂点や辺を抜けた時にその値の逆元を記録
→累積和により、値から該当する点までのパスの辺の和を得られる(足す順番が固定されている点に注意。
頑張れば別の順番で足すようにもできる)

.よって、求めるものは以下の通りになる
	- 通った順番に{頂点/辺/頂点の値(or単位元or逆元)/辺の値(or単位元or逆元)/深さ/頂点の親}を記録したもの
	  (ここでET[0],ET[4]の第2n項はrootの頂点として、ET[5]は長さnで、他は長さ2n)
	- 各頂点に対して、inしたindexとoutしたindex

例として以下のような実装になる(グラフの親と子供も取得してしまう)
*/

// Gは各頂点に対して、{その頂点から出る辺の行き先,その辺の値}というpairを要素に持つvectorである。
// 辺や頂点の値を持たない時は0など適当な値で良い
// 辺や頂点の演算に関する単位元は最初に指定する

//再帰用(child,parent,ET(情報を入れるvector),頂点の値を入れるvector,今の頂点,今の頂点の深さ,頂点と辺のid,現在のindex)
void Euler_Tour_reduction(vector<vpll>& child, vpll& pare, vvl& ET, vl& VertexValue, vpii& Vin_out, int nv, int depth, int& num){
	ET[0].pb(nv);
	ET[1].pb(nv+1);
	ET[2].pb(VertexValue[nv]);
	ET[3].pb(pare[nv].se);
	ET[4].pb(depth);
	Vin_out[nv].fi=num;
    num++;
	for(auto x:child[nv]){
		ll to = x.fi;
		ll val = x.se;
		Euler_Tour_reduction(child, pare, ET, VertexValue, Vin_out, to, depth+1, num);
		ET[0].pb(nv);
		ET[4].pb(depth);
	}
	
	ET[1].pb(-nv-1);
	ET[2].pb(0); //パスクエリにしたいときなどは変える
	ET[3].pb(-pare[nv].se); //パスクエリにしたいときなどは変える
	Vin_out[nv].se=num;
    num++;
	return;
}

pair<vvl,vpii> Euler_Tour(vector<vpll>& G, int root, vl& VertexValue){
	int n=G.size();
	vi order={root},depth(n);
	vpll pare(n,{-INF,-INF});
	vector<vpll> child(n);
	vpii Vin_out(n,{-1,-1});
	pare[root]={-1,0};
	for(int i=0;i<n;i++){
		int a=order[i];
		for(auto x:G[a]){
			ll to=x.fi;
			ll val=x.se;
			if(pare[to].fi==-inf){
				pare[to].fi=a;
				pare[to].se=val;
				depth[to]=depth[a]+1;
				order.push_back(to);
				child[a].push_back({to,val});
			}
		}
	}


	vvl ET(6);
    int num=0;
	Euler_Tour_reduction(child, pare, ET, VertexValue, Vin_out, root, 0, num);
	ET[0].pb(root);
	ET[4].pb(0);
	vl parent;
	rep(i,n){
		parent.pb(pare[i].fi);
	}
	ET[5]=parent;
	return {ET,Vin_out}; //Vin_outが欲しい時は、関数の方をpair<vvl,vpii>としておけばよい
                         //ETにおいて番号iの辺は、下頂点がi-1,上頂点がET[5][i-1]である。
                         //つまり、辺iを持つ2つのindexは、下側の頂点をuとしてET2[u].fi,ET2[u].se
}

//二頂点の最近共通祖先(LCA)を求める
//前処理
pii LCA_op(pii a, pii b){
	return min(a,b);
}
pii LCA_e(){
	return {inf,inf};
}
vpii DEP;
rep(i,n){
	DEP.pb({ET[4][i],i});
}

atcoder::segtree<vpii, LCA_op, LCA_e> S(DEP);

//実際には以下のコードはmain関数の中に埋め込む
int LCA(int u, int v, vvl& ET, vpii& Vin_out){
	int ff=Vin_out[u].fi;
	int ss=Vin_out[v].fi;
	if(ff>ss) swap(ff,ss);
	pii ww = S.prod(ff,ss+1);
	int ii = ww.se;
	return ET[0][ii];
}

//構造体を用いる
struct Edge{
	ll from, to, cost;
	ll index;
}

//抽象化