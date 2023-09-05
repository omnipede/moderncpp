#include <iostream>
#include <numbers>
#include <numeric>
// Arithmetic

int main() {

    // int 와 unsigned int 를 섞어서 사용할 때의 문제점
    int x = -2;
    unsigned int y = 10;
    std::cout << std::boolalpha;
    std::cout << " -2 < 7 = " << (x < y) << std::endl; // false?
    std::cout << " -2 <= 7 = " << (x <= y) << std::endl; // false?
    std::cout << " -2 > 7 = " << (x > y) << std::endl; // true?
    std::cout << " -2 >= 7 = " << (x >= y) << std::endl; // true?
    std::cout << std::endl;
    // 위 문제를 막기 위해 C++20 에서 cmp_XX 가 추가됨
    std::cout << " -2 < 7 = " << std::cmp_less(x, y) << std::endl;
    std::cout << " -2 <= 7 = " << std::cmp_less_equal(x, y) << std::endl;
    std::cout << " -2 > 7 = " << std::cmp_greater(x, y) << std::endl;
    std::cout << " -2 >= 7 = " << std::cmp_greater_equal(x, y) << std::endl;
    std::cout << std::endl;

    // 수학 상수 기호 추가
    std::numbers::pi;
    std::numbers::pi_v<float>;
    std::numbers::sqrt2;
    std::numbers::e;

    // 중간값
    constexpr int mid = std::midpoint(10, 20);

    // 선형 보간
    // a + t * (b-a)
    constexpr int ler = std::lerp(10, 20, 0.1);
}