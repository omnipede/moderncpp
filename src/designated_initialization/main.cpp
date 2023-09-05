#include <iostream>

// Designated initialization

struct Pos2D {
    int x;
    int y;
};

class Pos3D {
public:
    int x;
    int y;
    int z;
};

int main() {

    // Aggregate initialization
    // - 직접 만든 생성자가 없어야 한다.
    // - 가상 함수 없어야 한다.
    // - private / protected / static 인 data 변수
    Pos3D pos {0, 1, 2}; // 선언된 변수 순서대로 들어간다.

    // 만약 변수가 많아지면 일일이 채우는것은 손이 많이 간다.
    // 모든 변수를 채우는게 아니라 일부 변수를 채울수는 없다.
    // 이를 해결하기 위한 것이 designated initialization
    Pos2D pos2d { .x = 2, .y = 3}; // 특히 struct 초기화에 도움이 된다.
    Pos3D pos3d { .x = 2, .z = 3 }; // 단, 변수 선언 순서는 지켜야 한다.
}