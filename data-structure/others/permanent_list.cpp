//1. 部分永続配列
/*
- 配列の各indexごとに，(更新時刻,更新後の値)からなるvectorを持っておくと，
    更新履歴をO(logN)で取得できる．
*/

struct PartialPersistentArray {
    vector<vector<pair<int, int>>> b;
    int last_time = 0;

    // 時刻 -1 における a を設定する。
    PartialPersistentArray(vector a) {
        b.resize(a.size());
        for (int i=0; i < a.size(); ++i) {
            b[i].push_back(make_pair(-1, a[i]));
        }
    }

    // 時刻 last_time において、a[i] <- val と更新する。
    void set(int i, int val) {
        b[i].push_back(make_pair(last_time++, val));
    }

    // 時刻 time における a[i] の値を返す。
    int get(int i, int time) {
        int ok = 0, ng = b[i].size();
        while (ng - ok > 1) {
            int middle = (ok + ng) / 2;
            if (b[i][middle].first <= time) {
                ok = middle;
            } else {
                ng = middle;
            }
        }
        return b[i][ok].second;
    }

};

//2. 完全永続配列
/*
- 配列の更新の際に，現在ではなくより過去の状態を参照して更新することがある．
(ex: A->B->C->D->Bのような)
- path copying という方法を用いる．有向完全m分木として配列を持つ．
更新の際には，更新するノードと根を結ぶパスを複製し，それに接続する部分木を
元々のパスと同じように有向辺を張る．
*/

//永続セグメント木
/*

*/