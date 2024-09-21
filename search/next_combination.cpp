//Next Combination
template <typename T> bool next_combination(const T first, const T last, int k) {
    const T subset = first + k;
    // empty container | k = 0 | k == n 
    if (first == last || first == subset || last == subset) {
        return false;
    }
    T src = subset;
    while (first != src) {
        src--;
        if (*src < *(last - 1)) {
            T dest = subset;
            while (*src >= *dest) {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

vector<int> v{1, 2, 3, 4, 5, 6, 7};
do {

} while(next_combination(v.begin(), v.end(), k));
//(vの中のk個の集合を、各回においてv[0],v[1],...v[k-1]が
//異なるk個となるようにしている)



/* next combination 
ll next_combination(ll sub) {
	int x = sub & -sub, y = sub + x;
	return (((sub & ~y) / x) >> 1) | y;
}
int main() {
	ll n = 5;  // {0, 1, 2, 3, 4} の部分集合を考える
	ll k = 3;

	ll bit = (1 << n) - 1;  // bit = {0, 1, 2}
	for (; bit < ((ll)1 << n); bit = next_combination(bit)) {
		 ここに処理を書く */


//Next Permutation
 int array[]={1,2,3,4};
    do{
        for(int i=0; i<4; i++){
            cout<<array[i];
            if(i!=3)cout<<" ";
        }
        cout<<endl;
    }while(next_permutation(array,array+4));

//例
int a[3] = {1, 2, 3};
  
do {
  for(int i= 0; i < 3; i++){
    cout << a[i] << ' ';
  }
  cout << endl;
} while(next_permutation(a, a + 3));

//vectorの例
 vector<int> vec{};
    rep(i,n){
        vec.pb(i);
    }
    do{

    }while(next_permutation(all(vec)));