/*
- 一般グラフについて，その最大安定頂点集合(どの2点も1本の辺でむすばれていない)のサイズを求める
    (最大安定頂点集合そのものを求める際も，dpに最大サイズでなく最大サイズを実現する
    頂点集合を持たせればok)
*/
//半分全列挙で頂点数nに対してO(2^{n/2})


struct MaximumIndependentSet{
    int n;
    vector<vector<int>> v;
    MaximumIndependentSet(int n_=0):n(n_),v(n_){}
    MaximumIndependentSet(int n_, vector<vector<int>> v_):n(n_),v(v_){}
    void add_edge(int x,int y){
        v[x].push_back(y);
        v[y].push_back(x);
    }
    void dfs(int x, vector<bool> &seen, vector<bool> &comp, vector<bool> can) {
        seen[x] = true;
        for(auto to:v[x]) {
            if (!seen[to] && can[to]) dfs(to, seen, comp, can);
        }
        comp[x] = true;
    }
    int ConnectedCase(vector<bool> can) {
        int pMax = -1, pMin = -1, Max = -1, Min = n+1, num = 0;
        for (int i = 0; i < n; ++i) {
            if (!can[i]) continue;
            ++num;
            int tnum = 0;
            for (auto to:v[i]) if (can[to]) ++tnum;
            if (Max < tnum) Max = tnum, pMax = i;
            if (Min > tnum) Min = tnum, pMin = i;
        }
        if (num == 1) return 1;
        if (Max <= 2) {
            if (Min == 1) return (num+1)/2;
            else return num/2;
        }
        int res = 0;
        if (Min < 2) {
            vector<bool> ncan=can;
            ncan[pMin] = false;
            for (auto to:v[pMin]) ncan[to] = false;
            res = max(res, GeneralCase(ncan) + 1);
        }
        else {
            vector<bool> ncan=can;
            ncan[pMax] = false;
            for (auto to:v[pMax]) ncan[to] = false;
            int temp1 = GeneralCase(ncan);
            res = max(res, temp1 + 1);

            ncan=can;
            ncan[pMax] = false;
            res = max(res, GeneralCase(ncan));
        }
        return res;
    }

    int GeneralCase(vector<bool> can) {
        if (n == 1) return 1;
        vector<bool> seen(n, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (!seen[i] && can[i]) {
                vector<bool> gcan(n, false);
                dfs(i, seen, gcan, can);
                res += ConnectedCase(gcan);
            }
        }
        return res;
    }

    int StableSet() {
        vector<bool> can(n, 1);
        return GeneralCase(can);
    }
};

//使用方法
/*
    - MaximumIndependentSet mis(n); 頂点数nのグラフを用意
    - mis.add_edge(a,b); a,bに辺を追加
    - mis.StableSet(); 最大安定集合の頂点数を求める

*/