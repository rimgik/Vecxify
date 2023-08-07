#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <functional>
#include <array>
#include <cstddef>
#include <cassert>
#include <initializer_list>
#include <bit>
#include <algorithm>
#include <stdexcept>

namespace vecxify {

/*
 template <typename T, size_t ROW, size_t COL>
 class Basic_Matrix {
     
 private:
     
     // multiplication for strassen algorithms
     // both matrix has to be power of 2
     template <size_t N>
     static Basic_Matrix<T, N, N> multiply(const Basic_Matrix<T, N, N>& lhs, const Basic_Matrix<T, N, N>& rhs);
     
 protected:
     // store the element of the Basic_Matrix
     std::array<std::array<T, COL>, ROW> _data{};
     
     // apply mapping to each element in the Basic_Matrix
     // func := (row index, col index, current element) -> T
     // if using lambda function with mutable variable as the argument of this mapping function
     // wrap it in a reference wrapper, use std::ref
     Basic_Matrix<T, ROW, COL> map(const std::function<T(const size_t&, const size_t&, const T&)>& func);
     
     Basic_Matrix<T, ROW, COL> consume(const std::function<void(const size_t&, const size_t&, const T&)>& func) const;
 
     // return a Matrix same as the current Matrix but its size
     // is scaled to the required size, extra element are filled with 0
     template <size_t N, size_t M>
     Basic_Matrix<T, N, M> scaleMatrix() const;
     
     // strassen algorithm for matrix multiplication
     template <size_t N>
     Basic_Matrix<T, ROW, N> strassenMultiply(const Basic_Matrix<T, COL, N>& rhs) const;
     
     std::array<T, COL>& operator[](const size_t& i) const;
     
     Basic_Matrix();
     
     Basic_Matrix(const std::initializer_list<std::initializer_list<T>>& m);
     
     Basic_Matrix(const Basic_Matrix<T, ROW, COL>& m);
     
     explicit Basic_Matrix(const std::array<std::array<T, COL>, ROW>& m);
     
     
 public:
     
     // set all element in the Basic_Matrix to be val
     void set(T val);
     
     Basic_Matrix<T, COL, ROW> transpose() const;
     
     // return a submatrix
     template <size_t R, size_t C>
     Basic_Matrix<T, R, C> submat(const size_t& row, const size_t& col) const;
     
     bool isSquareMatrix() const noexcept;
     
     T& operator() (const size_t& row, const size_t& col) noexcept;
     
     const T& operator() (const size_t& row, const size_t& col) const noexcept;
     
     T& at(const size_t& row, const size_t& col);
     
     const T& at(const size_t& row, const size_t& col) const;
     
     Basic_Matrix<T, ROW, COL>& operator=(const Basic_Matrix<T, ROW, COL>& rhs);
     
     template <size_t U>
     Basic_Matrix<T, ROW, U> operator*(const Basic_Matrix<T, COL, U>& rhs) const;
     
     template<typename U, size_t R, size_t C>
     friend class Basic_Matrix;
     
     friend Basic_Matrix<T, ROW, COL> operator* <>(const Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);
     friend Basic_Matrix<T, ROW, COL> operator* <>(const T& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
     friend Basic_Matrix<T, ROW, COL> operator+ <>(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
     friend Basic_Matrix<T, ROW, COL> operator- <>(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
     friend Basic_Matrix<T, ROW, COL>& operator+= <>(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
     friend Basic_Matrix<T, ROW, COL>& operator-= <>(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
     friend Basic_Matrix<T, ROW, COL>& operator*= <>(Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);
     
     template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
     friend bool operator==(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);
     
     template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
     friend bool operator!=(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);
     
     friend std::ostream& operator<< <T, ROW, COL>(std::ostream& out, const Basic_Matrix<T, ROW, COL>& rhs);
     
 };
*/

template <typename T, size_t ROW, size_t COL>
class Basic_Matrix;

template <typename T, size_t ROW, size_t COL>
class Mat;

// partial template specialization for square matrix
template <typename T, size_t N>
class Mat<T, N, N>;

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator*(const Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator*(const T& lhs, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator+(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator-(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator+=(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator-=(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator*=(Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);

template <typename T, size_t ROW, size_t COL, size_t N>
Basic_Matrix<T, ROW, N>& operator*=(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, COL, N>& rhs);

template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
bool operator==(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);

template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
bool operator!=(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);

template <typename T, size_t ROW, size_t COL>
std::ostream& operator<< (std::ostream& out, const Basic_Matrix<T, ROW, COL>& rhs);

template <typename T, size_t ROW, size_t COL>
class Basic_Matrix {
    
    static_assert(ROW != 0 && COL != 0, "Dimension of matrix must be positive");
    
private:
    
    // multiplication for strassen algorithms
    // both matrix has to be power of 2
    template <size_t N>
    static Basic_Matrix<T, N, N> multiply(const Basic_Matrix<T, N, N>& lhs, const Basic_Matrix<T, N, N>& rhs) {
        static_assert(std::popcount(N) == 1);
        Basic_Matrix<T, N, N> res;
        
        if constexpr (N == 1) {
            res(0, 0) = lhs(0, 0) * rhs(0, 0);
        } else if constexpr (N == 2) {
            res(0, 0) = lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0);
            res(0, 1) = lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1);
            res(1, 0) = lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0);
            res(1, 1) = lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1);
        } else {
            //upper left
            auto c1 = multiply<N/2>(lhs.template submat<N/2, N/2>(0, 0), rhs.template submat<N/2, N/2>(0, 0)) +
            multiply<N/2>(lhs.template submat<N/2, N/2>(0, N/2), rhs.template submat<N/2, N/2>(N/2, 0));
            
            //upper right
            auto c2 = multiply<N/2>(lhs.template submat<N/2, N/2>(0, 0), rhs.template submat<N/2, N/2>(0, N/2))+
            multiply<N/2>(lhs.template submat<N/2, N/2>(0, N/2), rhs.template submat<N/2, N/2>(N/2, N/2));
            
            //lower left
            auto c3 = multiply<N/2>(lhs.template submat<N/2, N/2>(N/2, 0), rhs.template submat<N/2, N/2>(0, 0)) +
            multiply<N/2>(lhs.template submat<N/2, N/2>(N/2, N/2), rhs.template submat<N/2, N/2>(N/2, 0));
            
            //lower right
            auto c4 = multiply<N/2>(lhs.template submat<N/2, N/2>(N/2, 0), rhs.template submat<N/2, N/2>(0, N/2) )+
            multiply<N/2>(lhs.template submat<N/2, N/2>(N/2, N/2), rhs.template submat<N/2, N/2>(N/2, N/2));
            
            //combine them into result
            res.map(
                    [&](const size_t& row, const size_t& col, const T& element) {
                        if (row < N/2 && col < N/2) return c1(row, col);
                        else if (row < N/2 && col >= N/2) return c2(row, col - N/2);
                        else if (col < N/2) return c3(row - N/2, col);
                        else return c4(row - N/2, col - N/2);
                    }
            );
        }
        return res;
    }
    
protected:
    // store the element of the Basic_Matrix
    std::array<std::array<T, COL>, ROW> _data{};
    
    // apply mapping to each element in the Basic_Matrix
    // func := (row index, col index, current element) -> T
    // if using lambda function with mutable variable as the argument of this mapping function
    // wrap it in a reference wrapper, use std::ref
    Basic_Matrix<T, ROW, COL> map(const std::function<T(const size_t&, const size_t&, const T&)>& func) {
        for (size_t row = 0; row < ROW; ++row) {
            for (size_t col = 0; col < COL; ++col) {
                _data[row][col] = func(row, col, _data[row][col]);
            }
        }
        return *this;
    }
    
    Basic_Matrix<T, ROW, COL> consume(const std::function<void(const size_t&, const size_t&, const T&)>& func) const {
        for (size_t row = 0; row < ROW; ++row) {
            for (size_t col = 0; col < COL; ++col) {
                func(row, col, _data[row][col]);
            }
        }
        return *this;
    }
    
    // return a Matrix same as the current Matrix but its size
    // is scaled to the required size, extra element are filled with 0
    template <size_t N, size_t M>
    Basic_Matrix<T, N, M> scaleMatrix() const {
        static_assert(N > 0 && M > 0);
        Mat<T, N, M> res{};
        res.map(
                [&](const size_t& row, const size_t& col, const size_t& element) -> T{
                    if (row >= ROW || col >= COL)
                        return 0;
                    else return operator()(row, col);
                }
                );
        return res;
    }
    
    // strassen algorithm for matrix multiplication
    template <size_t N>
    Basic_Matrix<T, ROW, N> strassenMultiply(const Basic_Matrix<T, COL, N>& rhs) const {
        constexpr size_t dim = std::max(std::bit_ceil(ROW), std::max(std::bit_ceil(COL), std::bit_ceil(N)));
        // scale the matrix to the closest power of 2
        auto scaledLhs = scaleMatrix<dim, dim>();
        auto scaledRhs = rhs.template scaleMatrix<dim, dim>();
        auto res = multiply<dim>(scaledLhs, scaledRhs);
        return res.template scaleMatrix<ROW, N>();
    }
    
    Basic_Matrix() {
        map(
            [&](const size_t& row, const size_t& col, const T& element) -> T {
                return T{};
            }
        );
    }
    
    Basic_Matrix(const std::initializer_list<std::initializer_list<T>>& m) {
        if (m.size() != ROW)
            throw std::invalid_argument("Row number must match");
        
        for (size_t row = 0; auto& v : m) {
            if (v.size() != COL)
                throw std::invalid_argument("Column number must match");
            for (size_t col = 0; auto& x : v) {
                _data[row][col] = x;
                ++col;
            }
            ++row;
        }
    }
    
    explicit Basic_Matrix(const std::array<std::array<T, COL>, ROW>& m) : _data{ m } {}
    
public:
    
    // set all element in the Basic_Matrix to be val
    void set(T val) {
        map(
            [&](const size_t& row, const size_t& col, const T& element) -> T {
                return val;
            }
        );
    }
    
    Basic_Matrix<T, COL, ROW> transpose() const {
        Basic_Matrix<T, COL, ROW> res;
        res.map(
                [&](const size_t& row, const size_t& col, const T& element) -> T {
                    return this->operator()(col, row);
                }
            );
        return res;
    }
    
    // return a submatrix
    template <size_t R, size_t C>
    Basic_Matrix<T, R, C> submat(const size_t& row, const size_t& col) const {
        if (!(row + R <= ROW && col + C <= COL))
            throw std::out_of_range("Submatrix out-of-range");
            
        Basic_Matrix<T, R, C> res{};
        res.map(
                [&](const size_t& r, const size_t& c, const T& element) -> T {
                    return (*this)(r + row, c + col);
                }
                );
        return res;
    }
    
    bool isSquareMatrix() const noexcept {
        if constexpr (ROW == COL) {
            return true;
        } else {
            return false;
        }
    }
    
    T& operator() (const size_t& row, const size_t& col) noexcept {
        assert(row < ROW && row >= 0 && col < COL && col >= 0 && "Matrix index out of range");
        return _data[row][col];
    }
    
    const T& operator() (const size_t& row, const size_t& col) const noexcept {
        assert(row < ROW && row >= 0 && col < COL && col >= 0 && "Matrix index out of range");
        return _data[row][col];
    }
    
    T& at(const size_t& row, const size_t& col) {
        if (!(row < ROW && row >= 0 && col < COL && col >= 0))
            throw std::out_of_range("Matrix index out-of-range");
        return _data[row][col];
    }
    
    const T& at(const size_t& row, const size_t& col) const {
        if (!(row < ROW && row >= 0 && col < COL && col >= 0))
            throw std::out_of_range("Matrix index out-of-range");
        return _data[row][col];
    }
    
    Basic_Matrix<T, ROW, COL>& operator=(const Basic_Matrix<T, ROW, COL>& rhs) {
        _data = rhs._data;
        return *this;
    }
    
    template <size_t U>
    Basic_Matrix<T, ROW, U> operator*(const Basic_Matrix<T, COL, U>& rhs) const {
        return strassenMultiply(rhs);
    }
    
    template<typename U, size_t R, size_t C>
    friend class Basic_Matrix;
    
    friend Basic_Matrix<T, ROW, COL> operator* <>(const Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);
    friend Basic_Matrix<T, ROW, COL> operator* <>(const T& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
    friend Basic_Matrix<T, ROW, COL> operator+ <>(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
    friend Basic_Matrix<T, ROW, COL> operator- <>(const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
    friend Basic_Matrix<T, ROW, COL>& operator+= <>(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
    friend Basic_Matrix<T, ROW, COL>& operator-= <>(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs);
    friend Basic_Matrix<T, ROW, COL>& operator*= <>(Basic_Matrix<T, ROW, COL>& lhs, const T& rhs);
    
    template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
    friend bool operator==(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);
    
    template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
    friend bool operator!=(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs);
    
    friend std::ostream& operator<< <T, ROW, COL>(std::ostream& out, const Basic_Matrix<T, ROW, COL>& rhs);
    
};

template <typename T, size_t R, size_t C>
class Mat : public Basic_Matrix<T, R, C> {
private:
    
public:
    Mat() : Basic_Matrix<T, R, C>(){}
    
    Mat(const std::initializer_list<std::initializer_list<T>>& m) : Basic_Matrix<T, R, C>(m) {}
    
    explicit Mat(const std::array<std::array<T, C>, R>& m) : Basic_Matrix<T, R, C>(m) {}
    
};

template <typename T, size_t N>
class Mat<T, N, N> : public Basic_Matrix<T, N, N> {
private:

public:
    
    Mat() : Basic_Matrix<T, N, N>(){}
    
    Mat(const std::initializer_list<std::initializer_list<T>>& m) : Basic_Matrix<T, N, N>(m) {}
    
    explicit Mat(const std::array<std::array<T, N>, N>& m) : Basic_Matrix<T, N, N>(m) {}
    
    Mat<T, N, N>& identity() {
        Basic_Matrix<T, N, N>::map(
            [&](const size_t& row, const size_t& col, const T& element) -> T {
                if (row == col) return 1;
                return 0;
            }
        );
        return *this;
    }
    
    T determinant() const {
        auto copy = *this;
        T res{1};
        
        // perform gaussian elimination
        // target = target + multiply * original
        auto eliminate = [&](const size_t& original, const size_t& target, const T& multiply) -> void {
            for (size_t i = 0; i < N; ++i)
                copy(target, i) += multiply * copy(original, i);
        };
        
        for (size_t i = 0; i < N; ++i) {
            
            // make sure copy(row, col) are non-zero
            if (copy(i, i) == T{0}) {
                size_t next = i + 1;
                while(next < N && copy(next, i) == 0)
                    next++;
                if (next == N) // all entry below current row are zero, hence the determinant is zero
                    return T{0};
                else
                    std::swap(copy._data[i], copy._data[next]);
            }
            
            for (size_t j = i + 1; j < N; ++j) {
                eliminate(i, j, -copy(j, i) / copy(i, i));
            }
            
            res *= copy(i, i);
        }
        return res;
    }
  
};

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator* (const Basic_Matrix<T, ROW, COL>& lhs, const T& rhs) {
    Basic_Matrix<T, ROW, COL> res;
    res.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return lhs(row, col) * rhs;
        }
    );
    return res;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator* (const T& lhs, const Basic_Matrix<T, ROW, COL>& rhs) {
    Basic_Matrix<T, ROW, COL> res;
    res.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return lhs * rhs(row, col);
        }
    );
    return res;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator+ (const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs) {
    Basic_Matrix<T, ROW, COL> res;
    res.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return lhs(row, col) + rhs(row, col);
        }
    );
    return res;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL> operator- (const Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs) {
    Basic_Matrix<T, ROW, COL> res;
    res.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return lhs(row, col) - rhs(row, col);
        }
    );
    return res;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator+= (Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs) {
    lhs.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return element + rhs(row, col);
        }
    );
    return lhs;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator-= (Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, ROW, COL>& rhs) {
    lhs.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return element - rhs(row, col);
        }
    );
    return lhs;
}

