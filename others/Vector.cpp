//目次
/*
vectorの色々
マージソート
比較関数ソート
座標圧縮
*/

vector<int> vec1{};
vector<int> vec2{};

//二つの配列が同じか
if(vec1==vec2) //でよい

//先頭に要素を追加
vec1.insert(vec1.begin(), 2023);

//配列の末尾に配列を追加
vec1.insert(vec1.end(), vec2.begin(), vec2.end());

//末尾の要素を削除
vec1.pop_back();
vec1.erase(vec1.begin()); // 先頭の要素を削除

//全消去
vec1.clear();

//ソート済みvertorの重複要素を一つにして返す
template<typename T>
vector<T> removeDuplicates(const vector<T>& sortedVec) {
    vector<T> result = sortedVec;
    auto last = std::unique(result.begin(), result.end());
    result.erase(last, result.end());
    return result;
}

//ソート済みのvectorにxが含まれているか(含まれていればそのindexを、含まれていなければ-1を返す)
int vector_finder(vector<int>& vec, int x){
    auto iter_lower = lower_bound(vec.begin(), vec.end(), x);
    if(iter_lower==vec.end()) return -1;
    if(*iter_lower==x)return distance(vec.begin(),iter_lower);
    else return -1;
}

//ソート済みの[重複要素のない]vectorに対し，n以上の整数でvectorに含まれていないもののうち最小を返す
int vector_finder2(vector<int>& vec, int n){
    int ind=distance(vec.begin(),lower_bound(vec.begin(),vec.end(),n));
    if(ind==vec.size()||vec[ind]!=n) return n;
    int l=ind;
    int r=vec.size();
    while(r-l>1){
        int mid=(l+r)/2;
        if(vec[mid]-n>mid-l) r=mid;
        else l=mid;
    }
    return vec[l]+1;
}

//ソート済みの2つのvectorに共通して含まれている要素を求める??
vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {2, 4, 6, 8, 10};
    vector<int> result;

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));

    for(auto x : result){
        cout << x << " ";
    }
    cout << endl;

// setに変換せずにvectorの重複要素を消す(座圧などに使える)
vector<int> vec = {10,40,40,20,20,30,20,20,40};
sort(vec.begin(), vec.end()); //あらかじめソートしておく
vec.erase(std::unique(vec.begin(), vec.end()), vec.end()); //これでvec={10,20,30,40}となる
//なお、ソートせずに最終行を行うと、vec={10,40,20,30,20,40}となる

//vectorをソートして(要素,個数)というベクトルを返す
template<typename T>
vector<pair<T,int>> vector_count(vector<T> vec){
    vector<pair<T,int>> ret;
    sort(vec.begin(),vec.end());
    int cnt=1;
    for(int i=0;i<vec.size();i++){
        if(i==vec.size()-1){
            ret.push_back(make_pair(vec[i],cnt));
            break;
        }
        if(vec[i]==vec[i+1]) cnt++;
        else{
            ret.push_back(make_pair(vec[i],cnt));
            cnt=1;
        }
    }
    return ret;
}


//マージソート(O(NlogN))
//入力: 配列
//出力: 配列をソートしたもの
template<typename T>
void merge(vector<T> &vec, vector<T> &v1, vector<T> &v2) {
    auto siz1 = v1.size();
    auto siz2 = v2.size();
    size_t p1 = 0;
    size_t p2 = 0;

    while (p1 < siz1 && p2 < siz2) {
        if (v1.at(p1) < v2.at(p2))
            vec.push_back(v1.at(p1++));
        else
            vec.push_back(v2.at(p2++));
    }

    while (p1 < siz1) vec.push_back(v1.at(p1++));
    while (p2 < siz2) vec.push_back(v2.at(p2++));
}

template<typename T>
void mergeSort(vector<T> &vec) {
    if (vec.size() <= 1)
        return;

    auto iter = vec.begin() + vec.size() / 2;
    vector<T> v1(vec.begin(), iter);
    vector<T> v2(iter, vec.end());

    mergeSort(v1);
    mergeSort(v2);

    vec.clear();
    merge(vec, v1, v2);
}


//任意の比較関数でソートする
struct comp{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if(a.first!=b.first) return a.first < b.first;
        else return a.second < b.second;
    }
};
//例えば上のようにすると、(1,1)<(2,3)<(2,4)などとなり、ソートをするとこの順に左から並ぶ
//使い方
priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
sort(vec.begin(), vec.end(), comp());
/// ラムダ式でソートを定義(R[i]の値が小さい順にindexからなるvectorをソートする)
sort(I.begin(), I.end(), [&](int x, int y){return R[x]<R[y];});



//座標圧縮
//入力: 配列(ll or int)
//出力: 入力の配列は圧縮後の配列に変化し、返り値としては圧縮前の配列の元をsortして重複部分を無くしたものが返る。
//ex) {1,6,12,5,4,5}->{0,3,4,2,1,2}となり、返り値は{1,4,5,6,12}となる
template<typename T>
vector<T> compress(vector<T> &vec) {
    vector<T> ret = vec;
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    for (T &x : vec) {
        x = lower_bound(ret.begin(), ret.end(), x) - ret.begin();
    }
    return ret;
}

//入力: 値 /上で求めた返り値
//出力 座標変換前の値を、座標変換後の値の中で何番目に当たるか返す
//ex) {2,4,6,7,10} -> {0,1,2,3,4}のとき、 1->0, 2->0, 3->1, 10->4, 11->5
template<typename T>
T compress_value(T x, vector<T> &ret) {
    return lower_bound(ret.begin(), ret.end(), x) - ret.begin();
}


//入力: 別のvector / 一番上で求めた返り値
//出力: 入力のvectorの各要素に対して、その要素が上で求めた返り値の番号に変換したvectorにする。 (-1なら座標の最小値より小さい)
//ex) {3,5,10,4,2} -> {0,2,3,1,0}(3は、{1,4,5,6,12}のうち0以上4未満なので0番目にあたる)
template<typename T>
void compress_vector(vector<T> &vec, vector<T> &ret) {
    for (T &x : vec) {
        x = upper_bound(ret.begin(), ret.end(), x) - ret.begin()-1;
    }
    return;
}



//一般pair型ソート(配列vi = x[m][n])について、x[i][0]の値で昇順ソートする
//→単にsort(all(v))でいける



//K重ループ(Kは可変) void
//i番目のループは，添字がLiからRi-1まで動いてほしいとする
//入力: K(ループの個数) // vpii (L,R) (添字の動く範囲が[L,R)であることを表す)

void multifor(int K, vector<pair<int,int>> &range){
    vector<int> I(K,0); //添字となるもの
    int roopsum=1;
    for(int i=0;i<K;i++){
        roopsum*=range[i].se-range[i].fi;
        I[i] =range[i].fi;
    }
    for(int i=0;i<roopsum;i++){
        //Iを用いて処理を書く



        //
        if(i==roopsum-1)break;
        for(int i=K-1;i>=0;i--){
            I[i]++;
            if(I[i]==range[i].se){
                I[i]=range[i].fi;
            }
            else break;
        }
    }
}

