//標準ライブラリのrandom
/*rand()で[0,32767]の整数乱数を生成するが、
    生成の範囲が狭い
    rand()%Nが一様でない
    周期があまり長くない
    乱数生成アルゴリズムが固定
    正規分布など、一様でない乱数生成が面倒
といった問題がある。
(rand()は線形合同法によって乱数を生成している)
*/

//高速で簡易的なrand
 unsigned int randInt() {
        static unsigned int tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
        unsigned int tt = (tx ^ (tx << 11));
        tx = ty; ty = tz; tz = tw;
        return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
    }


//1以上upper以下の整数を高速にランダムで生成する
ll Random(ll upper) {
    static mt19937_64 engine(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, upper);
    return dist(engine);
}

// mt19937による生成
uint_fast64_t seed=202202052100238523; //seedを設定
//ここでuint_fast64_t は、計算速度が早い64bitの符号なし整数型
  mt19937_64 engine(seed); //エンジンを用意して初期化

  int MAX = 1000000006;

  vector<vector<uint_fast64_t>> hs(MAX,vector<uint_fast64_t>(3,0));
  //uint_fast64_t型の初期値として0を代入した2次元配列を用意
	for(int i=0;i<MAX;i++){
		hs[i][0]=engine(); //engine() で、エンジンから乱数を取り出して代入
		hs[i][1]=engine();
		hs[i][2]=(hs[i][0]^hs[i][1]);
	}

//[0,n]の一様な整数乱数
long long random_uniform(long long n) {
    random_device rnd; 
    mt19937_64 mt(rnd());
    uniform_int_distribution<long long> dist(0, n);
    return dist(mt);
}
//random_deviceを使わずにseedを決定した方が多分早いが、この方が乱数の質は高い

//実行時間(10^6回の施行)
/*
randInt: 0.004s
Random: 0.03s
random_uniform 9s

*/