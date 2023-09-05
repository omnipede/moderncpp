#include <iostream>

// Attribute

// 컴파일러에게 걸어주는 hint.
[[nodiscard]]
int func() {
    return 10;
}

class Knight {
public:
    int _hp = 100;
    [[nodiscard]]
    Knight(int hp): _hp(hp) {}
};

enum class ErrorCode {
    None,
    Warning,
    Critical,
};

[[nodiscard("에러 코드 사용해야함")]]
ErrorCode get_error() {
    return ErrorCode::Critical;
}

int Sum(std::vector<int> &v) {
    int ret = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < 0) {
            [[unlikely]] // 이쪽 경로로 올 확률이 적다는 것을 알려줌으로써 컴파일 최적화한다.
            ret -= v[i];
        } else {
            ret += v[i];
        }
    }
    return ret;
}

struct Empty {};

struct NoUniqueAddress {
    int d;
    [[no_unique_address]] // 새로 주소 할당하지 않아도 된다는 힌트.
    Empty e;
};

int main() {
    //[[noreturn]] C++11
    //[[deprecated]] C++14
    //[[nodiscard]] C++17 // 반환값을 버리지 않고 반드시 사용해야 한다.
    //[[nodiscard("사유")]] C++20
    //[[likely]] [[unlikely]]
    // [[no_unique_address]]

    NoUniqueAddress n1, n2, n3;
    // 동일한 주소로 잡히게 된다.
    std::cout << &n1.e << std::endl;
    std::cout << &n2.e << std::endl;
    std::cout << &n3.e << std::endl;
}