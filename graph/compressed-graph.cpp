/*
    - 与えられた有向グラフの強連結成分を一点と見なして縮約したDAGを返す

        - 強連結成分分解を得た後，各強連結成分に対して，
        元から他の代表元に到達できるまで元のグラフ上で
        探索をする 各辺は高々一回しか通らないので，
        

    - 入力 : 有向グラフ (Wgraph)
    - 出力 : 縮約してできたDAG
    - 計算量 : O(n+m)
    - 依存 : ACL scc / グラフテンプレート
*/

template<typename G>
G compressed_graph(G &graph){
    int n = graph.size();
    atcoder::scc_graph g(n);

}

