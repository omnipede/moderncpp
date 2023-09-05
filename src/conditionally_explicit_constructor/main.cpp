#include <iostream>

struct A {
    A() = default;
    // explicit keyword: 원하지 않는 형 변환이 일어나지 않도록 제한한다.
    explicit A(int n) {
        std::cout << n << std::endl;
    }
};

void test_A(A a) {

}

struct B {
    template<typename T>
    explicit B(T n) {

    }
};

void test_B(B b) {

}

struct C {
    // 조건부 Explicit
    // - bool 에 의한 간접 변환 (implicit conversion) 은 허용
    // - 그 외에는 explicit
    template<typename T>
    explicit (!std::is_same<T, bool>::value) C(T t) {
        std::cout << typeid(t).name() << std::endl;
    }
};

void test_C(C c) {

}

int main() {
    A a;
    test_A(a);
//    test_A(10); // 만약 explicit 으로 선언되지 않았다면 간접적으로 A 를 만들어서 넣어준다.

    B b { 2002 };
    test_B(b);
//    test_B(2022); // explicit 이 없으면 컴파일 된다.
//    test_B("Hello world"); // explicit 이 없으면 컴파일 된다.

    C c { 2002 };
    C c1 = true;
    test_C(true);
//    test_C(10); // 마찬가지로 explicit 이 없다면 컴파일이 되었을 것이다.
}
