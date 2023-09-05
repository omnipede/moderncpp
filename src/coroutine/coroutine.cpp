#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>
#include "my_coroutine.h"

// Coroutine

struct CoroutineObject {
    // 1) promise 객체는 다음과 같은 인터페이스를 제공해야 함
    // - 기본 생성자: promise 객체는 기본 생성자로 만들어질 수 있어야 함
    // - get_return_object: 코루틴 객체를 반환
    // - return_value(val): co_return val 에 의해 호출
    // - return_void(): co_return; 에 의해 호출
    // - yield_value(val): co_yield 에 의해 호출
    // - initial_suspend(): 코루틴이 실행 전에 중단 / 연기될 수 있는지
    // - unhandled_exception(): 예외 처리시 호출됨
    struct promise_type {
        CoroutineObject get_return_object() { return {};}
        std::suspend_never initial_suspend() const noexcept { return {}; }
        std::suspend_never final_suspend() const noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

CoroutineObject hello_coroutine() {
    co_return;
}

Future<int> create_future() {
    co_return 2021;
}

Generator<int> create_numbers(int start = 0, int delta = 1) {
    int now = start;
    while(true) {
        co_yield now;
        now += delta;
    }
}

Job prepare_job() {
    co_await std::suspend_never();
}

int main() {
    // 함수가 coroutine 이 되려면 ...
    // - co_return
    // - co_yield
    // - co_await

    // 코루틴을 사용할 수 있는 Framework 를 제공
    // 3가지 요소로 구성
    // - promise 객체
    // - 코루틴 헨들 (밖에서 코루틴 resume / destory 할 때 사용하는 일종의 리모컨)
    // - 코루틴 프레임 (promise 객체, 코루틴의 인자 등을 포함하는 heap 할당 객체)

    // co_yield, co_await, co_return 을 함수 안에서 사용하면, 그 함수는 코루틴이 됨.
    // 예를 들어 다음과 같은 흐름으로 의사 코드가 생성됨
    /**
     * {
     *  Promise prom; (get_return_object)
     *  co_await prom.initial_suspend();
     *  try {
     *      // co_return, co_yield, co_await 를 포함하는 코드
     *  } catch(...) {
     *      prom.unhandled_exception();
     *  }
     *  co_await prom.final_suspend();
     * }
     */
    // co_await 플로우
    /**
     * {
     *  if awaitable.await_ready() returns false;
     *      suspend coroutine
     *      awaitable.await_suspend(handle) returns:
     *          void:
     *              awaitable.await_suspend(handle);
     *              coroutine kees suspended
     *              return to caller
     *         bool:
     *              bool result = awaitable.await_suspend(handle);
     *              if (result)
     *                  coroutine keeps suspended
     *                  return to caller
     *              else
     *                  return awaitable.await_resume()
     *         another coroutine handle:
     *              anotherCoroutineHandle = awaitable.await_suspend(handle);
     *              anotherCoroutineHandle.resume();
     *              return to caller;
     * }
     */
    hello_coroutine();

    // 예제 1.
    auto future = create_future();
    // ... some operations ...
    std::cout << future.get() << std::endl;

    // 예제 2.
    auto numbers = create_numbers(0, 1);
    for (int i = 0; i < 20; i++) {
        numbers.next();
        std::cout << " " << numbers.get();
    }
    std::cout << std::endl;

    // 예제 3.
    auto job = prepare_job();
    job.start();
    return 0;
}
