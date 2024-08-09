//min maxは、比べる2つの型が違うときは明示する
int a=1;
ll b=2;
cout<< min<ll>(a,b) <<endl; //1

//3つ以上の時は、型が同じ要素のリストとして書く
ll a=min({1,2,3,4,5});

//全ての要素が条件を満たすか
vector<double> a={31.0,33.1,35.2};
if( all_of(a.begin(), a.end(), [](double t) { return t < 37.5; }) ) //hoge
if( any_of(a.begin(), a.end(), [](double t) { return t < 37.5; }) ) //条件を満たす要素が一つでもあるか
if( none_of(a.begin(), a.end(), [](double t) { return t < 37.5; }) ) //条件を満たす要素が一つもないか

count_if(coins.begin(), coins.end(), [](int n){ return n <= 10; }); //条件を満たす要素の個数を返す

//配列に関する操作
vector<ll> numbers={1,2,3,4};
fill(numbers.begin(), numbers.end(), -1); //指定した範囲を-1で埋める
numbers.erase(std::remove(numbers.begin(), numbers.end(), 3), numbers.end()); //配列から3を削除する
rotate(numbers.begin(), numbers.begin() + 3, numbers.end()); //配列を3つだけ右にずらす(numbers[3]が先頭になるように)
numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end()); //同じ要素が隣り合わないよう削除する
std::nth_element(numbers.begin(), numbers.begin() + 3, numbers.end()); //3+1番目に小さい要素を求める(平均O(N))