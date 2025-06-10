/* Rollback-Mo 
 *
 * 削除操作の代わりに，rollbackメソッドを用いる(snapshotを撮った位置まで巻き戻す)
 *  - rollbackは，<配列のindex,元の値>のペアを記録しておいて時系列の逆順に戻す様にやる
 * O(N √Q * [追加操作の計算量])で解ける
 * 
 * https://ei1333.github.io/luzhiled/snippets/other/mo.html
 * 
 * verified at : 
 * 
 * 
 * 
*/

struct MoRollBack {
  using ADD = function< void(int) >; //戻り値がvoidで，引数がintの一つ
  using REM = function< void(int) >;
  using RESET = function< void() >;
  using SNAPSHOT = function< void() >;
  using ROLLBACK = function< void() >;

  int width;
  vector< int > left, right, order;

  MoRollBack(int N, int Q) : width((int) sqrt(N)), order(Q) {
    iota(begin(order), end(order), 0); //0から始まり1ずつ増える値で埋める
  }

  void add(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  // add(idx) : idx番目の要素を入れる / rem(idx) : クエリidxを処理する
  // reset : データ構造の初期化 / snapshot : 現在の状態を記録 / rollback : 直前のsnapshotに戻る
  int run(const ADD &add, const REM &rem, const RESET &reset, const SNAPSHOT &snapshot, const ROLLBACK &rollback) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      return right[a] < right[b];
    }); 
    reset();
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) {
        for(int i = left[idx]; i < right[idx]; i++) add(i);
        rem(idx);
        rollback();
      }
    }
    int nr = 0, last_block = -1;
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) continue;
      int block = left[idx] / width;
      if(last_block != block) {
        reset();
        last_block = block;
        nr = (block + 1) * width;
      }
      while(nr < right[idx]) add(nr++);
      snapshot();
      for(int j = (block + 1) * width - 1; j >= left[idx]; j--) add(j);
      rem(idx);
      rollback();
    }
  }
};