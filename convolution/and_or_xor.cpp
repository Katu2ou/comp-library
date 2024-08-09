//
/*
    - and,or,xor の畳み込み(NlogN)
        - c_k = \sum_{i (and, or, xor) j = k} a_i * b_j の形の畳み込み
            (* は普通の積を表す)
        - 出典: https://sapphire15.hatenablog.com/entry/2021/09/13/114900
*/


template<class T>
class Bitwise_convolution {
    using Vec = std::vector<T>;
    using conv_size_type
    = typename Vec::size_type;

    template<T (*a)(), T (*b)(),
             T (*c)(), T (*d)()>
    static constexpr std::pair<T, T>
    liner_map(const T &x, const T &y) {
        return {a()*x + b()*y, c()*x + d()*y};
    }

    template<std::pair<T, T> 
            (*liner_map)(const T&, const T&)>
    static constexpr Vec 
    kronecker_product(Vec vec) {
        using kp_size_type =
        typename Vec::size_type;

        auto vec_size = vec.size();

        // check vec_size is power of 2
        assert(((vec_size - 1)&vec_size) == 0);
        
        for(kp_size_type i = 1; i < vec_size; i = i << 1) {
            auto mask = ~i;
            for(auto j = i; j < vec_size; j = (j+1)|i) {
                T &a = vec[j&mask];
                T &b = vec[j];
                std::pair<T, T> &&tmp = liner_map(a, b);
                a = tmp.first;
                b = tmp.second;
            }
        }
        return vec;
    }

    static constexpr T conv_zero() { return T(0);  }
    static constexpr T conv_one()  { return T(1);  }
    static constexpr T conv_neg()  { return T(-1); }

    template<class VecType>
    static auto and_map (VecType& vec) { 
        return kronecker_product
               <liner_map
                <conv_one , conv_one ,
                 conv_zero, conv_one >>(vec);
    }
    template<class VecType>
    static auto and_map_inv (VecType& vec) { 
        return kronecker_product
               <liner_map
                <conv_one , conv_neg ,
                 conv_zero, conv_one >>(vec);
    }

    template<class VecType>
    static auto or_map (VecType& vec) { 
        return kronecker_product
               <liner_map
                <conv_one , conv_zero,
                 conv_one , conv_one >>(vec);
    }
    template<class VecType>
    static auto or_map_inv (VecType& vec) { 
        return kronecker_product
               <liner_map
                <conv_one , conv_zero,
                 conv_neg , conv_one >>(vec);
    }

    template<class VecType>
    static auto xor_map (VecType& vec) { 
        return kronecker_product
               <liner_map
                <conv_one , conv_one ,
                 conv_one , conv_neg >>(vec);
    }
    template<class VecType>
    static auto xor_map_inv (VecType& vec) { 
        auto ret = xor_map(vec);
        for(auto &&i : ret) {
            i /= vec.size();
        }
        return ret;
    }

    template<Vec (*Transform)(const Vec&),
             Vec (*Inverse)  (const Vec&)>
    static auto convolution (const Vec &a,
                             const Vec &b) {
        auto vec_size = a.size();
        auto &&transa = Transform(a),
             &&transb = Transform(b);
        for(conv_size_type i = 0; i < vec_size; i++) {
            transa[i] *= transb[i];
        }
        return Inverse(transa);
    }

    public:

    static auto and_convolution(const Vec&a, const Vec&b) {
        return convolution<and_map, and_map_inv>(a, b);
    }
    static auto xor_convolution(const Vec&a, const Vec&b) {
        return convolution<xor_map, xor_map_inv>(a, b);
    }
    static auto or_convolution(const Vec&a, const Vec&b) {
        return convolution<or_map, or_map_inv>(a, b);
    }
};