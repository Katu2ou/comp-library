#include<atcoder/all>
using namespace std;
using namespace atcoder;

/*
//segtree(n<=10^8)
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
の両方を満たすrをいずれか一つ返す
ここでf(e())=true,0<=l<=nが制約

S.max_left<f>(int r); 
関数 bool f(int x)を用意する。
l = r もしくは f(op(a[l], a[l + 1], ..., a[r - 1])) = true
l = 0 もしくは f(op(a[l - 1], a[l], ..., a[r - 1])) = false
の両方を満たすrをいずれか一つ返す
ここでf(e())=true,0<=r<=nが制約
*/



// 区間最小を演算とするセグメント木
int op(int a,int b){
	return min(a,b);
}
//単位元はinfを取っておく
int e(){
	return 1e9;
}

int main(){
   int n;
	cin>>n;
	vector<vector<int>> x(n);
	rep(i,n){
		int a,b,c;
		cin>>a>>b>>c;
		x[i] = {a,b,c};
		sort(x[i].begin(),x[i].end());
	}
}

//使用例・用法
/*
(1) LIS(最長増加部分列)を求める
各Pjに対してPjを末尾とする単調増加部分列の長さの最大値をdpjとする。
dp1=1であり、一般のjに対しては、
i<jかつPi<Pjなるiについてのdpiの最大値+1(そのようなiがなければ1)として求められる。
*/
//実装(各点に対してその点を末尾とするLISの長さを持つvectorを返す)
//Pは座標圧縮済みのvector(長さnに対して0,1,...,n-1以下)
//LISの復元は、dpの値が更新される時に、自身以下のiでdpiが最大のものを記録することでできる
int op(int a,int b){
	return max(a,b);
}
int e(){
	return 0;
}
vector<int> LIS(vector<int>& P){
	int n = P.size();
	vector<int> dp(n,0);
	vector<int> ans(n,0);
	segtree<int,op,e> S(dp);
	rep(j,n){
		int u=S.prod(0,P[j])+1;
		S.set(P[j],u);
		ans[j]=u;
	}
	rep(i,n){
		dp[i]=S.get(P[i]);
	}
	return dp;
}


//(2) セグ木上の二分探索


