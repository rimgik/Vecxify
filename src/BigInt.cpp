#include "BigInt.hpp"

namespace vecxify {

bool BigInt::isNumber(const char& x) noexcept {
    return (x <= '9' && x >= '0');
}

bool BigInt::isValidBigInt(const std::string_view& m) noexcept{
    if (m.length() == 0)
        return false;
    
    if (m.length() == 1 && m == "0")
        return true;
    
    size_t last = 0;
    for (size_t i = m.length() - 1; i >= 1; --i){
        if (!isNumber(m[i]))
            return false;
        if (m[i] != '0')
            last = i;
    }
    return (isNumber(m[0]) && m[0] != '0') || (m[0] == '-' && last == 1);
}

int8_t BigInt::charToInt(const char& c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    throw std::invalid_argument("char should be between '0' to '9'");
}
char BigInt::intToChar(const int8_t& x) {
    if (0 <= x && x <= 9) {
        return x + '0';
    }
    throw std::invalid_argument("int8_t should be between 0 to 9");
}

bool BigInt::sameSign(const BigInt& rhs) const noexcept {
    return _positive == rhs._positive;
}


BigInt::BigInt (const std::shared_ptr<std::string>& ptr, const bool& positive) {
    if (!ptr)
        throw std::invalid_argument("ptr is null");
    _num = ptr;
    _positive = positive;
}

BigInt BigInt::shallowCopy() noexcept {
    BigInt res{};
    res._num = _num;
    res._positive = _positive;
    return res;
}

BigInt BigInt::deepCopy() const noexcept {
    BigInt res{};
    res._num = std::make_shared<std::string>(*_num);
    res._positive = _positive;
    return res;
}

BigInt BigInt::abs() const noexcept {
    BigInt res{};
    res._num = _num;
    res._positive = _positive;
    if (!_positive && *_num != "0")
        res._positive = true;
    return res;
}

BigInt BigInt::operator*(const int8_t& rhs) const noexcept {
    assert(rhs <= 9 && rhs >= 0);
    
    BigInt res{deepCopy()};
    res *= rhs;
    return res;
}

BigInt& BigInt::operator*=(const int8_t& rhs) noexcept {
    assert(rhs <= 9 && rhs >= 0);
    
    std::string res{};
    int carry{0};
    for (auto it = _num->rbegin(); it != _num->rend(); ++it) {
        int total = {carry + charToInt(*it) * rhs};
        carry = total / 10;
        res.push_back(intToChar(total % 10));
    }
    if (carry)
        res.push_back(intToChar(carry));
   
    std::reverse(res.begin(), res.end());
    _num = std::make_shared<std::string>(std::move(res));
    return *this;
}

BigInt::BigInt() noexcept : _num {std::make_shared<std::string>("0")}, _positive(false) {}

BigInt::BigInt(const std::string_view& m) {
    if (!isValidBigInt(m))
        throw std::invalid_argument("Invalid representation of BigInt");
    
    if (m[0] == '-') {
        _num = std::make_shared<std::string>(m.substr(1));
        _positive = false;
    } else {
        _num = std::make_shared<std::string>(m);
        _positive = true;
    }
}

BigInt::BigInt(const char& m) {
    if (!isNumber(m))
        throw std::invalid_argument("Invalid representation of BigInt");
    
    _positive = m > '0';
    _num = std::make_shared<std::string>(1, m);
        
}

BigInt::BigInt(const long long& m) noexcept {
    _num = std::make_shared<std::string>(std::to_string(std::abs(m)));
    _positive = m > 0;
}

BigInt::BigInt(const BigInt& m) noexcept {
    _num = std::make_shared<std::string>(*m._num);
    _positive = m._positive;
}

BigInt::BigInt(const BigInt&& m) noexcept {
    _num = std::move(m._num);
    _positive = m._positive;
}

BigInt& BigInt::operator=(const std::string_view& m) {
    if (!isValidBigInt(m))
        throw std::invalid_argument("Invalid representation of BigInt");
    BigInt copy{m};
    _num = copy._num;
    _positive = copy._positive;
    return *this;
}

BigInt& BigInt::operator=(const BigInt& m) noexcept {
    BigInt copy{m.deepCopy()};
    _num = copy._num;
    _positive = m._positive;
    return *this;
}

BigInt& BigInt::operator=(const BigInt&& m) noexcept {
    _num = std::move(m._num);
    _positive = m._positive;
    return *this;
}

BigInt BigInt::operator+(const BigInt& rhs) const {
    BigInt res = *this;
    res += rhs;
    return res;
}


BigInt BigInt::operator-() const noexcept {
    BigInt res{deepCopy()};
    if (*res._num != "0")
        res._positive = !res._positive;
    else res._positive = false;
    return res;
}

BigInt BigInt::operator-(const BigInt& rhs) const {
    return *this + (-rhs);
}

BigInt BigInt::operator*(const BigInt& rhs) const {
    BigInt res{ deepCopy() };
    return (res *= rhs);
}

BigInt BigInt::operator%(const BigInt& rhs) const {
    BigInt res { deepCopy() };
    return (res %= rhs);
}


BigInt& BigInt::operator+=(const BigInt& rhs) {
    bool resultIsPositive = false;
    std::string res{};

    bool compare = (this->abs() <= rhs.abs());
    const BigInt& largerNum = compare ? rhs : *this;
    const BigInt& smallerNum = compare ? *this : rhs;
    auto it = largerNum._num->crbegin();
    auto it2 = smallerNum._num->crbegin();

    if (sameSign(rhs)) {
        resultIsPositive = _positive;
        bool carry = false;

        for ( ; it2 != smallerNum._num->rend(); it++, it2++) {
            int total { carry + charToInt(*it) + charToInt(*it2) };
            carry = (total >= 10);
            total %= 10;
            res.push_back(intToChar(total));
        }

        for ( ; it != largerNum._num->rend(); it++) {
            int total { carry + charToInt(*it) };
            carry = (total >= 10);
            total %= 10;
            res.push_back(intToChar(total));
        }

        if (carry)
            res.push_back('1');

    } else {
        resultIsPositive = largerNum._positive;
        bool takeOver = false;
        for ( ; it2 != smallerNum._num->rend(); it++, it2++) {
            int total { charToInt(*it) - takeOver - charToInt(*it2)};
            takeOver = total < 0;
            if (total < 0) {
                total += 10;
            }
            res.push_back(intToChar(total));
        }

        for ( ; it != largerNum._num->rend(); it++, it2++) {
            int total { charToInt(*it) - takeOver};
            takeOver = total < 0;
            if (total < 0)
                total += 10;
            res.push_back(intToChar(total));
        }
    }

    std::reverse(res.begin(), res.end());

    //erase for prefix zero
    size_t prefix = -1;
    for (size_t i = 0; i < res.length() && res[i] == '0'; ++i) {
        prefix = i;
    }
    if (prefix == res.length() - 1) {
        _num = std::make_shared<std::string>("0");
        _positive = false;
    } else {
        res = res.substr(prefix + 1);
        _num = std::make_shared<std::string>(std::move(res));
        _positive = resultIsPositive;
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& rhs) {
    return (*this += rhs);
}

BigInt& BigInt::operator*=(const BigInt& rhs) {
    std::string zero{};
    BigInt res{};
    for (auto it = rhs._num->crbegin(); it != rhs._num->crend(); ++it, zero += '0') {
        BigInt tmp{(*this) * charToInt(*it)};
        tmp._num->operator+=(zero);
        res += tmp;
    }
    _positive = !(_positive ^ rhs._positive);
    if (!_positive && !rhs._positive && *res._num == "0")
        _positive = false;
    _num = res._num;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& rhs) {
    if (rhs == BigInt("0"))
        throw std::invalid_argument("Remainder of zero is undefined");
    
    bool tmp = *this < BigInt{"0"};
    
    while (*this > BigInt{"0"})
        *this -= rhs.abs();
        
    while (*this < BigInt{"0"})
        *this += rhs.abs();
    
    if (tmp)
        *this -= rhs.abs();
    
    return *this;
}

bool BigInt::operator==(const BigInt& rhs) const noexcept {
    return (_positive == rhs._positive) && (_num == rhs._num || *_num == *(rhs._num));
}

bool BigInt::operator<(const BigInt& rhs) const noexcept {
    if (!sameSign(rhs)) {
        if (_positive) return false;
        else return true;
    } else {
        size_t lhsLength = _num->length();
        size_t rhsLength = rhs._num->length();
        if (_positive) {
            return (lhsLength != rhsLength ? lhsLength < rhsLength : *_num < *(rhs._num));
        } else {
            return (lhsLength != rhsLength ? lhsLength > rhsLength : *_num > *(rhs._num));
        }
        return 1;
    }
}

bool BigInt::operator<=(const BigInt& rhs) const noexcept {
    return (*this < rhs) || (*this == rhs);
}

bool BigInt::operator>(const BigInt& rhs) const noexcept {
    return !(*this <= rhs);
}

bool BigInt::operator>=(const BigInt& rhs) const noexcept {
    return !(*this < rhs);
}

//auto BigInt::operator<=>(const BigInt& rhs) const {
//    if (!sameSign(rhs)) {
//        if (_positive) return 1;
//        else return -1;
//    } else {
//        size_t lhsLength = _num.length();
//        size_t rhsLength = rhs._num.length();
//        if (lhsLength != rhsLength) {
//            if (lhsLength < rhsLength) return _positive ? -1 : 1;
//            else return _positive ? 1 : -1;
//        } else {
//            auto compare = (_num <=> rhs._num);
//            if (compare == 0) return 0;
//            return _positive ? compare < 0 : compare > 0;
//        }
//    }
//}

BigInt::operator bool() const noexcept {
    return (*_num) != "0";
}

std::ostream& operator<<(std::ostream& out, const BigInt& x) {
    if (!x._positive && *(x._num) != "0")
        out << '-';
    out << *(x._num);
    return out;
}

BigInt abs(const BigInt& x) noexcept {
    assert(!x._num);
    return BigInt(std::make_shared<std::string>(*x._num), *x._num != "0" ? true : false);
}

BigInt abs(const BigInt&& x) noexcept {
    assert(!x._num);
    std::string tmp = std::move(*x._num);
    bool sign = tmp != "0" ? true : false;
    return BigInt(std::make_shared<std::string>(std::move(tmp)), sign);
}

}
