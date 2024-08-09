/*RMQ (一点更新・区間最小値)
 nは元のノードの個数

 RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    update(i,x): i 番目の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
*/

void update(int i, int x) { // i: 更新したい数列の位置　x: 更新する値
    i += n - 1;    // i番目は、配列上では n-1+i 番目に格納されている
    dat[i] = x;    // 葉の更新
    while (i > 0) {    // 親を辿りながら更新していく
        i = (i - 1) / 2;  // parent
        dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
}

void update(int i, int x) { // i: 更新したい数列の位置　x: 更新する値
    i += n - 1;    // i番目は、配列上では n-1+i 番目に格納されている
    dat[i] = x;    // 葉の更新
    while (i > 0) {    // 親を辿りながら更新していく
        i = (i - 1) / 2;  // parent
        dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
}

void set(int i, T x) { dat[i + n - 1] = x; }
void build() {
    for (int k = n - 2; k >= 0; k--){
        dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }
}

int find_rightest(int a, int b, T x) { return find_rightest_sub(a, b, x, 0, 0, n); }
int find_rightest_sub(int a, int b, T x, int k, int l, int r) {
    if (dat[k] > x || r <= a || b <= l) {  // 自分の値がxより大きい or [a,b)が[l,r)の範囲外ならreturn a-1
        return a - 1;
    } else if (k >= n - 1) {  // 自分が葉ならその位置をreturn
        return (k - (n - 1));
    } else {
        int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
        if (vr != a - 1) {  // 右の部分木を見て a-1 以外ならreturn
            return vr;
        } else {  // 左の部分木を見て値をreturn
            return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
        }
    }
}




/////////////完成品//////////

/* RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    set(int i, T x), build(): i番目の要素をxにセット。まとめてセグ木を構築する。O(n)
    update(i,x): i 番目の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
    find_rightest(a,b,x): [a,b) で x以下の要素を持つ最右位置を求める。O(log(n))
    find_leftest(a,b,x): [a,b) で x以下の要素を持つ最左位置を求める。O(log(n))
*/

template <typename T>
struct RMQ {
    const T e = numeric_limits<T>::max();
    function<T(T, T)> fx = [](T x1, T x2) -> T { return min(x1, x2); };
    int n;
    vector<T> dat;
    RMQ(int n_) : n(), dat(n_ * 4, e) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }
    void set(int i, T x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
    void update(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  
            dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    // the minimum element of [a,b)
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return e;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }
    int find_rightest(int a, int b, T x) { return find_rightest_sub(a, b, x, 0, 0, n); }
    int find_leftest(int a, int b, T x) { return find_leftest_sub(a, b, x, 0, 0, n); }
    int find_rightest_sub(int a, int b, T x, int k, int l, int r) {
        if (dat[k] > x || r <= a || b <= l) {  
            return a - 1;
        } else if (k >= n - 1) {  
            return (k - (n - 1));
        } else {
            int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            if (vr != a - 1) {  
                return vr;
            } else {  
                return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            }
        }
    }
    int find_leftest_sub(int a, int b, T x, int k, int l, int r) {
        if (dat[k] > x || r <= a || b <= l) {  
            return b;
        } else if (k >= n - 1) {  
            return (k - (n - 1));
        } else {
            int vl = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            if (vl != b) {  
                return vl;
            } else {  
                return find_leftest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            }
        }
    }
};



/////////////








/* RUQ 区間更新+RMQ (遅延セグ木)
 kは今見ている配列の位置
 RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    update(a,b,x): 区間[a,b) の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
*/


void eval(int k) { // 配列のk番目を更新
    if (lazy[k] == INF) return;  // 更新するものが無ければ終了
    if (k < n - 1) {             // 葉でなければ子に伝搬(上から伝搬)
        lazy[k * 2 + 1] = lazy[k];
        lazy[k * 2 + 2] = lazy[k];
    }
    // 自身を更新
    dat[k] = lazy[k];
    lazy[k] = INF;
}


int query_sub(int a, int b, int k, int l, int r) {
    eval(k); // ここが追加！
    if (r <= a || b <= l) {  // 完全に外側の時
        return INF;
    } else if (a <= l && r <= b) {  // 完全に内側の時
        return dat[k];
    } else {  // 一部区間が被る時
        int vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(vl, vr);
    }
}
int query(int a, int b) { return query_sub(a, b, 0, 0, n); }

void add(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {  // 完全に内側の時
            lazy[k] += x;
            eval(k);
        } else if (a < r && l < b) {                  // 一部区間が被る時
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void add(int a, int b, T x) { add(a, b, x, 0, 0, n); }

void update(int a, int b, int x, int k, int l, int r) {　//[k,l]を
    eval(k);
    if (a <= l && r <= b) {  // 完全に内側の時
        lazy[k] = x;
        eval(k);
    } else if (a < r && l < b) {                     // 一部区間が被る時
        update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
        update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
        dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
}
void update(int a, int b, int x) { update(a, b, x, 0, 0, n); }



/////////完成品//////////

/* RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    set(i,x), build(): i番目の要素をxにセット。まとめてセグ木を構築する。O(n)
    add(a,b,x): 区間[a,b) の要素に x を加算。O(log(n))
    update(a,b,x): 区間[a,b) の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
    find_rightest(a,b,x): [a,b) で x以下の要素を持つ最右位置を求める。O(log(n))
    find_leftest(a,b,x): [a,b) で x以下の要素を持つ最左位置を求める。O(log(n))
*/


template <typename T>
struct RMQ {
    const T INF = numeric_limits<T>::max();
    int n;
    vector<T> dat, lazy;
    RMQ(int n_) : n(), dat(n_ * 4, INF), lazy(n_ * 4, INF) {
        int x = 1;
        while (n_ > x) x *= 2;
        n = x;
    }

    void set(int i, T x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }

    void eval(int k) {
        if (lazy[k] == INF) return;  
        if (k < n - 1) {             
            lazy[k * 2 + 1] = lazy[k];
            lazy[k * 2 + 2] = lazy[k];
        }
      
        dat[k] = lazy[k];
        lazy[k] = INF;
    }

 void add(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {  
            lazy[k] += x;
            eval(k);
        } else if (a < r && l < b) {                 
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);  
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);  
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void add(int a, int b, T x) { add(a, b, x, 0, 0, n); }


    void update(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {  
            lazy[k] = x;
            eval(k);
        } else if (a < r && l < b) {                     
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);  
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);  
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, T x) { update(a, b, x, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        eval(k);
        if (r <= a || b <= l) {  
            return INF;
        } else if (a <= l && r <= b) { 
            return dat[k];
        } else {  
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }

 T find_rightest(int a, int b, int x) { return find_rightest_sub(a, b, x, 0, 0, n); }  // 存在しなければ a-1
    T find_leftest(int a, int b, int x) { return find_leftest_sub(a, b, x, 0, 0, n); }    // 存在しなければ b
    T find_rightest_sub(int a, int b, int x, int k, int l, int r) {
        eval(k);
        if (dat[k] > x || r <= a || b <= l) {  
            return a - 1;
        } else if (k >= n - 1) {  
            return (k - (n - 1));
        } else {
            int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            if (vr != a - 1) {  
                return vr;
            } else {  
                return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            }
        }
    }
    T find_leftest_sub(int a, int b, int x, int k, int l, int r) {
        eval(k);
        if (dat[k] > x || r <= a || b <= l) { 
            return b;
        } else if (k >= n - 1) {  
            return (k - (n - 1));
        } else {
            int vl = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            if (vl != b) { 
                return vl;
            } else {  
                return find_leftest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            }
        }
    }


    inline T operator[](int a) { return query(a, a + 1); }
    void print() {
        for (int i = 0; i < 2 * n - 1; ++i) {
            cout << (*this)[i];
            if (i != n) cout << ",";
        }
        cout << endl;
    }
};













