#include <iostream>
#include <string>
// Non-type template parameter
// Non-type
// - int, enum
// - 포인터, 참조값
// - nullptr_t
// C++20 에서 다음 3가지 추가됨
// - float, double
// - Literal Type (types of constexpr variable)
// - String Literal

template<int i>
auto get_int() {
    return i;
}

struct ClassType {
    constexpr ClassType(int) {}
};

template<ClassType c>
auto get_class_type() {
    return c;
}

template<int N>
class StringLiteral {
public:
    constexpr StringLiteral(char const(&str)[N]) {
        std::copy(str, str + N, _data);
    }
    char _data[N];
};

template<StringLiteral str>
class ClassTemplate {};

template<StringLiteral str>
void function_template() {
    std::cout << str._data << std::endl;
}

int main() {
    int i = get_int<13>();
    std::cout << i << std::endl;
    std::array<int, 5> arr { 1, 2, 3 }; // <-- 예를 들어 이와 같은 경우 non-type template parameter 를 사용한다.

    auto c1 = get_class_type<ClassType(2011)>();

    // String literal
    // 사용처: compile time regular expression 을 확인하기 위해서 ... 하지만 많이 사용하지 않을 것 같음
    // 예를 들어 std::regex 는 런타임에 동작한다.
    ClassTemplate<"Hello world"> cls;
    function_template<"Hello world">();
}
