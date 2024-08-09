//mod2での行列演算
// bitsetでの演算ができるので高速
// https://drken1215.hatenablog.com/entry/2019/03/20/202800

//定義 BitMatrix A(m,n)などとして定義する



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