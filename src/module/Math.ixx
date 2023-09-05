module; // global module fragment

// 각종 외부 헤더 추가

export module Math;
export import Math.Time; // export submodule

// 각종 외부 모듈 추가
// import module AAA...

// 1) 함수 앞에 export
export int add(int a, int b) {
    return a + b;
}

// 2) export 하고 싶은 부분을 따로 묶기
export {
    void TestExport() {

    }
}

// 3) namespace 를 지정 <-- 주로 많이 사용됨
export namespace test {
    void TestExport2() {

    }
}