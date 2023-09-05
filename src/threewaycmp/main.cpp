#include <iostream>
#include <compare>

// Three-Way comparison 연산자. (Spaceship operator <=>)

struct MyInt {
    MyInt(int value): _value(value) {}

    // < <= > >= == !== 를 한 세트로 만들어줘야한다. 즉, 손이 많이 간다.
    // bool operator<(const MyInt& rhs) const { return _value < rhs._value; }

    // 삼항 연산자를 이용하면 한 줄로 구현이 끝난다.
    auto operator<=>(const MyInt& rhs) const = default;

    int _value;
};

int main() {
    MyInt a{1};
    MyInt b{2};
    bool test = a < b;

    // 비교 (Relational, Equivalence, Comparable)
    // - 6종 비교 연산 지원 == !=, <. <=, >, >= (Relational)
    // - 모든 Equivalent 한 값들은 서로 구분되지 않고 완전 똑같다. (Equivalence)
    // - a < b, a == b, a > b 중 하나는 반드시 참이다. (Comparable)
    //      ex) float 비교 시 b 가 NaN 이면 위의 3가지 비교 연산이 모두 참이 아니다.

    // strong_ordering: Relational, Equivalence, Comparable
    // weak_ordering: Relational, Comparable
    // partial_ordering: Relational

    int x = 1;
    int y = 2;
    auto ret = (x <=> y);
    if (ret < 0)
        std::cout << "a < b" << std::endl;
    else if (ret == 0)
        std::cout << "a == b" << std::endl;
    else if (ret > 0)
        std::cout << "a > b" << std::endl;
}

struct Strong {
    std::strong_ordering operator<=>(const Strong&) const = default;
};

struct Weak {
    std::weak_ordering operator<=>(const Weak&) const = default;
};

struct Partial {
    std::partial_ordering operator<=>(const Partial&) const = default;
};

struct Test {
    // partial_ordering 으로 연역된다. 멤버 s, w, p 중 p 가 가장 약하기 때문.
    auto operator<=>(const Test&) const = default;
    Strong s;
    Weak w;
    Partial p;
};