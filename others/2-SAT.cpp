/*
    2-SAT: (a_1a or a_1b) and (a_2a or a_2b) and a_3 and ... の形が充足可能か
    (各項は高々2つからなる)

    - 各変数に対して，肯定ノードと否定ノードを一つづつ割り当てる
        (a_1a or a_1b) を[a_1aでないならa_1b], [a_1bでないならa_1a]と考え，
        a_1aの否定ノードからa_1bの肯定ノードに枝を引く
        (１変数からなる項については，？)
    
    - こうしてできた有向グラフにおいて，xiとxiの否定が同じ強連結成分に
    入っていれば充足不可能，そうでなければ充足可能

    atcoder libraryでの用例
        - two_sat ts(int n);  n変数の2-SATを作る (O(n))
        - (void) ts.add_clause(int i, bool f, int j, bool g);  (x_i=f)or(x_j=g)というクローズを足す (ならしO(1))
        - (void) ts.satisfiable();  割り当てが存在するかの判定 (O(n+m))
        - vector<bool> ts.answer(); 最後に呼んだsatisfiableの，クローズを満たす割り当てを返す (O(n))
    

*/