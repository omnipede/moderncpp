#include <iostream>
#include <bit>
#include <bitset>
// Bit operation (비트 연산)

int main() {

    // 암호학
    // 게임서버 ID
    // 기타 알고리즘 문제

    // 모든 토핑이 추가됨
    unsigned int full_pizza = (1 << 20) - 1;

    // 토핑 추가
    unsigned int toppings = 0;
    enum {
        PEPERONI = 3
    };
    toppings |= (1 << PEPERONI); // 3번 토핑 추가

    //포함 여부 확인
    bool added = ((toppings & ( 1 << PEPERONI)));

    // 삭제
    toppings &= ~(1 << PEPERONI);

    // 토글
    toppings ^= (1 << PEPERONI);

    // 엔디안
    // std::endian::native;
}