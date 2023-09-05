#pragma once
#include <coroutine>
#include <iostream>

// 코루틴 객체
template<typename T>
class Future {
public:
    Future(std::shared_ptr<T> value): _value(value) {}
    T get() { return * _value; }
private:
    std::shared_ptr<T> _value;
public:
    struct promise_type {
        // data
        std::shared_ptr<T> _ptr = std::make_shared<T>();
        // methods
        Future<T> get_return_object() { return Future<T>(_ptr); }
        void return_value(T value) { *_ptr = value; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
    };
};

// 코루틴 객체 2
template<typename T>
class Generator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    Generator(handle_type handle): _handle(handle) {}

    ~Generator() {
        if (_handle)
            _handle.destroy();
    }

    T get() { return _handle.promise()._value; }

    bool next() {
        _handle.resume(); // 중요!
        return !_handle.done();
    }
private:
    handle_type _handle;

public:
    struct promise_type {
        // Data
        T _value;
        // Methods
        Generator<T> get_return_object() { return Generator(handle_type::from_promise(*this)); }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(const T value) { _value = value; return {}; }
        std::suspend_always return_void() { return {}; }
        void unhandled_exception() {}
    };
};

class Job {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    Job(handle_type handle): _handle(handle) {}
    ~Job() {
        if (_handle)
            _handle.destroy();
    }
    void start() {
        if (_handle)
            _handle.resume();
    }
private:
    handle_type _handle;
public:
    struct promise_type {
        Job get_return_object() { return Job(handle_type::from_promise(*this)); }
        std::suspend_always initial_suspend() { std::cout << "Prepare Job" << std::endl; return {}; }
        std::suspend_always final_suspend() noexcept { std::cout << "Do Job" << std::endl; return {}; }
        std::suspend_never return_void() { return {}; }
        void unhandled_exception() {}
    };
};