#ifndef ModNum_hpp
#define ModNum_hpp

#include <iostream>

namespace vecxify {

template <typename T, T N>
class ModNum;

template <typename T, T N>
std::ostream& operator<< (std::ostream& out, const ModNum<T, N>& m) {
    out << m.get();
    return out;
}

template <typename T, T N>
class ModNum final {
private:
    T _data;
public:
    
    ModNum() : _data {} {}
    
    ModNum(const T& m) : _data { m % N } {};
    
    ModNum<T, N>& operator= (const T& m) {
        _data = m % N;
        return *this;
    }
    
    const T& get() const noexcept {
        return _data;
    }
    
    ModNum<T, N> operator+(const ModNum<T, N>& rhs) const {
        return (_data + rhs.get()) % N;
    }
    
    ModNum<T, N> operator-(const ModNum<T, N>& rhs) const {
        return (_data - rhs.get() + N) % N;
    }
    
    ModNum<T, N> operator-() const {
        return (N - _data) % N;
    }
    
    ModNum<T, N> operator*(const ModNum<T, N>& rhs) const {
        return (_data * rhs.get()) % N;
    }
    
    ModNum<T, N>& operator+=(const ModNum<T, N>& rhs) {
        _data = (_data + rhs.get()) % N;
        return *this;
    }
    
    ModNum<T, N>& operator-=(const ModNum<T, N>& rhs) {
        _data = (_data - rhs.get() + N) % N;
        return *this;
    }
    
    ModNum<T, N>& operator*=(const ModNum<T, N>& rhs) {
        _data = (_data * rhs.get()) % N;
        return *this;
    }
    
    ModNum<T, N>& operator++() {
        _data++;
        _data %= N;
        return *this;
    }
    ModNum<T, N>& operator--() {
        _data--, _data += N;
        _data %= N;
        return *this;
    }
    
    ModNum<T, N> operator++(int) {
        ModNum<T, N> copy{ *this };
        ++(*this);
        return copy;
    }
    
    ModNum<T, N> operator--(int) {
        ModNum<T, N> copy{ *this };
        --(*this);
        return copy;
    }
    
    bool operator==(const ModNum<T, N>& rhs) const {
        return _data == rhs.get();
    }
    
    bool operator!=(const ModNum<T, N>& rhs) const {
        return !(*this == rhs);
    }
    
    bool operator>(const ModNum<T, N>& rhs) const {
        return _data > rhs.get();
    }
    
    bool operator<(const ModNum<T, N> &rhs) const {
        return (!(*this > rhs)) && (*this != rhs);
    }
    
    bool operator>=(const ModNum<T, N> &rhs) const {
        return (*this > rhs) || (*this == rhs);
    }
    
    bool operator<=(const ModNum<T, N> &rhs) const {
        return (!(*this > rhs));
    }
    
    operator bool() const {
        return _data > 0;
    }
    
};


}
#endif
