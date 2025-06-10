// 実装（軽いもの) https://snuke.hatenablog.com/entry/2016/07/01/000000

int n; // 数列の長さ
int q; // クエリ数
vector<int> l(q), r(q); //クエリの[l,r)

int sq = max(1,int(n/sqrt(q)));
vector<int> qi(q);
for(int i = 0; i < q; ++i) qi[i] = i;
sort(qi.begin(), qi.end(), [&](int i, int j) { //クエリの順番を{l/sq,r}でソート
    if(l[i]/sq != l[j]/sq) return l[i] < l[j];
    return r[i] < r[j];
});

int nl = 0, nr = 0; //[nl,nr)
for(int i : qi){
    // add(nl) : 数列の要素A[nl]を加える時の処理
    // del(nl) : 数列の要素A[nl]を削除する時の処理
    while(nl > l[i]) --nl, add(nl);
    while(nr < r[i]) add(nr), ++nr;
    while(nl < l[i]) del(nl), ++nl;
    while(nr > r[i]) --nr, del(nr);
    /*
    クエリの結果を計算する
    */
}
