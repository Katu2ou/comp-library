//https://nyaannyaan.github.io/library/matrix/f2-matrix.hpp

namespace std {
template <size_t N>
bool operator<(const bitset<N> &a, const bitset<N> &b) {
  int f = (a ^ b)._Find_first();
  return f == N ? false : a[f];
}
}  // namespace std

template <size_t H_MAX, size_t W_MAX>
struct F2_Matrix {
  using Mat = F2_Matrix;

  int H, W;
  array<bitset<W_MAX>, H_MAX> A;
  F2_Matrix(int h = H_MAX, int w = W_MAX) : H(h), W(w) {
    assert(0 <= h and h <= (int)H_MAX);
    assert(0 <= w and w <= (int)W_MAX);
    for (int i = 0; i < (int)H_MAX; i++) A[i].reset();
  }
  inline bitset<W_MAX> &operator[](int i) { return A[i]; }
  inline const bitset<W_MAX> &operator[](int i) const { return A[i]; }

  static Mat I(int n) {
    Mat a(n, n);
    for (int i = 0; i < n; i++) a[i][i] = true;
    return a;
  }

  // (AND, XOR) 半環
  // (AND, OR) 半環には operator/ を割り当てた
  Mat &operator*=(const Mat &B) {
    Mat C(H, B.W);
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (A[i][j]) C[i] ^= B[j];
      }
    }
    swap(A, C.A);
    return *this;
  }
  Mat operator*(const Mat &B) const { return Mat(*this) *= B; }

  // (AND, OR) 半環
  friend Mat and_or_product(const Mat &A, const Mat &B) {
    Mat C(A.H, B.W);
    for (int i = 0; i < A.H; i++) {
      for (int j = 0; j < A.W; j++) {
        if (A[i][j]) C[i] |= B[j];
      }
    }
    return C;
  }

  // [0, wr) の範囲で列を掃き出し, rank を返す(0列目からwr-1列目までの列ベクトルから生成される空間の次元)
  int sweep(int wr = -1) {
    if (wr == -1) wr = W;
    int t = 0;
    for (int u = 0; u < wr; u++) {
      int piv = -1;
      for (int i = t; i < H; i++) {
        if (A[i][u]) {
          piv = i;
          break;
        }
      }
      if (piv == -1) continue;
      if (piv != t) swap(A[piv], A[t]);
      for (int i = 0; i < H; i++) {
        if (i != t && A[i][u]) A[i] ^= A[t];
      }
      t++;
    }
    return t;
  }

  Mat inverse() const {
    assert(H == W);
    int N = H;
    F2_Matrix<H_MAX, W_MAX * 2> c(H, W * 2);
    for (int i = 0; i < N; i++) {
      c[i][i + N] = 1;
      for (int j = 0; j < N; j++) {
        c[i][j] = A[i][j];
      }
    }
    int r = c.sweep();
    assert(r == N);
    Mat b(H, W);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        b[i][j] = c[i][j + N];
      }
    }
    return b;
  }

  int determinant() const {
    assert(H == W);
    F2_Matrix<H_MAX, W_MAX> c{*this};
    int r = c.sweep();
    return r == H ? 1 : 0;
  }

  bool operator<(const Mat &rhs) const {
    if (H != rhs.H) return H < rhs.H;
    if (W != rhs.W) return W < rhs.W;
    return A < rhs.A;
  }
  bool operator==(const Mat &rhs) const {
    return H == rhs.H and W == rhs.W and A == rhs.A;
  }

  friend ostream &operator<<(ostream &os, const Mat &b) {
    for (int i = 0; i < b.H; i++) {
      os << "[ ";
      for (int j = 0; j < b.W; j++) {
        os << b[i][j] << ", ";
      }
      os << "],\n";
    }
    return os;
  }
};

/*
  F2_Matrix<4,5> A;
  A[0]=17;
  A[1]=13;
  A[2]=5;
  A[3]=12;

  -> {A={1,0,0,0,1},{1,0,1,1,0},{1,0,1,0,0},{0,0,1,1,0}}
  2進表記として逆向きに値が設定されるので注意！ <-嘘では

  int u = A[2].to_ullong();
  
  -> u = 5 (また逆向きにして返ってくる)

*/






//mod2での行列演算
// bitsetでの演算ができるので高速
// https://drken1215.hatenablog.com/entry/2019/03/20/202800

//定義 BitMatrix A(m,n)などとして定義する




/*
struct BitMatrix {
    int H, W; //メンバ変数
    static const int MAX_ROW = 510; // to be set appropriately
    static const int MAX_COL = 510; // to be set appropriately
    bitset<MAX_COL> val[MAX_ROW]; 
    BitMatrix(int m = 1, int n = 1) : H(m), W(n) {}
    inline bitset<MAX_COL>& operator [] (int i) {return val[i];}

    public:
    //F2上なので + と - は等価
    BitMatrix operator+(BitMatrix& B) {
        assert(this->H == B.H && this->W == B.W);
        BitMatrix C(this->H, this->W);
        for (int i = 0; i < this->H; ++i) {
            C[i] = this->val[i] ^ B.val[i];
        }
        return C;
    }

    BitMatrix operator+=(BitMatrix& B) {
        assert(this->H == B.H && this->W == B.W);
        for (int i = 0; i < this->H; ++i) {
            this->val[i] ^= B[i];
        }
        return *this;
    }


    BitMatrix T(const BitMatrix& A) {
        BitMatrix B(A.W, A.H);
        for (int i = 0; i < A.H; ++i) {
            for (int j = 0; j < A.W; ++j) {
                B[j][i] = A.val[i][j];
            }
        }
        return B;
    }

    BitMatrix operator*(BitMatrix& B) {
        assert(this->W == B.H);
        BitMatrix C(this->H, B.W);
        BitMatrix tB = T(B);
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < B.W; ++j) {
                C[i][j] = (this->val[i] & tB[j]).count() & 1;
            }
        }
        return C;
    }

    BitMatrix Dot(const BitMatrix& A, const BitMatrix& B) {
        assert(A.W == B.H);
        BitMatrix C(A.H, B.W);
        BitMatrix tB = T(B);
        for (int i = 0; i < A.H; ++i) {
            for (int j = 0; j < B.W; ++j) {
                C[i][j] = (A.val[i] & tB[j]).count() & 1;
            }
        }
        return C;
    }

    BitMatrix Inverse(BitMatrix A) {
        int n = A.H;
        assert(n == A.W); // Ensure A is a square matrix
        BitMatrix B(n, n);
        for (int i = 0; i < n; ++i) B[i][i] = 1; // Initialize B as an identity matrix

        for (int i = 0; i < n; ++i) {
            int pivot = -1;
            for (int j = i; j < n; ++j) {
                if (A[j][i]) {
                    pivot = j;
                    break;
                }
            }
            assert(pivot != -1); // No inverse exists if pivot == -1

            swap(A[i], A[pivot]);
            swap(B[i], B[pivot]);

            for (int j = 0; j < n; ++j) {
                if (i != j && A[j][i]) {
                    A[j] ^= A[i];
                    B[j] ^= B[i];
                }
            }
        }

        return B;
    }

    //行列Aに対し，縦ベクトル　a_1,...a_wの基底をなす組を一つ求める
    vector<int> makebase(BitMatrix &A) {
        int n = A.H, m = A.W;
        vector<int> bases;
        for(int v :A){
            for(int e:base){

            }
        }
        return bases;
    }

};

*/