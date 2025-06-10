//辺や頂点の情報がない時の簡単な場合
//ETに持たせる情報は{点/辺/深さ/親}
//Vin_outは同様の情報を持たせる

void Euler_Tour_reduction(vvi& child, vi& pare, vvi& ET, vpii& Vin_out, int nv, int depth, int& num){
	ET[0].pb(nv);
	ET[1].pb(nv+1);
	ET[2].pb(depth);
	Vin_out[nv].fi=num;
    num++;
	for(auto x:child[nv]){
		int to = x.fi;
		int val = x.se;
		Euler_Tour_reduction(child, pare, ET,  Vin_out, to, depth+1, num);
		ET[0].pb(nv);
		ET[2].pb(depth);
	}
	
	ET[1].pb(-nv-1);
	Vin_out[nv].se=num;
    num++;
	return;
}

pair<vvi,vpii> Euler_Tour(vvi& G, int root){
	int n=G.size();
	vi order={root},depth(n);
	vi pare(n,-inf);
	vvi child(n);
	vpii Vin_out(n,{-1,-1});
	pare[root]={-1,0};
	for(int i=0;i<n;i++){
		int a=order[i];
		for(auto to:G[a]){
			if(pare[to]==-inf){
				pare[to]=a;
				depth[to]=depth[a]+1;
				order.push_back(to);
				child[a].push_back(to);
			}
		}
	}

	vvi ET(4);
    int num=0;
	Euler_Tour_reduction(child, pare, ET, Vin_out, root, 0, num);
	ET[0].pb(root);
	ET[2].pb(0);
	vi parent;
	rep(i,n){
		parent.pb(pare[i]);
	}
	ET[3]=parent;
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
	DEP.pb({ET[2][i],i});
}

atcoder::segtree<vpii, LCA_op, LCA_e> S(DEP);

//実際には以下のコードはmain関数の中に埋め込む
int LCA(int u, int v, vvi& ET, vpii& Vin_out){
	int ff=Vin_out[u].fi;
	int ss=Vin_out[v].fi;
	if(ff>ss) swap(ff,ss);
	pii ww = S.prod(ff,ss+1);
	int ii = ww.se;
	return ET[0][ii];
}




//辺にのみ情報を持たせる時


