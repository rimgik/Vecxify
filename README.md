# Vecxify
Vecxify is a generic C++ math library

## Features
#### Common operation are supported, such as addition, subtraction, multiplication and comparison.
- **Matrix**     ```Mat<T, ROW, COL>```
  - Fast matrix multiplication with Strassen algorithm
  - Calculation of determinant
  - Perform transpose and identity operations
- **Vector** ```Vec<T, N>```
  - Dot product calculation
- **BigInt** ```BigInt```
  - Handle arbitrary large number
  - Support addition, subtraction, multiplication and comparison
- **Modular Number** ```ModNum<T, N>```
  - Perform operations within modular arithmetic


# Example 
#### Large fibonacci number with matrix exponentiation
```cpp
using namespace vecxify;

Mat<BigInt, 2, 2> binary_power(Mat<BigInt, 2, 2> base, const int& exp) {
    Mat<BigInt, 2, 2> res { identity(Mat<BigInt, 2, 2>()) };
    while (exp) {
        if (exp%2)
          res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

BigInt fib (const int& n) {
    Mat<BigInt, 2, 2> result { {1, 1}, {1, 0} };
    return binary_power(result, n).at(0, 1);
}

int main() {
    std::cout << "200th term of fib is " << fib(200) << std::endl;
}
```
```
200th term of fib is 280571172992510140037611932413038677189525
```
#### Determinant, Transpose, Identity
```cpp
using namespace vecxify;

int main() {
    Mat<double, 2, 2> m { {1.2, 3.4}, {7.3, 8.0} };
    std::cout << "Matrix m is: \n"           << m              << "\n\n";
    std::cout << "2x2 identity matrix\n"     << identity(m)    << "\n\n";
    std::cout << "Determinant of matrix m: " << determinant(m) << "\n\n";
    std::cout << "Transpose of matrix m: \n" << transpose(m)   << '\n';
}
```
```
Matrix m is:
[1.2, 3.4]
[7.3, 8]

This is a 2x2 identity matrix
[1, 0]
[0, 1]

Determinant of matrix m: -15.22

Transpose of matrix m: 
[1.2, 7.3]
[3.4, 8]
```
#### Factorial with BigInt
```cpp
using namespace vecxify;

BigInt factorial(const long long& n) {
    if (n <= 1) return BigInt(1ll);
    return BigInt(n) * factorial(n - 1);
}

int main() {
    std::cout << "Result: " << factorial(50) << std::endl;
}
```
```
Result: 30414093201713378043612608166064768844377641568960512000000000000
```
