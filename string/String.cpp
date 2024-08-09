//目次
/*
文字変換,部分文字列の取得,文字削除など
配列nex(i文字目以降で文字#が出現する最小の添字j)
Z-algorithm
LIS(最長増加部分列)
Rolling Hash

*/

//大小文字の変換
 char c = 'c';
 if (islower(c)) c = c - 32;
 cout << c << endl;		// 小文字から大文字への変換(逆は32を足す)

string s = "str";
transform(s.begin(), s.end(), s.begin(), ::toupper);
cout << s << endl;		// まとめて変換(::tolowerが逆操作)

//数値型から文字列への変換
int number = 100;
  string s = to_string(number);

//文字列からint型への変換
string s = "100";
  int n = stoi(s); //int型
	uint64_t tt = stoull(t); // unsigned long long 型に変換
//(他はstoll,stodなど)

  //二進数の場合
  string s = "0111";
    int ss = std::stoi(s, nullptr, 2); // int 型に変換 ss=7(int)

//部分文字列の取得
string s="abcde";
s=s.substr(1,2);//sの(0-indexedで)1文字目から2文字だけ取り出したstringを返す -> s="bc"

//先頭と末尾の削除
s.pop_back(); // 末尾の要素を削除
s.erase(s.begin()); // 先頭の要素を削除

//連続成分ごとに分割する
vector<pair<char,int>> string_partition(string s){
    vector<pair<char,int>> res;
    int cnt=1;
    char now=s[0];
    for(int i=1;i<s.size();i++){
        if(s[i]==now) cnt++;
        else{
            res.push_back(make_pair(now,cnt));
            now=s[i];
            cnt=1;
        }
    }
    res.push_back(make_pair(now,cnt));
    return res;
}


//配列nex: nex[i][c]は、文字列Sのi文字目以降で、文字cが出現する最小の添字(存在しない場合は N)
//Sを受け取って vvi型のnexを返す関数
//英小文字用である。大文字なら直さないとSEとなる
vector<vector<int> > calcNext(const string &S) {
    int n = (int)S.size();
    vector<vector<int> > res(n+1, vector<int>(26, n));
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) res[i][j] = res[i+1][j];
        res[i][S[i]-'a'] = i;
    }
    return res;
}


//Z-algorithm
/*
次の性質を満たすZ[i]という配列を生成する
___ 文字列 S[0]S[1]...S[N-1] について、S と S[i:] の最長共通接頭辞の長さを Z[i] とする ___

方針
1. 基本は各iごとにZ[i]がいくつになるのか伸ばしながら調べる
2. 一致しなくなってそれ以上伸ばせなくなったら，その一致している範囲について Z値をコピー
3. ただし，1 回目の登場時の右端が収まっていない (一致していたり，はみ出したりしている) 場合には，そのままコピーできないので，iをその位置に移動させて，探索を再開します．
4. その際，すでに一致することがわかっている部分については比較処理を飛ばす
*/
//実装例
vector<int> Z_algorithm(string S){
  vector<int> Z(S.size());
  Z[0] = S.size();
  int i = 1, j = 0;
  while(i < S.size()){
      while(i + j < S.size() && S[j] == S[i + j]) j++;
      Z[i] = j;

      if(j == 0){
          i++;
          continue;
      }
      int k = 1;
      while(k < j && k + Z[k] < j){
          Z[i + k] = Z[k];
          k++;
      }
      i += k;
      j -= k;
  }
return Z;
}


//LIS(最長増加部分列)


//Rolling Hash
/*
高速に文字列検索を行うための方法(O(n+m))

m文字の文字列Aに対し、互いに素な基数(base = b)とmod p を取って、
hash(A) = (A_0*b^(m-1) + A_1*b^(m-2) + ... + A_(m-1)*b^0) mod p
とする。(ここでA_iは、Aのi文字目に対応したある値とする 例えばA_i-'a'など)

hが十分に大きい時はハッシュ値の衝突はほとんど起こりにくいと考えられる。
→文字列の一致検証がO(n)からO(1)に高速化できる

- pは2^61-1を用いると安全らしい
- 

*/
//実装例
//baseはstruct内で決める
//modはusingに書いてある
class RollingHash {
    static const uint64_t mod = (1ull << 61ull) - 1;
    vector<uint64_t> power;
    const uint64_t base;

