#include <bits/stdc++.h>
#define ALL(v) v.begin(), v.end()
#define MAX 510000
#define rrep(i, n) for(ll i = 0; i < (ll)(n); i++)
#define rep(i, n) for(ll i = 1; i <= (ll)(n); i++)
#define dcout cout<<fixed<<setprecision(15);
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long int  ll;
typedef pair<ll, ll> P;


constexpr ll inf = 1LL << 60;

template< typename S, typename T >
inline void chmax(S &a, const T &b) { if(a < b) a = b; }
 
template< typename S, typename T >
inline void chmin(S &a, const T &b) { if(a > b) a = b; }
 



////////////////////////////////////////////////////////////////////


inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
long long extGcd(long long a, long long b, long long &p, long long &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    long long d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;  
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<long long, long long> Ch(long long b1, long long m1, long long b2, long long m2) {
  long long p, q;
  long long d = extGcd(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
  if ((b2 - b1) % d != 0) return make_pair(0, -1);
  long long m = m1 * (m2/d); // lcm of (m1, m2)
  long long tmp = (b2 - b1) / d * p % (m2/d);
  long long r = mod(b1 + m1 * tmp, m);
  return make_pair(r, m);
}

ll modpow(ll a, ll n, ll p) {
	if(n==0) return (ll)1;
  if (n == 1) return a % p;
  if (n % 2 == 1) return (a * modpow(a, n - 1, p)) % p;
  ll t = modpow(a, n / 2, p);
  return (t * t) % p;
}


int main(){	
 ios::sync_with_stdio(false);


int cnt=0;

for(int a1=0;a1<=1;a1++){
for(int a2=0;a2<=3;a2++){
for(int a3=0;a3<=7;a3++){
for(int a4=0;a4<=11;a4++){
for(int a5=0;a5<=15;a5++){
for(int a6=0;a6<=23;a6++){
	int a7=-2;

int fin=0;
int v=-1;
for(int t=0;t<=47;t++){
	
if(t%2!=a1 && t%4!=a2 && t%8!=a3 && t%12!=a4 && t%16!=a5 && t%24!=a6){
	if(v==-1)v=t;
	else{fin=1;
	break;}
}
if(t==47)a7=v;
}
if(fin)continue;



cout<<a1<<" "<<a2<<" "<<a3<<" "<<a4<<" "<<a5<<" "<<a6<<" "<<a7<<endl;
cnt++;

//
pair<ll,ll> pr1=Ch(-modpow(2,a1,3),3,-modpow(2,a2,5),5);
pair<ll,ll> pr2=Ch(pr1.first,pr1.second,-modpow(2,a3,17),17);
pair<ll,ll> pr3=Ch(pr2.first,pr2.second,-modpow(2,a4,13),13);
pair<ll,ll> pr4=Ch(pr3.first,pr3.second,-modpow(2,a5,257),257);
pair<ll,ll> pr5=Ch(pr4.first,pr4.second,-modpow(2,a6,241),241);
pair<ll,ll> pr6=Ch(pr5.first,pr5.second,-modpow(2,a7,97),97);
ll v1=pr6.first;
ll v2=pr6.second;

cout<<v1<<" "<<v2<<endl;

ll prime=1;
for(ll i=2;i*i<=v1;i++){
if(v1%i==0){prime=0; break;}
}

if(prime)cout<<"PRIME!!"<<endl;

}
}
}
}
}
}
return 0;
}





