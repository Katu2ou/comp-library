//行列の表現
vvi X ={{1,2},{3,4}};
vvi Y = {{1,2,3},{0,-1,2}};

//行列の掛け算(mod Mのとき)
vvl matrix_multiply(vvl X, vvl Y) {
	vvl Z(X.size(), vl(Y[0].size()));
	assert(X[0].size() == Y.size());
	rep(i, X.size()) {
		rep(k, Y.size()) {
			rep(j, Y[0].size()) {
				Z[i][j] = (Z[i][j] + X[i][k] * Y[k][j]) % MOD;
			}
		}
	}
	return Z;
}

//A^nの計算
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