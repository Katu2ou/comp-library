//Fp上での行列演算
/*
    - Matrix: 行列の定義・和差積・転置・逆行列
    - Gaussian_elimination: ランク・掃き出し法・連立方程式の求解


*/

//以下、p=MODとする


//行列累乗
vvl matrix_pow(vvl A, ll n) {
	vvl B(A.size(), vl(A[0].size()));
	//単位行列でBを初期化
	rep(i, B.size()) {
		B[i][i] = 1;
	}

	while (n>0) {
		if (n & 1) { B = matrix_multiply(B, A); }
		A = matrix_multiply(A, A);
		n = n >> 1;
	}
	return B;
}