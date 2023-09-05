#include <iostream>
#include <vector>

// Template parameter for lambda
// Lambda 에 template parameter 를 섞어 쓸 수 있다.

auto sumTyped = [](int a, int b) { return a + b; }; // C++11 typed lambda

// 두 타입이 달라도 됨
auto sumGeneric = [](auto a, auto b) { return a + b; }; // C++14 Generic lambda

// 후자가 전자로 convertible 해야 함.
auto sumDeclType = [](auto a, decltype(a) b) { return a + b; }; // C++14 Generic lambda

// 두 타입이 같아야 함
auto sumTemplate = []<typename T>(T a, T b) { return a + b; }; // C++20 Template lambda

auto getVectorSize = []<typename T>(const std::vector<T>& v) { return v.size(); };

int main() {

    auto res1 = sumTyped(true, 100); // 101
    std::cout << res1 << std::endl;
    auto res2 = sumGeneric(true, 100); // 101
    std::cout << res2 << std::endl;
    auto res3 = sumDeclType(true, 100); // 2
    std::cout << res3 << std::endl;
    auto res4 = sumTemplate(true, true); // 2
    std::cout << res4 << std::endl;

    std::vector<int> v1 {1, 2};
    std::vector<double> v2 {1.0, 2.0, 3.0};
    std::cout << getVectorSize(v1) << std::endl;
    std::cout << getVectorSize(v2) << std::endl;
}