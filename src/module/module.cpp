
// module 을 사용하면 빌드 속도가 빨라진다.
// - 모듈은 한번만 import 된다.
// - import 순서 차이 없음
// - 심볼 중복 정의
// - 인터페이스/구현부 나눌 필요 없음

// 전처리 (#include)
// 컴파일 (.o 파일 생성)
// 링크 (.so 연결 등)

import Math;
import Math.Time;

#include <iostream>

int main() {
    int c = add(2, 3);
    std::cout << "Add result: " << c << std::endl;
    TestExport();
    math_time_func();
}
