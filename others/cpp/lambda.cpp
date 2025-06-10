//ラムダ式：これを使うと関数内で関数を定義できる

int main() {
  int max_num = 0;
 
  // 今まで受け取った値の中から最も大きな値を返す関数
  auto update_max = [&](int n) { //update_maxが再帰を含まないならauto型。[&]は外側の変数を参照できるようにするため。普通は[]と書く
    if (max_num < n) {
      max_num = n;
    }
    return max_num;
  };
 
  cout << update_max(5) << endl;
}

int main() {
  // 再帰関数の定義
  function<int(int)> sum = [&](int n) { //再帰を含むならfunction<返り値の型(引数の型)>と書く
    if (n == 0) {
      return 0;
    }
    int s = sum(n - 1);
    return s + n;
  };
 
  cout << sum(3) << endl;
}