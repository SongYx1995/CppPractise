#include <future>
#include <iostream>
#include <thread>
#include <memory>

void test_future() {
    std::cout << "<--- test_future BEGIN --->" << std::endl;

    std::promise<int> p;
    std::future<int> fut = p.get_future();

    std::unique_ptr<std::thread> thread(new std::thread([&p]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p.set_value(10);
    }));
    // fut.wait();
    int ret = fut.get();
    std::cout << ret << std::endl;
    thread->join();
    std::cout << "<--- test_future END --->" << std::endl;

}

void test_future_exception() {
    std::cout << "<--- test_future_exception BEGIN --->" << std::endl;
    std::promise<int> p;
    std::future<int> fut = p.get_future();

    std::unique_ptr<std::thread> thread(new std::thread([&p]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        try {
            throw(std::exception());
        } catch (std::exception& e) {
            p.set_exception(std::current_exception());
        }
    }));
    fut.wait();

    try {
        int ret = fut.get();
    } catch (std::exception e) {
        std::cout << "exception thrown" << std::endl;
    }
    // std::cout << ret << std::endl;
    thread->join();
    std::cout << "<--- test_future_exception END --->" << std::endl;
}

void test_future_wait() {
    std::cout << "<--- test_future_wait BEGIN --->" << std::endl;

    std::promise<int> p;
    std::future<int> fut = p.get_future();

    std::unique_ptr<std::thread> thread(new std::thread([&p]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p.set_value(10);
    }));
    std::future_status status = fut.wait_for(std::chrono::milliseconds(50));
    switch (status) {
        case std::future_status::timeout:
            std::cout << "timeout" << std::endl;
            break;
        case std::future_status::deferred:
            std::cout << "deferred" << std::endl;
            break;
        case std::future_status::ready:
            std::cout << "ready" << std::endl;
            break;
    }
    thread->join();
    std::cout << "<--- test_future_wait END --->" << std::endl;
}

int main() {
    test_future();
    test_future_exception();
    test_future_wait();
}