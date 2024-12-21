//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) rep2(i, 0, n)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)
#define all(...) std::begin(__VA_ARGS__), std::end(__VA_ARGS__)
#define rall(...) std::rbegin(__VA_ARGS__), std::rend(__VA_ARGS__)
#define CLR(a, b) memset((a), (b), sizeof(a))
#define DUMP(x) cout << #x << " = " << (x) << endl;
#define INF (long long)1001001001001001001
#define inf 1001001000
#define MOD 998244353
#define MOD1 1000000007
#define PI 3.14159265358979
#define epsilon 1e-12
#define fcout cout << fixed << setprecision(12)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define SORT(x) sort(x.begin(),x.end())
#define ERASE(x) x.erase(unique(x.begin(),x.end()),x.end())

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vd = vector<double>;
using vld = vector<long double>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpil = vector<pair<int, long long>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvd = vector<vector<double>>;
using vvld = vector<vector<long double>>;
using vvb = vector<vector<bool>>;
using vvpii = vector<vector<pair<int,int>>>;
using vvpll = vector<vector<pair<long long,long long>>>;
using vvvi = vector<vector<vector<int>>>;
using vvvl = vector<vector<vector<long long>>>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using LL = __int128_t;

ll gcd(ll x, ll y) {if (x == 0) return y;	return gcd(y%x, x);} 
ll lcm(ll x, ll y) { __int128_t xx,yy; xx=x; yy=y; __int128_t ans=xx * yy / gcd(x, y); ll ans2=ans; return ans2; }
template<typename T>
T POW(T x, ll n){T ret=1;	while(n>0){		if(n&1) ret=ret*x;		x=x*x;		n>>=1;	}	return ret;}
template<typename T>
T modpow(T a, ll n, T p) {	if(n==0) return (T)1;  if (n == 1) return a % p;  if (n % 2 == 1) return (a * modpow(a, n - 1, p)) % p;  T t = modpow(a, n / 2, p);  return (t * t) % p;}
template<typename T>
T modinv(T a, T m) {	if(m==0)return (T)1;	T b = m, u = 1, v = 0;	while (b) {		T t = a / b;		a -= t * b; swap(a, b);		u -= t * v; swap(u, v);	}	u %= m;	if (u < 0) u += m;	return u;}
template<typename T>
T REM(T a, T b){ return (a % b + b) % b;}
template<typename T>
T QUO(T a, T b){ return (a - REM(a, b)) / b;}
ll rand_int(ll l, ll r) { //[l, r]
	static mt19937_64 gen;
	return uniform_int_distribution<ll>(l, r)(gen);
}
/* 
const int MAXCOMB=510000;
ll MODCOMB = 998244353;
ll fac[MAXCOMB], finv[MAXCOMB], inv[MAXCOMB]; 
void COMinit() {	fac[0] = fac[1] = 1;	finv[0] = finv[1] = 1;	inv[1] = 1;	for (int i = 2; i < MAXCOMB; i++) {		fac[i] = fac[i - 1] * i % MODCOMB;		inv[i] = MODCOMB - inv[MODCOMB%i] * (MODCOMB / i) % MODCOMB;		finv[i] = finv[i - 1] * inv[i] % MODCOMB;	}}
ll COM(ll n, ll k) {	if (n < k) return 0;	if (n < 0 || k < 0) return 0;	return fac[n] * (finv[k] * finv[n - k] % MODCOMB) % MODCOMB;}
ll com(ll n,ll m){   if(n<m || n<=0 ||m<0){		return 0;	}	if( m==0 || n==m){		return 1;	}	ll k=1;	for(ll i=1;i<=m;i++){       k*=(n-i+1); 	   k%=MODCOMB;	   k*=modinv(i,MODCOMB);	   k%=MODCOMB;	}	return k;}
*/
/*
const int MAXCOMB=510000;
std::vector<mint> FAC(MAXCOMB), FINV(MAXCOMB), INV(MAXCOMB);
void COMinit() {FAC[0] = FAC[1] = 1;FINV[0] = FINV[1] = 1;INV[1] = 1;for (int i = 2; i < MAXCOMB; i++) {FAC[i] = FAC[i - 1] * i;INV[i] = mint(0) - INV[mint::mod() % i] * (mint::mod() / i);FINV[i] = FINV[i - 1] * INV[i];}}
mint COM(int n, int k) {if (n < k) return 0;if (n < 0 || k < 0) return 0;return FAC[n] * FINV[k] * FINV[n - k];}
*/

