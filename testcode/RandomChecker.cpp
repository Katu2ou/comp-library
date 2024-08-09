#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <atcoder/all>
using namespace std;
using namespace atcoder;


#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) rep2(i, 0, n)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)
#define all(...) std::begin(__VA_ARGS__), std::end(__VA_ARGS__)
#define rall(...) std::rbegin(__VA_ARGS__), std::rend(__VA_ARGS__)
#define FOR(i, a, b) for (int i = (a), i##_len = (b); i <= i##_len; ++i)
#define REV(i, a, b) for (int i = (a); i >= (b); --i)
#define CLR(a, b) memset((a), (b), sizeof(a))
#define DUMP(x) cout << #x << " = " << (x) << endl;
#define INF 1001001001001001001ll
#define inf (int)1001001000
#define MOD 998244353
#define Dval 1e-12
#define fcout cout << fixed << setprecision(12)
#define mp make_pair
#define pb push_back
#define fi first
#define se second

using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vd = vector<double>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvd = vector<vector<double>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using mint = atcoder::modint998244353;

ll POW(ll x, ll n){ll ret=1;	while(n>0){		if(n&1) ret=ret*x;		x=x*x;		n>>=1;	}	return ret;}
ll modpow(ll a, ll n, ll p) {	if(n==0) return (ll)1;  if (n == 1) return a % p;  if (n % 2 == 1) return (a * modpow(a, n - 1, p)) % p;  ll t = modpow(a, n / 2, p);  return (t * t) % p;}
ll modinv(ll a, ll m) {	if(m==0)return (ll)1;	ll b = m, u = 1, v = 0;	while (b) {		ll t = a / b;		a -= t * b; swap(a, b);		u -= t * v; swap(u, v);	}	u %= m;	if (u < 0) u += m;	return u;}
const int MAXCOMB=510000;
ll MODCOMB = 998244353;
ll fac[MAXCOMB], finv[MAXCOMB], inv[MAXCOMB]; 
void COMinit() {	fac[0] = fac[1] = 1;	finv[0] = finv[1] = 1;	inv[1] = 1;	for (int i = 2; i < MAXCOMB; i++) {		fac[i] = fac[i - 1] * i % MODCOMB;		inv[i] = MODCOMB - inv[MODCOMB%i] * (MODCOMB / i) % MODCOMB;		finv[i] = finv[i - 1] * inv[i] % MODCOMB;	}}
ll COM(ll n, ll k) {	if (n < k) return 0;	if (n < 0 || k < 0) return 0;	return fac[n] * (finv[k] * finv[n - k] % MODCOMB) % MODCOMB;}
ll com(ll n,ll m){   if(n<m || n<=0 ||m<0){		return 0;	}	if( m==0 || n==m){		return 1;	}	ll k=1;	for(ll i=1;i<=m;i++){       k*=(n-i+1); 	   k%=MODCOMB;	   k*=modinv(i,MODCOMB);	   k%=MODCOMB;	}	return k;}
ll rad(ll u, ll p){ ll cnt=0;	while(u%p==0){		u/=p;		cnt++;	}	return cnt;}


template <typename T> inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false));}
template <typename T> inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false));}
void fail() { cout << "-1\n"; exit(0); } void no() { cout << "No\n"; exit(0); } void yes() { cout << "Yes\n"; exit(0); }
template<class T> void er(T a) { cout << a << '\n'; exit(0); }
int dx[] = { 1,0,-1,0,1,1,-1,-1,0 }; int dy[] = { 0,1,0,-1,1,-1,1,-1,0 };

class UnionFind
{
public:

	UnionFind() = default;

	explicit UnionFind(size_t n)
		: m_parentsOrSize(n, -1) {}

	int find(int i)
	{
		if (m_parentsOrSize[i] < 0)
		{
			return i;
		}

		return (m_parentsOrSize[i] = find(m_parentsOrSize[i]));
	}

	void merge(int a, int b)
	{
		a = find(a);
		b = find(b);

		if (a != b)
		{
			if (-m_parentsOrSize[a] < -m_parentsOrSize[b])
			{
				std::swap(a, b);
			}

			m_parentsOrSize[a] += m_parentsOrSize[b];
			m_parentsOrSize[b] = a;
		}
	}

	bool connected(int a, int b)
	{
		return (find(a) == find(b));
	}

	int size(int i)
	{
		return -m_parentsOrSize[find(i)];
	}

private:
	std::vector<int> m_parentsOrSize;
};


ll Random(ll upper) {
    static mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, upper);
    return dist(engine);
}

vi random_int(ll upper, int n){ //[1,upper]の整数をランダムにn個生成
    vi vec(n);
    rep(i,n){
        vec[i]=Random(upper);
    }
    return vec;
}

vi random_permutation(int n){ //1~nの順列をランダムに生成
    vi vec(n);
    rep(i,n){
        vec[i]=i+1;
    }
    mt19937_64 get_rand_mt; 
    shuffle( vec.begin(), vec.end(), get_rand_mt );
    return vec;
}

vs random_string(int len, int n){ //長さlenの英小文字列をランダムにn個生成
    vs vec(n);
    rep(i,n){
        int nlen=Random(len);
        if(nlen==1)nlen++;
        string s(nlen,'a');
        rep(j,nlen){
            s[j]=Random(26)-1+'a';
        }
        vec[i]=s;
    }
    return vec;
}

vs random_numstr(int len, int n){ //長さlenの10進数の値をランダムにn個生成
    vs vec(n);
    rep(i,n){
        string s(len,'a');
        rep(j,len){
            s[j]=Random(10)-1+'0';
        }
        vec[i]=s;
    }
    return vec;
}

