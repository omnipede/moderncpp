#include <iostream>

// C++20: concept 1) requires clause
template<typename T>
requires std::integral<T>
void test_concept(T number) {
    std::cout << number << std::endl;
}

// C++20: concept 2) Trailing requires clause
template<typename T>
void test_concept_2(T number) requires std::integral<T> {
    std::cout << number << std::endl;
}

// C++20: concept 3) Constrained template parameter
template<std::integral T>
void test_concept_3(T number) {
    std::cout << number << std::endl;
}

// C++20: concept 4) Abbreviated function template
void test_concept_4(std::integral auto number) {
    std::cout << number << std::endl;
}

class GameObject {

};

class Knight: public GameObject {

};

template<typename T>
requires std::derived_from<T, GameObject>
void TestObj(T* obj) {

}

// Concept 생성 방법
template<typename T>
concept MyConcept = !std::is_integral_v<T> && std::derived_from<T, GameObject>;

template<typename T>
concept Addable = requires (T a, T b) {
    a + b;
}; // a + b 가 가능해야 함

template<typename T>
concept Equality = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

int main() {
    // Concept
    test_concept(3);
    test_concept_2(2l);
    test_concept_3(10);
    test_concept_4(100);

    TestObj(new Knight());
//    TestObj(new int); // <-- 에러 발생
    return 0;
}