    //1以上mod - 1以下のランダムなbaseを生成
    static inline uint64_t generate_base() {
        mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint64_t> rand((uint64_t)1,(uint64_t)mod - 1);
        return rand(engine);
    }

    //足し算
    static inline uint64_t add(uint64_t a, uint64_t b) {
        if((a += b) >= mod) a -= mod;
        return a;
    }

    //掛け算（__uint128_tを使用）
    static inline uint64_t mul(uint64_t a, uint64_t b) {
        __uint128_t c = (__uint128_t) a * b;
        return add(c >> 61,c & mod);
    }

    inline void expand(size_t sz) {
        if(power.size() < sz + 1) {
            int pre_sz = (int)power.size();
            power.resize(sz + 1);
            for(int i = pre_sz - 1;i < sz;i++) {
                power.at(i + 1) = mul(power.at(i),base);
            }
        }
    }

public:

    explicit RollingHash(uint64_t base = generate_base()) : base(base),power{1} {}

    //文字列Sのハッシュを返す
    vector<uint64_t> build(string S) {
        vector<uint64_t> hash(S.size() + 1);
        for (int i = 0; i < S.size(); i++) {
            hash.at(i + 1) = add(mul(hash.at(i),base),S.at(i));
        }
        return hash;
    }

    //hashの[l,r)のハッシュ値を返す
    uint64_t get(vector<uint64_t> &hash,int l,int r) {
        expand(r - l);
        return add(hash.at(r),mod - mul(hash.at(l),power.at(r - l)));
    }

    //ハッシュ値h1と長さh2lenのハッシュ値h2を結合
    uint64_t connect(uint64_t h1, uint64_t h2, size_t h2len) {
        expand(h2len);
        return add(mul(h1, power.at(h2len)), h2);
    }

    //hash1の区間[l1,r1)とhash2の区間[l2,r2)のlcp（最長共通接頭辞）の長さを返す
    int LCP(vector<uint64_t> &hash1,int l1,int r1,vector<uint64_t> &hash2,int l2,int r2) {
        int len = min(r1 - l1,r2 - l2);
        int ok = 0;
        int ng = len + 1;
        int mid;
        while(ng - ok > 1) {
            mid = (ok + ng) / 2;
            if(get(hash1,l1,l1 + mid) == get(hash2,l2,l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

string T,P;
    cin >> T >> P;
    if(T.size() < P.size()) return 0;
    RollingHash rh; 
    vector<uint64_t> t = rh.build(T); //ハッシュテーブルを作って返す
    vector<uint64_t> p = rh.build(P);
    uint64_t cnt = rh.get(p,0,P.size()); //
    for(int i = 0;i < T.size() - P.size() + 1;i++) {
        if(rh.get(t,i,i + P.size()) == cnt) cout << i << endl;
            }


string s="strangeorange";
string t="strongrange";
RollingHash rh; //準備
vector<uint64_t> t = rh.build(T); //ハッシュテーブルを作って返す(rhは他の文字列に対しても繰り返し使う)
rh.get(p,l,r) //ハッシュテーブルpに対して、区間[l,r)のハッシュ値を求めるO(N)
rh.connect(h1,h2,h2len) //ハッシュテーブルh1と、長さh2lenのハッシュテーブルh2を結合する(O(1))
LCP(h1,l1,r1,h2,l2,r2) //ハッシュテーブルh1の元の文字列の部分区間区間[l1,r1)と、ハッシュテーブルh2の元の文字列の部分区間区間[l2.r2)の最長共通接頭辞の長さを求める(O(logn))
