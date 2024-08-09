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
#define Dval 1e-12
#define fcout cout << fixed << setprecision(12)
#define Mp make_pair
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
using vpil = vector<pair<int, long long>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvd = vector<vector<double>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvpii = vector<vector<pair<int,int>>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using LL = __int128_t;
using mint = atcoder::modint998244353;

ll dgt(ll b, ll n){ ll cnt=0; while(n){ cnt++; n/=b;} return cnt;}
ll gcd(ll x, ll y) {	if (x == 0) return y;	return gcd(y%x, x);} ll lcm(ll x, ll y) { return x * y / gcd(x, y); }
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
template <class T> T BS(vector<T> &vec, T key) { auto itr = lower_bound(vec.begin(), vec.end(), key); return distance(vec.begin(), itr); }
template<class T> pair<T,T> RangeBS(vector<T> &vec, T lowv, T highv){auto itr_l = lower_bound(vec.begin(), vec.end(), lowv); auto itr_r = upper_bound(vec.begin(), vec.end(), highv); return make_pair(distance(vec.begin(), itr_l), distance(vec.begin(), itr_r)-1);}
void fail() { cout << "-1\n"; exit(0); } void no() { cout << "No\n"; exit(0); } void yes() { cout << "Yes\n"; exit(0); }
template<class T> void er(T a) { cout << a << '\n'; exit(0); }
int dx[] = { 1,0,-1,0,1,1,-1,-1,0 }; int dy[] = { 0,1,0,-1,1,-1,1,-1,0 };

vector<ll> Eratosthenes(int N) {
    vector<int> isprime(N+1, 1);
    vl pr;
    isprime[1] = 0;
    
    for (ll p = 2; p <= N; ++p) {
        if (isprime[p] != 1) continue;
        for (ll q = p * p; q <= N; q += p) {
            if(isprime[q]==1) isprime[q] = p;
        }
    }

    for(int p=2;p<=N;p++){
        if(isprime[p]==1) pr.pb(p);
        
    }
    //cout<<pr.size()<<endl;
    return pr;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;
    cin>>n;
    if(n==2){
        cout<<4<<" "<<7<<endl;
        cout<<23<<" "<<10<<endl;
        return 0;
    }

    vl plist=Eratosthenes(5000000);
    //cout<<plist.size()<<endl;
    vvl ans(n,vl(n,0));
    int ind=0;
    int ilm=0;
    int jlm=n-1;
    if(n%2==0)jlm--;
    rep(i,n){
        rep(j,n){
            if((i+j)%2==1)continue;
            ans[i][j]=plist[(i+j)/2+1+504]*plist[(i-ilm+jlm-j)/2];
        }
    }
    rep(i,n){
        rep(j,n){
            if((i+j)%2==0)continue;
            ll val=1;
            if(i>0)val=lcm(val,ans[i-1][j]);
            if(j>0)val=lcm(val,ans[i][j-1]);
            if(i<n-1)val=lcm(val,ans[i+1][j]);
            if(j<n-1)val=lcm(val,ans[i][j+1]);
            ans[i][j]=val+1;
            __int128_t vall=1;
            if(i>0)vall=lcm(vall,ans[i-1][j]);
            if(j>0)vall=lcm(vall,ans[i][j-1]);
            if(i<n-1)vall=lcm(vall,ans[i+1][j]);
            if(j<n-1)vall=lcm(vall,ans[i][j+1]);
            assert(vall+1<=1000000000000000);
        }
    }

    rep(i,n){
        rep(j,n){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }

    map<ll,ll> mp;
    rep(i,n){
        rep(j,n){
            assert(mp[ans[i][j]]==0);
            assert(ans[i][j]<=1000000000000000&&ans[i][j]>=1);
            mp[ans[i][j]]=1;
            // long double lg=0.0;
            // rep(k,4){
            //     if(i+dx[k]<0 || i+dx[k]>=n || j+dy[k]<0 || j+dy[k]>=n)continue;
            //     assert(max(ans[i][j],ans[i+dx[k]][j+dy[k]])%min(ans[i][j],ans[i+dx[k]][j+dy[k]])==1);
            // }
        }
    }

    
    
     
     

        return 0;
}
