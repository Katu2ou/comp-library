// https://qiita.com/izu_nori/items/7810fc2bc0423c8d407f

// アダマール変換 O(n)
// 入力 vector<T> v (長さが2^kであることを仮定)
// 出力 入力が変化したもの vector<T>  Hv*2^k (アダマール変換後のベクトル)
// 2の冪乗倍の影響は考慮していないので，2回適用したら2^kで割らないといけない

template <typename T>
void Hadamard_Transformation(vector<T> v) {
    int n = v.size();
    int sz = n;
    int len = 1;
    while(sz > 1){
        for(int i=0;i<n;i+=2*len){
            for(int j=i;j<i+len;j++){
                mint v1=v[j];
                mint v2=v[j+len];
                v[j] = v1+v2;
                v[j+len]=v1-v2;
            }
        }
        assert(sz/2*2==sz);
        sz/=2;
        len*=2;
    }
    return;
}


// xor畳み込み O(nlogn)
// 入力 vector<T> v,u,k (vとuの長さが2^kであることを仮定)
// 出力 vector<T>  v (vとuのxor畳み込み)

template <typename T>
vector<T> xorConvolution(vector<T> v, vector<T> u, int k){
    Hadamard_Transformation(v);
    Hadamard_Transformation(u);
    for(int i=0;i<v.size();i++){
        v[i]*=u[i];
    }
    Hadamard_Transformation(v);
    for(int i=0;i<v.size();i++){
        v[i] >>=k; 
    }
    return v;
}
