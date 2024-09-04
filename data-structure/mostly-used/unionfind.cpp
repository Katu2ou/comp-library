//UnionFind
class UnionFind
{
public:
	UnionFind() = default;
	explicit UnionFind(size_t n)
		: m_parentsOrSize(n, -1) {}
	int find(int i)
	{	if (m_parentsOrSize[i] < 0) return i;
		return (m_parentsOrSize[i] = find(m_parentsOrSize[i]));}
	void merge(int a, int b)
	{	a = find(a);
		b = find(b);
		if (a != b){
			if (-m_parentsOrSize[a] < -m_parentsOrSize[b]) std::swap(a, b);
			m_parentsOrSize[a] += m_parentsOrSize[b];
			m_parentsOrSize[b] = a;
		}
	}
	bool connected(int a, int b)
	{	return (find(a) == find(b));}
	int size(int i)
	{	return -m_parentsOrSize[find(i)];}
private:
	std::vector<int> m_parentsOrSize;
};


//解説
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


/*
m_parentOrsize: 要素が根であるならそのグループの要素数を負の値として持つ．
				根でない場合は，親のindex(非負)を持つ．
unite(a,b) : aとbを併合する．(aのグループの要素数)<(bのグループの要素数)ならbが根になり，それ以外ならaが根になる．
*/

