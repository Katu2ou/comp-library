//Lowlink 関節点と橋をO(E+V)で求めるアルゴリズム

/*DFS順で頂点に番号を振り、ループ検出された時にループを構成する(DFSでの)頂点番号の最小値を
伝播する。DFSにおける親の番号<子の伝播番号 なら、その辺は橋である。
 根ノードなら子が2つ以上であり、根ノード以外であれば 自身の番号<=子の伝播番号 なら、
その頂点は関節点である
*/

// (https://algo-logic.info/bridge-lowlink/)
template <typename T>
struct LowLink {
    const WGraph<T> &G;
    vector<int> used, ord, low;
    vector<int> aps;  // 関節点の集合
    vector<int> bridges; //橋である辺のindexの集合
    LowLink(const WGraph<T> &G_) : G(G_) {
        used.assign(G.size(), 0);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        int k = 0;
        for (int i = 0; i < (int)G.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
        sort(aps.begin(), aps.end()); // 必要ならソートする
        sort(bridges.begin(), bridges.end()); // 必要ならソートする
    }
    int dfs(int id, int k, int par) { // id:探索中の頂点, k:dfsで何番目に探索するか, par:idの親
        used[id] = true;
        ord[id] = k++;
        low[id] = ord[id];
        bool is_aps = false;
        int count = 0; // 子の数
        for (auto &e : G[id]) {
            if (!used[e.to]) {
                count++;
                k = dfs(e.to, k, id);
                low[id] = min(low[id], low[e.to]);
                if (par != -1 && ord[id] <= low[e.to]) is_aps = true; 
                if (ord[id] < low[e.to]) bridges.emplace_back(e.index); // 条件を満たすので橋  
            } else if (e.to != par) { // eが後退辺の時
                low[id] = min(low[id], ord[e.to]);
            }
        }
        if (par == -1 && count >= 2) is_aps = true; 
        if (is_aps) aps.push_back(id);
        return k;
    }
};





//実装例(https://sen-comp.hatenablog.com/entry/2022/11/17/233858)
/**
 * 関節点と橋をO(E + V)で求めるアルゴリズム.
 */
class LowLink {
    typedef std::vector<std::vector<int>> Edge;

    /**
    * 訪問したことがある頂点かどうか.
    */
    vector<bool> visited;
    /**
    * 順序.
    */
    vector<int> order;
    /**
    * 配列low. low[親] < low[子]なら、ブリッジとなる。
    */
    vector<int> low;

public:
    /**
    * 与えられる木。隣接リスト形式でコストは含まれない.親は-1とする。
    */
    Edge E;
    /**
    * 関節点　その点を取り除くと全体が不連結になる点.
    */
    vector<int> articulation_points;
    /**
    * 橋。pair<int, int>でfirst < secondで橋となる両端を入れる.
    */
    vector<pair<int, int>> bridge;

private:

    void dfs(int now, int parent, int& count) {
        visited[now] = true;
        order[now] = count;
        low[now] = order[now];
        count++;
        bool is_art = false;/* 関節点であるかどうか */
        int son_count = 0;
        for (auto next : E[now]) {
            if (!visited[next]) {
                son_count++;
                dfs(next, now, count);
                if (next != parent)
                    low[now] = min(low[now], low[next]); // ループに行きついたときに、戻る際の伝播
                //関節点か イコールがつくのは、ひとまとまりのグループ内のlow[]は関節点のlow[]と同じ値だから。端はもうこれ以上伸びないので、関節点にカウントしない
                if (parent != -1 && order[now] <= low[next])
                    is_art = true;
                //橋か
                if (order[now] < low[next])
                    bridge.push_back(make_pair(min(now, next), max(now, next)));
            }
            else {
                //すでに行ったことある頂点=後退辺
                if (next != parent)
                    low[now] = min(low[now], order[next]);// ループに行きついた時にorder[]を代入
            }

        }
        //根は2つ以上の子があるなら、関節点
        if (parent == -1 && son_count >= 2)
            is_art = true;
        if (is_art)
            articulation_points.push_back(now);
    }

public:
    /**
    * 渡すのは隣接リスト形式のグラフ。辺の長さは受け付けない.
    *
    * \param e
    */
    LowLink(const Edge& e) {
        E = e;
        visited.assign(E.size(), 0);
        order.assign(E.size(), 0);
        low.assign(E.size(), 0);
    }
    /**
    * 計算の際に呼び出す。各連結成分ごとにDFSしている。.
    *
    */
    void build() {
        int count = 0;
        for (int i = 0; i < E.size(); i++) {
            if (!visited[i])
                dfs(i, -1, count);
        }
    }
};

// //使い方
// 	vvi E;
// 	//Eのグラフを構築
// 	LowLink lowlink(E);
// 	lowlink.build();

// 	auto a = lowlink.articulation_points; //関節点(vi)を得る(public変数より得られる)
// 	auto b = lowlink.bridge; //橋(vpii)を得る