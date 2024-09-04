// template型 matrix 構造体 (https://nyaannyaan.github.io/library/matrix/matrix.hpp)

template <class T>
struct Matrix {
  vector<vector<T> > A;

  Matrix() = default;
  Matrix(int n, int m) : A(n, vector<T>(m, T())) {}
  Matrix(int n) : A(n, vector<T>(n, T())){};

  int H() const { return A.size(); }

  int W() const { return A[0].size(); }

  int size() const { return A.size(); }

  inline const vector<T> &operator[](int k) const { return A[k]; }

  inline vector<T> &operator[](int k) { return A[k]; }

  static Matrix I(int n) {
    Matrix mat(n);
    for (int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix &operator+=(const Matrix &B) {
    int n = H(), m = W();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix &operator-=(const Matrix &B) {
    int n = H(), m = W();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix &operator*=(const Matrix &B) {
    int n = H(), m = B.W(), p = W();
    assert(p == B.H());
    vector<vector<T> > C(n, vector<T>(m, T{}));
    for (int i = 0; i < n; i++)
      for (int k = 0; k < p; k++)
        for (int j = 0; j < m; j++) C[i][j] += (*this)[i][k] * B[k][j];
    A.swap(C);
    return (*this);
  }

  Matrix &operator^=(long long k) {
    Matrix B = Matrix::I(H());
    while (k > 0) {
      if (k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }

  Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }

  Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

  Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }

  bool operator==(const Matrix &B) const {
    assert(H() == B.H() && W() == B.W());
    for (int i = 0; i < H(); i++)
      for (int j = 0; j < W(); j++)
        if (A[i][j] != B[i][j]) return false;
    return true;
  }

  bool operator!=(const Matrix &B) const {
    assert(H() == B.H() && W() == B.W());
    for (int i = 0; i < H(); i++)
      for (int j = 0; j < W(); j++)
        if (A[i][j] != B[i][j]) return true;
    return false;
  }

  Matrix inverse() const {
    assert(H() == W());
    Matrix B(H());
    B.A = inverse_matrix(A);
    return B;
  }

  friend ostream &operator<<(ostream &os, const Matrix &p) {
    int n = p.H(), m = p.W();
    for (int i = 0; i < n; i++) {
      os << (i ? "   " : "") << "[";
      for (int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }

  T determinant() const {
    Matrix B(*this);
    assert(H() == W());
    T ret = 1;
    for (int i = 0; i < H(); i++) {
      int idx = -1;
      for (int j = i; j < W(); j++) {
        if (B[j][i] != 0) {
          idx = j;
          break;
        }
      }
      if (idx == -1) return 0;
      if (i != idx) {
        ret *= T(-1);
        swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T inv = T(1) / B[i][i];
      for (int j = 0; j < W(); j++) {
        B[i][j] *= inv;
      }
      for (int j = i + 1; j < H(); j++) {
        T a = B[j][i];
        if (a == 0) continue;
        for (int k = i; k < W(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return ret;
  }
};


// template<typename T>
// struct Matrix {
//     vector<vector<T>> A;
//     int rows, cols;

//     Matrix() = default;
//     Matrix(int r, int c) : rows(r), cols(c) {
//         A.resize(r, vector<T>(c, 0));
//     }
//     Matrix(int n) : rows(n), cols(n) {
//         A.resize(n, vector<T>(n, 0));
//     }

//     vector<T>& operator[](int i) {
//         return mat[i];
//     }

//     const vector<T>& operator[](int i) const {
//         return mat[i];
//     }

//     Matrix operator+(const Matrix& other) const {
//         Matrix result(rows, cols);
//         for (int i = 0; i < rows; i++) {
//             for (int j = 0; j < cols; j++) {
//                 result[i][j] = mat[i][j] + other[i][j];
//             }
//         }
//         return result;
//     }

//     Matrix operator*(const Matrix& other) const {
//         Matrix result(rows, other.cols);
//         for (int i = 0; i < rows; i++) {
//             for (int j = 0; j < other.cols; j++) {
//                 for (int k = 0; k < cols; k++) {
//                     result[i][j] += mat[i][k] * other[k][j];
//                 }
//             }
//         }
//         return result;
//     }

//     Matrix transpose() const {
//         Matrix result(cols, rows);
//         for (int i = 0; i < rows; i++) {
//             for (int j = 0; j < cols; j++) {
//                 result[j][i] = mat[i][j];
//             }
//         }
//         return result;
//     }

//     static Matrix identity(int size) {
//         Matrix result(size, size);
//         for (int i = 0; i < size; i++) {
//             result[i][i] = 1;
//         }
//         return result;
//     }

//     Matrix operator^(long long exp) const {
//     if (rows != cols) {
//         throw invalid_argument("Matrix must be square to raise to a power.");
//     }
//     if (exp < 0) {
//         throw invalid_argument("Exponent must be non-negative.");
//     }
//     Matrix result = Matrix::identity(rows);
//     Matrix base = *this;
//     while (exp > 0) {
//         if (exp % 2 == 1) {
//             result = result * base;
//         }
//         base = base * base;
//         exp /= 2;
//     }
//     return result;
//     }

//     // 行列の表示
//     void print() const {
//         for (int i = 0; i < rows; i++) {
//             for (int j = 0; j < cols; j++) {
//                 cout << mat[i][j];
//                 if(j < cols - 1) cout<<" ";
//             }
//             cout << endl;
//         }
//     }
// };