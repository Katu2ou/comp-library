/*
  <index_set>
    - {0,1,...,n-1} の部分集合の所属判定と挿入・削除をO(1)(空間計算量はO(n))で行う

    [実装/関数]
        - index_set the_index_set : インスタンスを作成
        - void include(int index) : indexを追加
        - void stop : 計測の一時中止
        - void restart : 今までの計測時間を0として計測開始
        - double time : 今まで計測していた時間の総和を[s]単位で返す

    [計算時間]
        - 
    
    [備考]
        - https://atcoder.jp/contests/ahc010/submissions/31233938
    
    [参照]
        - 

    [verified at]
        - 
        
*/

struct index_set {
    vector<int> included;
    vector<int> included_pos;
    vector<int> excluded;
    vector<int> excluded_pos;
  
    index_set() {};
  
    index_set(int n) {
      included.reserve(n);
      excluded.reserve(n);
  
      for (int i = 0; i < n; i++) excluded.push_back(i);
  
      included_pos = vector<int>(n, -1);
      excluded_pos = vector<int>(n);
      for (int i = 0; i < n; i++) excluded_pos[i] = i;
    }
  
    void include(int index) {
      assert(0 <= index && index < (int) excluded.size());
      included.push_back(excluded[index]);
      included_pos[excluded[index]] = included.size()-1;
      swap(excluded_pos[excluded[index]], excluded_pos[excluded[excluded.size()-1]]);
      excluded_pos[excluded[index]] = -1;
      swap(excluded[index], excluded[excluded.size()-1]);
      excluded.pop_back();
    }
  
    void exclude(int index) {
      assert(0 <= index && index < (int) included.size());
      excluded.push_back(included[index]);
      excluded_pos[included[index]] = excluded.size()-1;
      swap(included_pos[included[index]], included_pos[included[included.size()-1]]);
      included_pos[included[index]] = -1;
      swap(included[index], included[included.size()-1]);
      included.pop_back();
    }
  
    bool is_included(int element) {
      return included_pos[element] != -1;
    }
  
    bool is_excluded(int element) {
      return excluded_pos[element] != -1;
    }
  
    bool include_element(int element) {
      assert(0 <= element && element < (int) excluded_pos.size());
      if (is_excluded(element)) {
        include(excluded_pos[element]);
        return true;
      }
      else return false;
    }
  
    bool exclude_element(int element) {
      assert(0 <= element && element < (int) included_pos.size());
      if (is_included(element)) {
        exclude(included_pos[element]);
        return true;
      }
      else return false;
    }
  };