#ifndef BigInt_hpp
#define BigInt_hpp

#include <iostream>
#include <algorithm>
#include <memory>
#include <cstdint>
#include <cassert>
#include <compare>
#include <stdexcept>

namespace vecxify {

#ifdef __CP__
using big = BigInt;
#endif

class BigInt final {
private:
    
    std::shared_ptr<std::string> _num;
    
    bool _positive;
    
    static bool isNumber(const char& x) noexcept;
    
    // check if a string is a valid representation of BigInt
    // a string is a valid representation of BigInt iff
    // the string has no prefix zero(except 0) and consist only number
    // with the exception the first character could be '-'
    static bool isValidBigInt(const std::string_view& m) noexcept;
    
    static int8_t charToInt(const char& c);
    
    static char intToChar(const int8_t& x);
    
    bool sameSign(const BigInt& rhs) const noexcept;
    
    BigInt(const std::shared_ptr<std::string>& ptr, const bool& positive);
    
    BigInt shallowCopy() noexcept;
    BigInt deepCopy() const noexcept;
    
    //return a temp (shallow copy) abosulte value of the original BigInt
    BigInt abs() const noexcept;
    
    // multiply by a single digit
    BigInt operator*(const int8_t& rhs) const noexcept;
    BigInt& operator*=(const int8_t& rhs) noexcept;
    
public:
    
    BigInt() noexcept;
    BigInt(const std::string_view& m);
    explicit BigInt(const char& m);
    BigInt(const long long& m) noexcept;
    BigInt(const BigInt& m) noexcept;
    BigInt(const BigInt&& m) noexcept;
    
    BigInt& operator=(const std::string_view& m);
    BigInt& operator=(const BigInt& m) noexcept;
    BigInt& operator=(const BigInt&& m) noexcept;
    
    BigInt operator+(const BigInt& rhs) const;
    BigInt operator-() const noexcept;
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator*(const BigInt& rhs) const;
    BigInt operator%(const BigInt& rhs) const;
    BigInt& operator+=(const BigInt& rhs);
    BigInt& operator-=(const BigInt& rhs);
    BigInt& operator*=(const BigInt& rhs);
    BigInt& operator%=(const BigInt& rhs);
    
    bool operator==(const BigInt& rhs) const noexcept;
    bool operator<(const BigInt& rhs) const noexcept;
    bool operator<=(const BigInt& rhs) const noexcept;
    bool operator>(const BigInt& rhs) const noexcept;
    bool operator>=(const BigInt& rhs) const noexcept;
    operator bool() const noexcept;
    
    friend std::ostream& operator<<(std::ostream& out, const BigInt& x);
    
    // return new instances of BigInt (deepCopy), which is the absolute value of original BigInt
    friend BigInt abs(const BigInt& x) noexcept;
    friend BigInt abs(const BigInt&& x) noexcept;
};

}

#endif /* BigInt_hpp */