template <typename T> inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false));}
template <typename T> inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false));}
template <class T> T BS(vector<T> &vec, T key) {return lower_bound(vec.begin(), vec.end(), key) - vec.begin();}
template<class T> pair<T,T> RangeBS(vector<T> &vec, T lowv, T highv){auto itr_l = lower_bound(vec.begin(), vec.end(), lowv); auto itr_r = upper_bound(vec.begin(), vec.end(), highv); return make_pair(distance(vec.begin(), itr_l), distance(vec.begin(), itr_r)-1);}
void fail() { cout << "-1\n"; exit(0); } void no() { cout << "No\n"; exit(0); } void yes() { cout << "Yes\n"; exit(0); }
template<class T> void er(T a) { cout << a << '\n'; exit(0); }
int dx[] = { 1,0,-1,0,1,1,-1,-1 }; int dy[] = { 0,1,0,-1,1,-1,1,-1};
bool range_in(int i, int j, int h, int w){ if(i<0 || j<0 || i>=h || j>=w) return false; return true;} 
int bitcount(int n){n=(n&0x55555555)+(n>>1&0x55555555); n=(n&0x33333333)+(n>>2&0x33333333); n=(n&0x0f0f0f0f)+(n>>4&0x0f0f0f0f); n=(n&0x00ff00ff)+(n>>8&0x00ff00ff); n=(n&0x0000ffff)+(n>>16&0x0000ffff); return n;}

//////////////////////////////////////////////////////////////////////////////////////////

#define MEASURE_TIME(block) { \
    auto start = std::chrono::high_resolution_clock::now(); \
    block \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); \
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl; \
}

class Xoroshiro128Plus {
private:
    uint64_t s[2];

    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

public:
    Xoroshiro128Plus(uint64_t seed1, uint64_t seed2) {
        s[0] = seed1;
        s[1] = seed2;
    }

    uint64_t next() {
        const uint64_t s0 = s[0];
        uint64_t s1 = s[1];
        const uint64_t result = s0 + s1;

        s1 ^= s0;
        s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
        s[1] = rotl(s1, 36);

        return result;
    }

    int range(int l, int r) {
        return l + (next() % (r - l + 1));
    }
};


int compare = 0;
int Kth_small(vector<int> &perm, int k, int l, int r){
    int pivot = rand_int(l,r);
    int lcnt = 0;
    int lind = l;

    swap(perm[pivot],perm[r]);
    for(int i=l;i<=r-1;i++){
        compare++;
        if(perm[i] <= perm[r]){
            swap(perm[lind],perm[i]);
            lind++;
            lcnt++;
        }
    }
    swap(perm[lind],perm[r]);
    // cout<<"AAA:"<<l<<" "<<r<<" "<<k<<" "<<perm[lind]<<endl;
    // for(int i=l;i<=r;i++){
    //     cout<<perm[i]<<" ";
    // }
    // cout<<endl;
    if(lcnt==k-1){
        return perm[lind];
    }
    if(lcnt>k-1){
        return Kth_small(perm,k,l,l+lcnt-1);
    }
    else{
        return Kth_small(perm,k-lcnt-1,l+lcnt+1,r);
    }
}

signed main(){
    int n;
    cin>>n;
    vector<int> perm;
    for(int i=0;i<n;i++){
        perm.push_back(i);
    }
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    int maxcnt = 0;
    double time = 0.0;
    double mintime = 100.0;
    double maxtime = 0.0;
    int iteration = 100;
     shuffle(all(perm),engine);
         int k = (n+1)/2;
    rep(t,iteration){
        vi base = perm;
        clock_t start = clock();
            int u = Kth_small(base,k,0,n-1);
        clock_t end = clock();
        double nowtime = double(end - start) / CLOCKS_PER_SEC;
        chmin(mintime,nowtime);
        chmax(maxtime,nowtime);
        time += nowtime;
        //cout<<"time: "<<nowtime<<endl;
    }
    cout<<"average: "<<time/iteration<<endl;
    cout<<"min: "<<mintime<<endl;
    cout<<"max: "<<maxtime<<endl;
    
}

