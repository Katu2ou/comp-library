/*
  <next combination>
    - n要素からなる配列のうちk要素の選び方を全て列挙する

    [実装/関数]
        - do{}while(next_combination(v.begin(),v.end(),k)); の形で使う
        - 
    
    [計算時間]
        - 計算量はO(n * nCk)? で，nが大きいと遅い -> 再帰で全探索する(後述)
    
    [備考]
        - 
    
    [参照]
        - 

    [verified at]
        - 
        
*/

template <typename T> bool next_combination(const T first, const T last, int k) {
    const T subset = first + k;
    // empty container | k = 0 | k == n 
    if (first == last || first == subset || last == subset) {
        return false;
    }
    T src = subset;
    while (first != src) {
        src--;
        if (*src < *(last - 1)) {
            T dest = subset;
            while (*src >= *dest) {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

// 再帰
// auto dfs = [&](auto &&dfs, vi &vec, int i, int j){ 
//         if(j==k){
//             //処理
//         }
//         for(int t=i+1;t<n;t++){
//                 //seen[t][j+1]=1;
//                 vec.PB(t);
//                 dfs(dfs,vec,t,j+1);
//                 vec.pop_back();       
//         }
//         return;
//     };