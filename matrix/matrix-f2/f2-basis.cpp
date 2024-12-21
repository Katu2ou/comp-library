//基底を見つける
// Aに対して，xor基底の組を一つ返す. (掃き出し法をする) 階段行列を得る

template<typename T>
vector<T> get_basis(vector<T> &A){
    vector<T> basis;
    for(T e: A){
        for(T b: basis)
            chmin(e,e^b);
        if(e)
            basis.push_back(e);
    }
    return basis;
}


// 簡約行列を得る (msbが他の要素で立っていないようなもの)

template<typename T>
vector<T> get_good_basis(vector<T> &A){
    vector<T> basis;
    for(T e: A){
        for(T b: basis)
            if((e ^ b) < e)
                e ^= b;
        for (auto &&b : basis)
            if((e ^ b) < b)
                b ^= e;
        if (e)
            basis.push_back(e);
    }
    return basis;
}