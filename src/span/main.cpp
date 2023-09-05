#include <iostream>
#include <span>
#include <vector>

// std::span

void PrintArray(int* arr, int len) {
    // arr 이 포인터이므로 arr의 size, length 를 알기 어려움
    std::cout << "array length = " << len << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << arr[i] << std::endl;
    }
}

void Print(std::span<int> container) {
    std::cout << "container size = " << container.size() << std::endl;
    for (int i = 0; i < container.size(); i++) {
        std::cout << container[i] << std::endl;
    }
}

int main() {

    // std::span = C 배열, std::array, std::vector, std::string 등의
    // 연이은 객체 시퀀스를 참조 (refer) 할 때 사용.

    // C 타입 배열 선언의 단점. arr 의 size, length 를 직접적으로 알기 어려움
    int arr[] = {1, 2, 3, 4, 5};
    const int size = sizeof(arr);
    const int len = sizeof(arr) / sizeof(int);
    PrintArray(arr, len);

    // std::span<type T, size_t Extent = dynamic_extent>
    // static_extent = 컴파일 타임에 크기가 정해짐
    // dynamic_extent
    // std::span 은 포인터 (시작 주소) + 크기 정보만 가지고 있음
    std::vector<int> vec1 { 1, 2, 3, 4, 5};
    std::vector<int> vec2 { 6, 7, 8, 9, 10};
    std::span<int> dynamic_span(vec1); // 가변 사이즈
    std::span<int, 5> static_span(vec2); // 고정 사이즈
    Print(dynamic_span);
    Print(static_span);

    // 포인터 + 사이즈를 이용해서 직접 span 생성
    std::span<int> span1(vec1.data(), vec1.size());
    Print(span1);

    // 부분적으로 잘라서 만들기
    std::span<int> span2(span1.subspan(1, span1.size() - 3));
    Print(span2);

    // 1 ~ 2 범위 대상으로 3에 기록한다.
    std::transform(span1.begin(), span1.end(), span1.begin(), [](int i) { return i * i; });
    Print(vec1); // Span 을 수정하면 원본 데이터도 같이 수정된다.
}
