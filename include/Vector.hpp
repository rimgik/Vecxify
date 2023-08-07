#ifndef Vector_hpp
#define Vector_hpp

#include "Matrix.hpp"
#include <iostream>
#include <memory>
#include <cassert>
#include <cmath>
#include <initializer_list>

namespace vecxify {

template <typename T, size_t N>
class Vec final : public Mat<T, 1, N> {
    
private:
    using Mat<T, 1, N>::transpose;
    using Mat<T, 1, N>::submat;
    using Mat<T, 1, N>::isSquareMatrix;
    using Mat<T, 1, N>::operator();
    using Mat<T, 1, N>::operator*;
    
public:
    Vec() : Mat<T, 1, N>() {}
    
    Vec(const std::initializer_list<T>& m) : Mat<T, 1, N>(std::initializer_list<std::initializer_list<T>>{m}) {}
    
    explicit Vec(const std::array<T, N>& m) : Mat<T, 1, N>(std::array<std::array<T, N>, 1>{m}) {}
    
    const T& operator() (const size_t& index) const {
        assert(index >= 0 && index < N && "Vector index out of range");
        return Mat<T, 1, N>::operator()(0, index);
    }
    
    T& operator() (const size_t& index) {
        assert(index >= 0 && index < N && "Vector index out of range");
        return Mat<T, 1, N>::operator()(0, index);
    }
    
    double length() const {
        T res{};
        Mat<T, 1, N>::consume(
              [&](const size_t& row, const size_t& col, const T& element) -> void {
                  res += element * element;
              }
          );
        return std::sqrt(res);
    }
    
    T operator*(const Vec<T, N>& rhs) const {
        T res{};
        for (size_t i = 0; i < N; ++i) {
            res += operator()(i) * rhs(i);
        }
        return res;
    }
    
};


}

#endif 
