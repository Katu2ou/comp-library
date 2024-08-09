//普通の実装(探索)
int BinarySearch(vector<int> vec, int key) {
    // key: 検索対象の値(Rはmax index+1とする)
    T left = 0, right = (T)vec.size(), mid;

    while (left < right) {
        mid = (left + right)/2;
        if (vec[mid] == key) {
            return mid;
        } else if (key < vec[mid]) {
            right = mid;
        } else if (vec[mid] < key) {
			//(左側はmid+1とする)
            left = mid + 1;
        }
    }
    // key が配列の中に見つからない場合
    return -1;
}

//普通の実装(条件を満たす最大(最小)の値を求めるやつ)
int left=-1;//とりうる値のmin-1
int right=l+1;//とりうる値のmax+1
while(right-left>1){
    mid = (left + right)/2;
    if(check(mid))left=mid;//midが条件を満たせば
    else right=mid;//leftもrightもmidにする(mid+1とかにしない)
}
cout<<left<<endl;//leftを出力する
//leftは常に「その値で条件を満たす」ことを表す
//rightは常に「その値で条件を満たさない」ことを表す
//どちらが「条件を満たす方」なのかを考えて最終的な値をleftかrightかで決定する

//lower_bound系
//1. binary_search
binary_search(vec.begin(), vec.end(), key)
//keyがvecの範囲内に含まれていればTrueを、そうでなければFalseを返す

//2. 
lower_bound(vec.begin(), vec.end(), key);
//指定した key 「以上の」要素の内，一番左側の要素の位置（最小のインデックス）をイテレータで返す

upper_bound(vec.begin(), vec.end(), key);

//指定した key 「より大きい」要素の内，一番左側の要素の位置（最小のインデックス）をイテレータで返す

//どちらにおいても、条件を満たす要素が見つからなかった場合は，配列の末尾のイテレータを返します

//使用例
vector<int> vec = {1, 1, 2, 2, 4, 5, 5, 6, 8, 8, 8, 10, 15}; //昇順にソート済み
    size_t len = vec.size();
    int key = 6;

    // 二分探索
    auto iter_lower = lower_bound(vec.begin(), vec.end(), key);
    auto iter_upper = upper_bound(vec.begin(), vec.end(), key);

	//イテレータに対応する要素は*(itr)の形で取得できる
	if(key==*iter_lower) cout << "6は存在する\n";

	//<<<直接indexを得る>>>
    //lindはkey以上の最小の要素のindex(存在しなければvec.size()であり、これを用いてvecにアクセスしてはいけない)
    //uindはkeyより大きい最小の要素のindex(存在しなければvec.size()であり、これを用いてvecにアクセスしてはいけない)
    //lind-1はkey未満の最大の要素のindex(lind=0ならアクセス禁止)
    //uind-1はkey以下の最大の要素のindex(uind=0ならアクセス禁止)
	ll lind = distance(vec.begin(),lower_bound(all(vec),key));
	ll uind = distance(vec.begin(),lower_bound(all(vec),key+1));


    //ライブラリに貼っているもの

    // 広義単調増加なvectorに対してkey以上の値をとる最小の要素のindexを返す
    //(存在しない場合はvec.size()を返す)
    template<class T> 
    T BS(vector<T> &vec, T key){
        auto itr = lower_bound(vec.begin(), vec.end(), key);
        return distance(vec.begin(), itr);
    }

    // 広義単調増加なvectorに対して、lowv以上highv以下の値をとる要素のindexの最小と最大を返す
    //(min=max-1のときは存在しないということ)
    template<class T> 
    pair<T,T> RangeBS(vector<T> &vec, T lowv, T highv){
        auto itr_l = lower_bound(vec.begin(), vec.end(), lowv);
        auto itr_r = upper_bound(vec.begin(), vec.end(), highv);
        return make_pair(distance(vec.begin(), itr_l), distance(vec.begin(), itr_r)-1);
    }



    // インデックスを取得
    long idx_lower = distance(vec.begin(), iter_lower);  // vec[idx_lower] = vec[7] = 6(indexがわかる)
    long idx_upper = distance(vec.begin(), iter_upper);  // vec[idx_upper] = vec[8] = 8(indexがわかる)


    // lower_bound で要素数を数える
    cout << "6 未満の要素数は " << idx_lower << "\n";  // 6 までの要素数 (idx_lower + 1) - 1
    cout << "6 以上の要素数は " << len - idx_lower << "\n";  // 6 までの要素数 (idx_lower + 1) - 1

    // lower_bound で要素数を数える
    cout << "6 以下の要素数は " << idx_upper << "\n";  // 6 までの要素数 (idx_lower + 1) - 1
    cout << "6 より大きい数の要素数は " << len - idx_upper << "\n";  // 6 までの要素数 (idx_lower + 1) - 1

	cout << "6である要素の数は" << idx_upper - idx_lower << "\n";

//lower_bound系には、渡すものがランダムアクセス可能なもの（配列，std::vector）である必要がある。setなどでは線形時間になってしまう。

//setにdistanceを用いると線形時間になる!! std::lower_boundも同様(ランダムアクセスイテレータなら定数時間)

	bool Inquery(int x, vector<int> &vec){
		auto itr = lower_bound(vec.begin(), vec.end(), x);
		if(itr != vec.end() && *itr == x) return true;
		else return false;
	}

//ソートされた配列にl以上r以下の値がいくつ含まれているかの個数を求める
    ll Count(ll l, ll r, vector<ll> &vec){
        auto itr_l = lower_bound(vec.begin(), vec.end(), l);
        auto itr_r = upper_bound(vec.begin(), vec.end(), r);
        return itr_r - itr_l;
    }