vd random_double(double upper, int n){ //0.0~(double)upperの実数をランダムにn個生成(桁数によって桁落ちにより精度の高いrandomになっていない場合がある)
    vd vec(n);
    rep(i,n){
        double u1=(double)Random(1000000000);
        double u2=(double)Random(1000000000);
        if(u1>=u2)swap(u1,u2);
        vec[i]=u1/u2*upper;
    }
    return vec;
}

//辺に情報を持たせるときはpairなどで({終点,重み}など)
vvi random_graph(int n, int m){ //n頂点m辺の単純無向グラフ(連結とは限らない)をランダムに作成
    vector<set<int>> check(n);
    vvi graph(n);
    int cnt=0;
    while(cnt<m){
        int a=Random(n);
        int b=Random(n);
        a--;
        b--;
        if(a==b) continue;
        if(check[a].count(b)) continue;
        check[a].insert(b);
        check[b].insert(a);
        graph[a].push_back(b);
        graph[b].push_back(a);
        cnt++;
    }
    return graph;
}

vvi random_directedgraph(int n, int m){ //n頂点m辺の単純有向グラフをランダムに作成
    vector<set<int>> check(n);
    vvi graph(n);
    int cnt=0;
    while(cnt<m){
        int a=Random(n);
        int b=Random(n);
        a--;
        b--;
        if(a==b) continue;
        if(check[a].count(b)) continue;
        check[a].insert(b);
        graph[a].push_back(b);
        cnt++;
    }
    return graph;
}

vvi random_tree(int n){ //n頂点の木をランダムに作成
    UnionFind uf(n);
    vvi graph(n);
    int cnt=0;
    while(cnt<n-1){
        int a=Random(n);
        int b=Random(n);
        a--;
        b--;
        if(a==b)continue;
        if(uf.connected(a,b))continue;
        uf.merge(a,b);
        graph[a].push_back(b);
        graph[b].push_back(a);
        cnt++;
    }
    return graph;
}

vvi random_Cgraph(int n, int m){ //n頂点m辺の単純無向グラフ(連結である)をランダムに作成
    vector<set<int>> check(n);
    vvi graph= random_tree(n);
    rep(i,n){
        rep(j,graph[i].size()){
            check[i].insert(graph[i][j]);
        }
    }
    int cnt=0;
    while(cnt<m-n+1){
        int a=Random(n);
        int b=Random(n);
        a--;
        b--;
        if(a==b) continue;
        if(check[a].count(b)) continue;
        check[a].insert(b);
        check[b].insert(a);
        graph[a].push_back(b);
        graph[b].push_back(a);
        cnt++;
    }
    return graph;
}

vvi random_Cdirectedgraph(int n, int m){ //n頂点m辺の単純有向グラフ(連結である)をランダムに作成
    vector<set<int>> check(n);
    vvi graph= random_tree(n);
    rep(i,n){
        rep(j,graph[i].size()){
            check[i].insert(graph[i][j]);
        }
    }
    int cnt=0;
    while(cnt<m-n+1){
        int a=Random(n);
        int b=Random(n);
        a--;
        b--;
        if(a==b) continue;
        if(check[a].count(b)) continue;
        check[a].insert(b);
        graph[a].push_back(b);
        cnt++;
    }
    return graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////


ll solve(vs &s){//適切な入力を設定 以下に解答用のコードを書く
    
    clock_t start=clock(); 
//ここにコードを書く



//////
    int finalans = -1;
    clock_t end=clock(); 
    cout<<"time:"<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl; //時間を測りたい時だけ外す
    return finalans;
}

ll solve_jury(vs &s){//確実に正しい解答を作成するコードを書く
return 0;
}

int main(){
    int continue_time; //入力に関する適当なパラメータ(n,m,l)とテストの繰り返し回数
    cin >> continue_time;
    rep(rp,continue_time){
        // ランダムな入力の生成
      int n=500;
      vi a = random_int(100,n);
      rep(i,n){
        int ran=Random(2);
        if(ran==1)a[i]*=-1;
      }
        clock_t start=clock();

    vvi dp(n,vi(n,0)); //[l,r]においてのスコア
    int ans=0;
    rep(i,n-2){
            int j=i+2;
            dp[i][j]=max(0,a[i]+a[i+1]+a[i+2]);
    }
    
    for(int d=6;d<=n;d+=3){
        for(int i=0;i<n-d+1;i++){
            int j=i+d-1;
            vi sdp(d,0); //iからi+rまで見た時のスコア  
            for(int k=0;k<d;k++){
                for(int t=2;k+t<d;t+=3){
                    if(k==0)chmax(sdp[k+t],dp[i][i+t]);
                    else chmax(sdp[k+t],sdp[k-1]+dp[i+k][i+k+t]);
                }
                if(k!=0)chmax(sdp[k],sdp[k-1]+a[i+k]);
                else chmax(sdp[k],a[i]);
            }
            dp[i][j]=sdp[d-1];
        }
    }

    int r=n%3;
    if(r==0)cout<<dp[0][n-1]<<endl;
    if(r==1)cout<<max(dp[0][n-2],dp[1][n-1])<<endl;
    if(r==2)cout<<max(dp[0][n-3],max(dp[1][n-2],dp[2][n-1]))<<endl;

       
        clock_t end=clock();
        cout<<"time:"<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
        
       }
    
            cout<<"AC for all test cases."<<endl;
    return 0;
}