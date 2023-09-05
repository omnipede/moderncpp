#include <iostream>
#include <vector>

// Range-based For with Initializer

struct User {
    int id;
};

User* GetUser() {
    return nullptr;
}

int main() {

    // C++17
    // if w/ initializer
    if (int a = 10; a == 10) {
        std::cout << a << std::endl;
    }

    // if 내부에 user 를 선언함으로써 아래쪽에서 user 라는 변수명을 재사용할 수 있다.
    if (User* user = GetUser(); user == nullptr || user->id == 0) {
        // 에러 처리
    }

    // Switch w/ initializer
    switch (int b = 3; b) {
        case 2:
            break;
        case 3:
            std::cout << "HERE!" << std::endl;
            break;
    }

    // Range-based for
    for (std::vector<int> vec {1, 2, 3}; auto v: vec) {
        std::cout << v << std::endl;
    }
}