#include <iostream>
#include <source_location>
#include <functional>
// 기타 함수

void PrintLog(const char* filename, int line) {
    std::cout << filename << " " << line << std::endl;
}

int Add(int a, int b) {
    return a + b;
}

void Test() {
    if (std::is_constant_evaluated()) {
        // 컴파일 타임
    } else {
        // 런타임
    }
}

int main() {
    // source_location
    // 로그 남길 때
    PrintLog(__FILE__, __LINE__); // 기존에는 매크로 사용
    auto src = std::source_location::current();
    PrintLog(src.file_name(), src.line());

    // bind_front
    using namespace std::placeholders;
    auto func = std::bind(Add, 10, _1); // 기존에는 placeholder 사용.
    std::cout << func(20) << std::endl;
    auto func2 = std::bind_front(Add, 10); // 대신 bind_front 사용.
    std::cout << func2(20) << std::endl;

    // is_constant_evaluated
    // consteval 붙은 함수는 컴파일 타임에 실행됨.
    // constexpr 붙은 함수는 컴파일/런타임 둘 다 됨
    // 보통 함수는 런타임
}
