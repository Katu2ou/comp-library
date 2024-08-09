/*
クラスカル法  𝑂(|𝐸|log|𝑉|) (辺を加える)
    1 辺集合Eをコストの小さい順にソートする
    2 以下を 𝑉−1 個の辺を選ぶまで（最小全域木 𝑇 ができるまで）繰り返す
        残っている辺の中からコストが最小の辺 e を取り出す。現在構成中の 𝑇 に e を加えても閉路ができないなら 𝑇 に加える。
        (閉路ができないことは、unionfindでeの端点が同じ集合に属していない(=2点間で連結ではない)ことで判定できる)
*/
//実装例

//UnionFindを使う

class UnionFind
{
public:

	UnionFind() = default;

	/// @brief Union-Find 木を構築します。
	/// @param n 要素数
	explicit UnionFind(size_t n)
		: m_parentsOrSize(n, -1) {}

	/// @brief 頂点 i の root のインデックスを返します。
	/// @param i 調べる頂点のインデックス
	/// @return 頂点 i の root のインデックス
	int find(int i)
	{
		if (m_parentsOrSize[i] < 0)
		{
			return i;
		}

		// 経路圧縮
		return (m_parentsOrSize[i] = find(m_parentsOrSize[i]));
	}

	/// @brief a のグループと b のグループを統合します。
	/// @param a 一方のインデックス
	/// @param b 他方のインデックス
	void merge(int a, int b)
	{
		a = find(a);
		b = find(b);

		if (a != b)
		{
			// union by size (小さいほうが子になる）
			if (-m_parentsOrSize[a] < -m_parentsOrSize[b])
			{
				std::swap(a, b);
			}

			m_parentsOrSize[a] += m_parentsOrSize[b];
			m_parentsOrSize[b] = a;
		}
	}

	/// @brief a と b が同じグループに属すかを返します。
	/// @param a 一方のインデックス
	/// @param b 他方のインデックス
	/// @return a と b が同じグループに属す場合 true, それ以外の場合は false
	bool connected(int a, int b)
	{
		return (find(a) == find(b));
	}

	/// @brief i が属するグループの要素数を返します。
	/// @param i インデックス
	/// @return i が属するグループの要素数
	int size(int i)
	{
		return -m_parentsOrSize[find(i)];
	}

private:

	// m_parentsOrSize[i] は i の 親,
	// ただし root の場合は (-1 * そのグループに属する要素数)
	std::vector<int> m_parentsOrSize;
};

//Edge A ={1,2,10,0};など
struct Edge {
  int u, v;
  long long cost;
  int index; // 辺の番号
  bool operator < (Edge const& o) {// 辺の重みで順序を定義
    return cost < o.cost;
  }
};
//　N は頂点数
// edges は辺のリスト
// 辺は無向を想定していて、edgesには片方向のみいれれば良い
vector<Edge> Kruskal(int N, vector<Edge> edges) {
  vector<Edge> tree_edges; 
  UnionFind uf(N);
  sort(edges.begin(), edges.end());// コストの昇順にソート
  
  for (Edge &e : edges) {
    if (uf.connected(e.u, e.v)) continue;// 閉路ができる場合は何もしない
    uf.merge(e.u, e.v);// 閉路ができないなら、採用
    tree_edges.push_back(e);
  }
  if(uf.size(0)<N){ //連結にならなかったら、空のvectorを返す
    vector<Edge> empty;
	return empty;
  }
  return tree_edges;
}

