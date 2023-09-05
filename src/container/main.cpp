#include <iostream>
#include <vector>
#include <set>
#include <map>

// Container
// 1. vector, string 에 constexpr 사용 가능
// algorithm 100 개 이상의 함수들이 constexpr 로 바뀜.
// 2. std::array 만드는 방법이 추가됨 (std::to_array)
// 3. std::make_shared 를 이용해서 shared_ptr 생성 가능.
// 4. std::erase / std::erase_if
// 5. map / set contains()
// 6. prefix / suffix checking (string starts_with, ends_with)


int main() {

    // to_array 사용.
    auto arr1 = std::to_array("Hello world!");
    for (auto ch: arr1)
        std::cout << ch;
    std::cout << std::endl;
    auto arr2 = std::to_array<int>({1, 2, 3, 4, 5});
    for (auto i: arr1)
        std::cout << i;
    std::cout << std::endl;

    // shared_ptr
//    int* arr3 = new int[10];
//    delete[] arr3;
    std::shared_ptr<int[]> shared_arr = std::make_shared<int[]>(1024);

    // 음수를 삭제하는 경우
    std::vector<int> vec { -1, 2, -3, 4, -5 };
    for (auto it = vec.begin(); it != vec.end(); it ++) {
        int value = *it;
        if (value < 0) {
            // 이렇게 하면 안된다.
            // vec.erase(it);
            it = vec.erase(it);
        } else {
            it ++;
        }
    }

    // 또한, 이렇게 하면 안된다.
    // 함정.
    // -1 2 -3 4 -5
    // 2 4 -3 4 -5 <-- ???
    // std::remove_if(vec.begin(), vec.end(), [](int num) { return num < 0; });
    // new_end 를 받아서 뒤쪽 안 쓰는 값들을 지워줘야 한다.
    auto new_end = std::remove_if(vec.begin(), vec.end(), [](int num) { return num < 0; });
    vec.erase(new_end, vec.end());

    // C++20 std::erase, std::erase_if
    std::vector<int> my_vec = {1, 2, 3, 4, -5};
    std::erase_if(my_vec, [](int num) { return num < 0; });
    for (auto n: vec) {
        std::cout << n << std::endl;
    }

    // map / set contains()
    std::set s { 1, 2, 3, 4, 5 };
    auto findIt = s.find(2);
    if (findIt != s.end()) {
        std::cout << "Found!" << std::endl;
    }
    if (s.contains(2)) {
        std::cout << "Found!" << std::endl;
    }

    std::map<int, int> m{{1, 1000}, {2, 2000}};
    if (m.contains(2)) {
        std::cout << "Found!" << std::endl;
    }

    // string starts_with
    std::string str = "Hello world";
    bool b1 = str.starts_with("Hello");
    bool b2 = str.ends_with("world");
}