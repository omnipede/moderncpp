#include <iostream>
#include <atomic>
#include <semaphore>
#include <thread>
#include <latch>
#include <barrier>

// Semaphore
std::counting_semaphore<1> sem(0);
std::vector<int> vec;

void PrepareWork() {
    vec.insert(vec.end(), {1, 2, 3, 4, 5});
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "데이터 준비됨" << std::endl;
    sem.release();
}

void CompleteWork() {
    std::cout << "데이터 기다리는 중 ..." << std::endl;
    sem.acquire();
    std::cout << "데이터 출력중 ..." << std::endl;
    for (auto n: vec)
        std::cout << n << std::endl;
}

// latch
std::latch workDone(5);
std::mutex countMutex;

void Print(std::string msg) {
    countMutex.lock();
    std::cout << msg << std::endl;
    countMutex.unlock();
}

void DoWork(std::string name) {
    Print(name);
    // Do something
    workDone.arrive_and_wait(); // decrement + blocking
}

void TestLatch() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++)
        threads.push_back(std::thread(DoWork, "thread" + std::to_string(i)));

    for (int i = 0; i < 5; i++)
        threads[i].join();

    std::cout << "Jobs done" << std::endl;
}

// barrier
std::barrier workDone2(5);

void DoFullTimeJob() {
    workDone2.arrive_and_wait(); // 카운트 1 줄이고 0 될 때까지 대기
    Print("Morning Job done!");

    workDone2.arrive_and_wait(); // 카운트 1 줄이고 0 될 때까지 대기
    Print("Afternoon Job done!");
}

void DoPartTimeJob() {
    workDone2.arrive_and_drop(); // 카운트 1 줄이고 0 될 때까지 대기. 그리고 다음 카운트 "초기값" 1 감소.
    Print("Morning Job done!");
}

void TestBarrier() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; i++)
        threads.push_back(std::thread(DoFullTimeJob));

    for (int i = 0; i < 2; i++)
        threads.push_back(std::thread(DoPartTimeJob));

    for (auto& t: threads)
        t.join();
}

int main() {

    // Atomic
    // atomic_ref
    int value = 0;
    int&ref = value;
    // std::atomic_ref<int>& ref = value; // <-- atomic_ref 로 해결가능하지만 .. 아직 mac clang++ 에는 구현 안된 것 같다.
    std::thread t1([&ref]() {
        for (int i = 0; i < 1000000; i++)
            ref ++;
    });
    std::thread t2([&ref]() {
        for (int i = 0; i < 1000000; i++)
            ref --;
    });
    t1.join();
    t2.join();
    std::cout << ref << std::endl;
    // atomic shared_ptr
    // modern c++ 은 생 포인터 대신 스마트 포인터 지향
    // thread-safe?
    // smart pointer = [resource block][control block (ref count)]
    //  - control block 은 thread safe 하다.
    class User {
    public:
        int id = 0;
        int hp = 0;
    };
    std::shared_ptr<User> user_ptr = std::make_shared<User>();
    // std::atomic<std::shared_ptr<User>> atomic_user_ptr = std::make_shared<User>();

    //----
    // Semaphore 가 C++20 에 추가되었다.
    // mutex
    // std::counting_semaphore<3>
    // std::binary_semaphore = counting_semaphore<1>

    // max(): 최대 카운터 값
    // acquire(): counter 를 1만큼 감소, 0이면 양수가 될 때 까지 대기
    // release(upd): counter 를 upd 만큼 증가 (대기하던 쓰레드가 있으면 풀어줌)
    // try_acquire(): 카운터가 0보다 크면 1감소
    // try_acquire_for(relTime): 최대 relTime 만큼 counter 를 1 감소하려 시도
    // try_acquire_until(absTime): 최대 absTime 까지 counter 를 1 감소하려 시도

    std::thread st1(PrepareWork);
    std::thread st2(CompleteWork);
    st1.join();
    st2.join();

    //----
    // Latch & barrier
    // latch: 1회용
    // barrier: 재사용 가능. 즉, count 값이 다 소모되면 다시 회복된다.
    TestLatch();
    TestBarrier();

    //----
    // jthread: joining thread. 자동으로 join 이 되는 thread
    // std::jthread jt(ThreadMain);
    // cooperative interruption
    // jt.request_stop(); // 말 그대로 요청한 것이고, 요청을 받지 않으면 의미가 없음.
}
