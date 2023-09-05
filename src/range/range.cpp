#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>

// Custom view 생성. 사용도는 떨어진다.
template<std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView: public std::ranges::view_interface<ContainerView<Range>> {
public:
    ContainerView() = default;
    constexpr ContainerView(Range r): _range(std::move(r)), _begin(std::begin(r)), _end(std::end(r)) {

    }
    constexpr auto begin() const { return _begin; }
    constexpr auto end() const { return _end; }
private:
    Range _range;
    std::ranges::iterator_t<Range> _begin;
    std::ranges::iterator_t<Range> _end;
};

template<typename Range>
ContainerView(Range&& range) -> ContainerView<std::ranges::views::all_t<Range>>;

int main() {
    // Range: 순회할 수 있는 아이템 그룹 (ex. STL Container)
    // View: Range 에 적용할 수 있는 연산

    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 짝수 추출
    std::vector<int> v2;
    for (int n: v1) {
        if (n % 2 == 0)
            v2.push_back(n);
    }
    // 짝수 추출: range 이용.
    auto results = v1 | std::views::filter([](int n) {return n % 2 == 0;})
            | std::views::transform([](int n) { return n * 2; })
            | std::views::take(3);

    for (auto n: results)
        std::cout << n << " ";
    std::cout << std::endl;

    // Sorting
    std::ranges::sort(v1);
    struct Knight {
        std::string name;
        int id;
    };
    std::vector<Knight> knights = {
            {"Rookiss", 1},
            {"Faker", 2},
            {"Dopa", 3},
            {"Deft", 4}
    };

    std::ranges::sort(knights, {}, &Knight::name);
    std::ranges::sort(knights, std::ranges::greater(), &Knight::name);
    std::ranges::sort(knights, {}, &Knight::name);
    std::ranges::sort(knights, std::ranges::greater(), &Knight::id);

    std::map<std::string, int> m = {
            {"Rookiss", 1},
            {"Faker", 2},
            {"Dopa", 3},
            {"Deft", 4}
    };
    for (const auto& name: std::views::keys(m) | std::views::reverse)
        std::cout << name << " ";
    std::cout << std::endl;

    // 0 ~ 100 사이 숫자 중 소수인 5개 숫자를 추출
    std::vector<int> v3;
    auto is_prime = [](int num) {
        if (num <= 1)
            return false;
        for (int n = 2; n * n <= num; n++) {
            if (num % n == 0)
                return false;
        }
        return true;
    };
    for (int n : std::views::iota(0, 100) | std::views::filter(is_prime) | std::views::take(5)) {
        v3.push_back(n);
    }

    // 커스텀 뷰
    std::vector<int> my_vec { 1, 2, 3, 4, 5};
    auto my_view = ContainerView(my_vec);
    for (auto n: my_view)
        std::cout << n << " ";
    std::cout << std::endl;
}
