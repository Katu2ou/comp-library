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


template<typename T>
T dgt(T b, T n){ T cnt=0; while(n){ cnt++; n/=b;} return cnt;}
ll gcd(ll x, ll y) {	if (x == 0) return y;	return gcd(y%x, x);} ll lcm(ll x, ll y) { __int128_t xx,yy; xx=x; yy=y; __int128_t ans=xx * yy / gcd(x, y); ll ans2=ans; return ans; }
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
int dx[] = { 1,1,0,-1,-1,-1,0,1}; int dy[] = { 0,1,1,1,0,-1,-1,-1 };
bool range_in(int i, int j, int h, int w){ if(i<0 || j<0 || i>=h || j>=w) return false; return true;} 
int bitcount(int n){n=(n&0x55555555)+(n>>1&0x55555555); n=(n&0x33333333)+(n>>2&0x33333333); n=(n&0x0f0f0f0f)+(n>>4&0x0f0f0f0f); n=(n&0x00ff00ff)+(n>>8&0x00ff00ff); n=(n&0x0000ffff)+(n>>16&0x0000ffff); return n;}

template <typename T, const T id>
class convex_hull_trick {
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
        ~node() {
            if (lch) delete lch;
            if (rch) delete rch;
        }
    };

private:
    const int n;
    const vector<T> pos;
    node *root;

public:
    convex_hull_trick(const vector<T>& pos_) : n(pos_.size()), pos(pos_), root(nullptr) {}
    ~convex_hull_trick() {
        if (root) delete root;
    }
    void insert(T a, T b) {
        line l(a, b);
        root = modify(root, 0, n - 1, l);
    }
    T get(T x) const {
        int t = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
        assert(t < n && pos[t] == x);
        return sub(root, 0, n - 1, t);
    }

private:
    node* modify(node *p, int lb, int ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(pos[lb]) >= l.get(pos[lb]) && p->l.get(pos[ub]) >= l.get(pos[ub])) return p;
        if (p->l.get(pos[lb]) <= l.get(pos[lb]) && p->l.get(pos[ub]) <= l.get(pos[ub])) {
            p->l = l;
            return p;
        }
        int c = (lb + ub) / 2;
        if (p->l.get(pos[c]) < l.get(pos[c])) swap(p->l, l);
        if (p->l.get(pos[lb]) <= l.get(pos[lb]))
            p->lch = modify(p->lch, lb, c, l);
        else
            p->rch = modify(p->rch, c + 1, ub, l);
        return p;
    }
    T sub(node *p, int lb, int ub, int t) const {
        if (!p) return id;
        if (ub - lb == 0) return p->l.get(pos[t]);
        int c = (lb + ub) / 2;
        if (t <= c) return max(p->l.get(pos[t]), sub(p->lch, lb, c, t));
        return max(p->l.get(pos[t]), sub(p->rch, c + 1, ub, t));
    }
};

void solve(int &FIN){
    vi b;
     convex_hull_trick<int,int> a(b);
     a.insert(2,3);
     cout<<a.get(1)<<endl;

}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
    int FIN=0;
	while(1){
        solve(FIN);
        if(FIN)return 0;
    }
}