template <typename T, size_t ROW, size_t COL>
Basic_Matrix<T, ROW, COL>& operator*=(Basic_Matrix<T, ROW, COL>& lhs, const T& rhs) {
    lhs.map(
        [&](const size_t& row, const size_t& col, const T& element) -> T {
            return element * rhs;
        }
    );
    return lhs;
}

template <typename T, size_t ROW, size_t COL, size_t N>
Basic_Matrix<T, ROW, N>& operator*=(Basic_Matrix<T, ROW, COL>& lhs, const Basic_Matrix<T, COL, N>& rhs) {
    return lhs = lhs*rhs;
}

template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
bool operator==(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs) {
    if constexpr (R1 != R2 || C1 != C2) {
        return false;
    } else {
        for (size_t i = 0; i < R1; ++i)
            for (size_t j = 0; j < C1; ++j)
                if (lhs(i,j) != rhs(i,j)) return false;
        
        return true;
    }
    
}

template <typename T1, size_t R1, size_t C1, typename T2, size_t R2, size_t C2>
bool operator!=(const Basic_Matrix<T1, R1, C1>& lhs, const Basic_Matrix<T2, R2, C2>& rhs) {
    return !(lhs == rhs);
}

template <typename T, size_t ROW, size_t COL>
std::ostream& operator<< (std::ostream& out, const Basic_Matrix<T, ROW, COL>& rhs) {
    rhs.consume(
        [&](const size_t& row, const size_t& col, const T& element) -> void {
            if(col == 0)
                out << '[';
            out << element;
            if (col == COL - 1){
                out << "]";
                if (row != ROW - 1) out << '\n';
            }else
                out << ", ";
        }
    );
    return out;
}

template <typename T, size_t R, size_t C>
Basic_Matrix<T, C, R> transpose(const Basic_Matrix<T, R, C>& x) {
    return x.transpose();
}

template <typename T, size_t N>
T determinant(const Mat<T, N, N>& x) {
    return x.determinant();
}

template <typename T, size_t N>
Mat<T, N, N> identity(const Mat<T, N, N>& x) {
    auto copy = x;
    return copy.identity();
}

}
#endif
