// template型 matrix 構造体

template<typename T>
struct Matrix {
    vector<vector<T>> mat;
    int rows, cols;

    Matrix(int r, int c) : rows(r), cols(c) {
        mat.resize(r, vector<T>(c, 0));
    }

    vector<T>& operator[](int i) {
        return mat[i];
    }

    const vector<T>& operator[](int i) const {
        return mat[i];
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = mat[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result[i][j] += mat[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[j][i] = mat[i][j];
            }
        }
        return result;
    }

    static Matrix identity(int size) {
        Matrix result(size, size);
        for (int i = 0; i < size; i++) {
            result[i][i] = 1;
        }
        return result;
    }

    Matrix operator^(long long exp) const {
    if (rows != cols) {
        throw invalid_argument("Matrix must be square to raise to a power.");
    }
    if (exp < 0) {
        throw invalid_argument("Exponent must be non-negative.");
    }
    Matrix result = Matrix::identity(rows);
    Matrix base = *this;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exp /= 2;
    }
    return result;
    }

    // 行列の表示
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << mat[i][j];
                if(j < cols - 1) cout<<" ";
            }
            cout << endl;
        }
    }
};