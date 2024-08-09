//https://atcoder.jp/contests/abc339/submissions/49931796 
//一点加算区間和の永続セグメント木

#define sz (1<<19)
struct per_seg{
	vector<int>root;
	int L[20000005],R[20000005],id;
	int seg[20000005];
	void make(){
		rep(i,20000005){
			L[i] = 0;
			R[i] = 0;
			seg[i] = 0;
		}
		id = 0; root.clear();
		for(int i=0;i<sz-1;i++) L[i] = i*2+1,R[i] = i*2+2;
		root.push_back(0); id = 2*sz;
	}
	int update(int a,int k,int l,int r,int st){
		if(l==r){
			seg[id] = seg[k]+st;
			return id++;
		}
		if(l<=a && a<=(l+r)/2){
			int x = update(a,L[k],l,(l+r)/2,st);
			seg[id] = (seg[x]+seg[R[k]]);
			L[id] = x; R[id] = R[k];
			return id++;
		}
		else{
			int x = update(a,R[k],(l+r)/2+1,r,st);
			seg[id] = (seg[L[k]]+seg[x]);
			L[id] = L[k]; R[id] = x;
			return id++;
		}
	}
	void update(int pos,int st){
		int R = root.back();
		int nw = update(pos,R,0,sz-1,st);
		root.push_back(nw);
	}
	int query(int a,int b,int k,int l,int r){
		if(r<a || b<l) return 0;
		if(a<=l && r<=b) return seg[k];
		return (query(a,b,L[k],l,(l+r)/2)+query(a,b,R[k],(l+r)/2+1,r));
	}
	int query(int ver,int l,int r){
		return query(l,r,root[ver],0,sz-1);
	}
}pseg;


/*
インスタンス名をpseg とする
pseg.make() :作成

update(pos,st) :現在のセグ木において，0-indexedでpos番目にstを加える
(中のupdate: (最下層において値を更新する位置の「左から数えた」index, 今見ている区間のindex, 今見ている区間の左端,
今見ている区間の右端, 更新後の値))

query(ver,l,r) :バージョンverのセグ木(最初が0で，updateを行うごとに+1される 根のノードにより規定)
において，区間[l,r]の和を求める

- 任意のバージョンでの任意の頂点の値は，query(ver,l,l)によってO(logNQ)で知ることができる．

*/
 
//テンプレート型

#define MAXseg 20000005
#define sz (1<<19)
template<typename T>
struct per_seg{
    vector<int>root;
	T L[MAXseg],R[MAXseg],seg[MAXseg];
	int id;
	void make(){
		rep(i,MAXseg){
			L[i] = 0;
			R[i] = 0;
			seg[i] = 0;
		}
		id = 0; root.clear();
		for(int i=0;i<sz-1;i++) L[i] = i*2+1,R[i] = i*2+2;
		root.push_back(0); id = 2*sz;
	}
	int update(int a,int k,int l,int r,T st){
		if(l==r){
			seg[id] = seg[k]+st;
			return id++;
		}
		if(l<=a && a<=(l+r)/2){
			int x = update(a,L[k],l,(l+r)/2,st);
			seg[id] = (seg[x]+seg[R[k]]);
			L[id] = x; R[id] = R[k];
			return id++;
		}
		else{
			int x = update(a,R[k],(l+r)/2+1,r,st);
			seg[id] = (seg[L[k]]+seg[x]);
			L[id] = L[k]; R[id] = x;
			return id++;
		}
	}
	void update(int pos,T st){
		int R = root.back();
		int nw = update(pos,R,0,sz-1,st);
		root.push_back(nw);
	}
	T query(int a,int b,int k,int l,int r){
		if(r<a || b<l) return 0;
		if(a<=l && r<=b) return seg[k];
		return (query(a,b,L[k],l,(l+r)/2)+query(a,b,R[k],(l+r)/2+1,r));
	}
	T query(int ver,int l,int r){
		return query(l,r,root[ver],0,sz-1);
	}
}pseg;