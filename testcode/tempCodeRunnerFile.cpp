#include <bits/stdc++.h>
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
#define MOD1 1000000007
#define PI 3.14159265358979
#define Dval 1e-12
#define fcout cout << fixed << setprecision(12)
#define Mp make_pair
#define pb push_back
#define fi first
#define se second
#define SORT(x) sort(x.begin(),x.end())
#define ERASE(x) x.erase(unique(x.begin(),x.end()),x.end())
#define POSL(x,v) (lower_bound(x.begin(),x.end(),v)-x.begin())
#define POSU(x,v) (upper_bound(x.begin(),x.end(),v)-x.begin())

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vd = vector<double>;
using vld = vector<long double>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpil = vector<pair<int, long long>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvd = vector<vector<double>>;
using vvld = vector<vector<long double>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvpii = vector<vector<pair<int,int>>>;
using vvpll = vector<vector<pair<long long,long long>>>;
using vvvi = vector<vector<vector<int>>>;
using vvvl = vector<vector<vector<long long>>>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using LL = __int128_t;
using mint = atcoder::modint998244353;
using vmint = vector<mint>;
using vvmint = vector<vector<mint>>;
using vvvmint = vector<vector<vector<mint>>>;

template<typename T>
T dgt(T b, T n){ T cnt=0; while(n){ cnt++; n/=b;} return cnt;}
ll gcd(ll x, ll y) {	if (x == 0) return y;	return gcd(y%x, x);} ll lcm(ll x, ll y) { __int128_t xx,yy; xx=x; yy=y; __int128_t ans=xx * yy / gcd(x, y); ll ans2=ans; return ans; }
template<typename T>
T POW(T x, T n){T ret=1;	while(n>0){		if(n&1) ret=ret*x;		x=x*x;		n>>=1;	}	return ret;}
template<typename T>
T modpow(T a, T n, T p) {	if(n==0) return (T)1;  if (n == 1) return a % p;  if (n % 2 == 1) return (a * modpow(a, n - 1, p)) % p;  T t = modpow(a, n / 2, p);  return (t * t) % p;}
mint Modpow(mint a, ll n){ mint ret=1; while(n>0){ if(n&1) ret*=a; a*=a; n>>=1;}	return ret;}
template<typename T>
T modinv(T a, T m) {	if(m==0)return (T)1;	T b = m, u = 1, v = 0;	while (b) {		T t = a / b;		a -= t * b; swap(a, b);		u -= t * v; swap(u, v);	}	u %= m;	if (u < 0) u += m;	return u;}
template<typename T>
T REM(T a, T b){ return (a % b + b) % b;}
template<typename T>
T QUO(T a, T b){ return (a - REM(a, b)) / b;}
const int MAXCOMB=510000;
ll MODCOMB = 998244353;
ll fac[MAXCOMB], finv[MAXCOMB], inv[MAXCOMB]; 
void COMinit() {	fac[0] = fac[1] = 1;	finv[0] = finv[1] = 1;	inv[1] = 1;	for (int i = 2; i < MAXCOMB; i++) {		fac[i] = fac[i - 1] * i % MODCOMB;		inv[i] = MODCOMB - inv[MODCOMB%i] * (MODCOMB / i) % MODCOMB;		finv[i] = finv[i - 1] * inv[i] % MODCOMB;	}}
ll COM(ll n, ll k) {	if (n < k) return 0;	if (n < 0 || k < 0) return 0;	return fac[n] * (finv[k] * finv[n - k] % MODCOMB) % MODCOMB;}
ll com(ll n,ll m){   if(n<m || n<=0 ||m<0){		return 0;	}	if( m==0 || n==m){		return 1;	}	ll k=1;	for(ll i=1;i<=m;i++){       k*=(n-i+1); 	   k%=MODCOMB;	   k*=modinv(i,MODCOMB);	   k%=MODCOMB;	}	return k;}
ll rad(ll u, ll p){ ll cnt=0;	while(u%p==0){		u/=p;		cnt++;	}	return cnt;}

template <typename T> inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false));}
template <typename T> inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false));}
template <class T> T BS(vector<T> &vec, T key) { auto itr = lower_bound(vec.begin(), vec.end(), key); return distance(vec.begin(), itr); }
template<class T> pair<T,T> RangeBS(vector<T> &vec, T lowv, T highv){auto itr_l = lower_bound(vec.begin(), vec.end(), lowv); auto itr_r = upper_bound(vec.begin(), vec.end(), highv); return make_pair(distance(vec.begin(), itr_l), distance(vec.begin(), itr_r)-1);}
void fail() { cout << "-1\n"; exit(0); } void no() { cout << "No\n"; exit(0); } void yes() { cout << "Yes\n"; exit(0); }
template<class T> void er(T a) { cout << a << '\n'; exit(0); }
int dx[] = { 1,0,-1,0,1,1,-1,-1,0 }; int dy[] = { 0,1,0,-1,1,-1,1,-1,0 };
int bitcount(int n){n=(n&0x55555555)+(n>>1&0x55555555); n=(n&0x33333333)+(n>>2&0x33333333); n=(n&0x0f0f0f0f)+(n>>4&0x0f0f0f0f); n=(n&0x00ff00ff)+(n>>8&0x00ff00ff); n=(n&0x0000ffff)+(n>>16&0x0000ffff); return n;}

void solve(){
    ll n;
    cin>>n;
    vl a(n,-1);
    a[0]=0;
    ll val=1;
    rep(i,n){
        if(i==0)continue;
        a[i]=val;
        val*=2;
    }
    rep(i,n){
        if(a[i]>1000000000){
            no();
        }
    }
    cout<<"Yes"<<endl;
    rep(i,n){
        cout<<a[i]<<" ";
    }

}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
	int TT; TT = 1; //cin >> TT;
	while(TT--) solve();
}