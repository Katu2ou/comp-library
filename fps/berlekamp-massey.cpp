/*
-   線形回帰数列(u_{n+p}=a_0u_n + ... + a_{p-1}u_{n+p-1} : p階の線形回帰数列)
    この前k項が与えられた時に第n項をO(k^2+klogklogn)で計算できる
    
    - (a_i)の母関数は，\sum_{i=0}^{\infty} a_i x^i = P(x)/(1-c_1x-c_2x^2-...-c_kx^k)
    と表せる．ここで，P(x)とc_1,...,c_kを求めるのがBerulekamp-massey アルゴリズム
    - Bostan-mori アルゴリズムは，分子分母が高々k次の多項式で表される分数P(x)/Q(x)に対し，[x^n]P(x)/Q(x)
    を求める．

    

