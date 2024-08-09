//平衡二分木(Splay木)
/*
https://take44444.github.io/Algorithm-Book/range/bbst/splay-tree/main.html
二分木：要素の検索・挿入・削除をO(log n)で処理する(要素の重複は認めない)

Splay木：splayという操作を用いて、アクセスしたノードを根に持っていく
ことで、計算量を抑える(償却計算量:「続けて行った」一連の操作の
平均した1回あたりの計算量。平均計算量は、あらゆる入力に対しての
操作をそれぞれ1回だけ行った時の計算量の平均値である。)

- zig : splayしたいノードの親が根ノードであるとき、親を中心に
回転する
- zig-zag : splayしたいノードの関係が、親と親の親ノードの関係と
逆である時に行われる
- zig-zig : splayしたいノードの関係が、親と親の親ノードの関係と
同じである時に行われる(splayしたいノードの親を中心に2回回転する)

実装例
*/
template <class T> struct Node {
  Node<T> *l, *r, *p;
  T k;
  Node(T k_) : l(nullptr), r(nullptr), p(nullptr), k(k_) {}
  int state() {
    if (p && p->l == this) return -1;
    if (p && p->r == this) return 1;
    return 0;
  }
  void rotate() {
    Node<T> *par = p;
    Node<T> *mid;
    if (p->l == this) {
      mid = r; r = par;
      par->l = mid;
    } else {
      mid = l; l = par;
      par->r = mid;
    }
    if (mid) mid->p = par;
    p = par->p; par->p = this;
    if (p && p->l == par) p->l = this;
    if (p && p->r == par) p->r = this;
  }
  void splay() {
    while(state()) {
      int st = state() * p->state();
      if (st == 0) {
        rotate();
      } else if (st == 1) {
        p->rotate();
        rotate();
      } else {
        rotate();
        rotate();
      }
    }
  }
};

template <class T> struct SplayTree {
private:
  using NC = Node<T>;
  NC *root, *min_, *max_;
  int sz;
  void splay(NC *node) { node->splay(), root = node; }
  NC* bound(T k, bool lower) {
    NC *valid = nullptr, *left = root, *right = nullptr;
    while (left) {
      valid = left;
      if ((lower && !(k > left->k)) || (!lower && (k < left->k))) {
        right = left;
        left = left->l;
      } else left = left->r;
    }
    if (!right && valid) splay(valid);
    return right;
  }
public:
  SplayTree() : root(nullptr), min_(nullptr), max_(nullptr), sz(0) {}
  int size() { return sz; }
  NC *begin() { return min_; }
  NC *rbegin() { return max_; }
  NC* lower_bound(T k) {
    NC *ret = bound(k, true);
    if (ret) splay(ret);
    return ret;
  }
  NC* upper_bound(T k) {
    NC *ret = bound(k, false);
    if (ret) splay(ret);
    return ret;
  }
  NC* entry(T k) {
    lower_bound(k);
    if (!root || root->k != k) return nullptr;
    return root;
  }
  pair<NC*, bool> insert(T k) {
    NC *nn = new NC(k);
    if (!root) { // if no nodes in tree
      min_ = nn, max_ = nn, root = nn;
    } else if (min_->k > k) { // if k become min k in tree
      min_->l = nn, nn->p = min_, min_ = nn;
      splay(nn);
    } else if (max_->k < k) { // if k become max k in tree
      max_->r = nn, nn->p = max_, max_ = nn;
      splay(nn);
    } else {
      NC *node = bound(k, true); // assert node is not null
      if (node->k == k) { // if tree already has k k
        splay(node); delete nn; return {root, false};
      }
      // now node is first node whose k is larger than k
      nn->l = node->l; node->l = nn;
      nn->p = node; if (nn->l) nn->l->p = nn;
      splay(nn);
    }
    sz++; return {root, true};
  }
  void erase(NC *node) {
    assert(node); splay(node); sz--;
    if (!root->l) { // it means this node is min_
      // if no nodes remain
      if (!root->r) root = nullptr, min_ = nullptr, max_ = nullptr;
      else {
        root = root->r; root->p = nullptr;
        for (min_ = root; min_->l; min_ = min_->l);
        splay(min_);
      }
    } else if (!root->r) {
      root = root->l; root->p = nullptr;
      for (max_ = root; max_->r; max_ = max_->r);
      splay(max_);
    } else {
      root->l->p = nullptr; // cut left tree
      NC *nx_root = root->l; // next root
      for (;nx_root->r; nx_root = nx_root->r);
      splay(nx_root);
      // now nx_root doesn't have right child
      nx_root->r = node->r; nx_root->r->p = nx_root;
      root->p = nullptr;
    }
    delete node;
  }
  bool erase(T k) {
    if (!entry(k)) return false;
    erase(root);
    return true;
  }
};

