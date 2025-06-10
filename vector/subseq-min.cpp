// 総和最小の部分列のコスト和を求める
/*
 * - 分割統治でO(nlogn)で求まる
 * - 総和最大の部分列のコスト和も同様
 * - 最小値(最大値)を達成する区間を取ってくるのは，最適値の更新の際に合わせて更新する形で得られる
 */

template<typename T>
T subseq_min(vector<T> &vec, int l, int r){ /* [l,r] */
    if(l == r) return vec[l];
    int mid = (l + r) / 2;
    T minval = subseq_min(vec, l, mid);
    minval = min(minval, subseq_min(vec, mid+1, r));
    T minv1 = 0;
    T sum = 0;
    for(int i = mid; i >= l; i--){
        sum += vec[i];
        minv1 = min(minv1, sum);
    }
    T minv2 = 0;
    sum = 0;
    for(int i = mid+1; i <= r; i++){
        sum += vec[i];
        minv2 = min(minv2, sum);
    }
    return min(minval, minv1 + minv2);
}

