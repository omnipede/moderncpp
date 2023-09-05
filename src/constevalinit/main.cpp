// consteval / constinit

int sqr_run_time(int n) {
    return n * n;
}

// c++11
constexpr int sqr_run_or_compile_time(int n) {
    return n * n;
}

// c++20
consteval int sqr_compile_time(int n) {
    return n * n;
}

int main() {
    // 함수 (일반 vs constexpr vs consteval)
    int val1 = sqr_run_time(10); // 실행전에 val1 값을 알 수 없다. 즉 런타임에 결정된다.
    int val2 = sqr_run_or_compile_time(10); // 런타임에 결정된다.
    constexpr int val22 = sqr_run_or_compile_time(10); // 단, constexpr 을 붙이면 컴파일 타임에 결정된다.
    int val3 = sqr_compile_time(10); // 컴파일 타임에 값이 결정된다.

    enum {
//        VAL_1 = sqr_run_time(10), // 런타임에 결정되기 때문에 enum 에서 사용할 수 없다.
        VAL_2 = sqr_run_or_compile_time(10),
        VAL_3 = sqr_compile_time(10)
    };

    // 변수 (const vs constexpr vs constinit)
    // const: (컴파일 타임 / 런타임 상관 없이 constness (상수성)이 있어야 한다.)
    const int const_int_val = sqr_run_time(10);
    // constexpr: (컴파일 타임에 반드시 초기화가 되어야 한다 + constness 있어야 한다.)
    constexpr int constexpr_int_val = sqr_compile_time(10);
    // constinit (컴파일 타임에 초기화 + constness 없음 + static/thread_local)
    // - global 변수, static 변수, thread_local 변수를 대상으로 사용. 즉 일반 변수는 안된다.
    constinit thread_local int const_init_val = sqr_compile_time(10);
    const_init_val+= 1; // constness 없다!
}
