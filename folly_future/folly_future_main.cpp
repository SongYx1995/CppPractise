#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
#include <iostream>

folly::Future<int> get_future() {
    auto promise = std::make_shared<folly::Promise<int>>();
    auto fut = promise->getFuture();

    std::thread async_job([promise]{
        // do something
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // set promise
        promise->setValue(0);
    });
    async_job.detach();
    return fut;
}

void test_0() {
    folly::Future<int> fut = get_future();
    fut.wait();
    std::cout << fut.value() << std::endl;
}

// void test_1() {
//     folly::ThreadedExecutor executor;
//     folly::Promise<int> pro = get_future();
//     folly::Future<int> fut = pro.getSemiFuture().via(&executor);
//     auto f2 = fut.thenValue([](int) {
//         std::cout << "process 1" << std::endl;
//     });
// }

int main() {
    test_0();
    // test_1();
}