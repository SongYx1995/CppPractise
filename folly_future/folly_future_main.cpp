#include <folly/futures/Future.h>
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

int main() {
    folly::Future<int> fut = get_future();
    fut.wait();
    std::cout << fut.value() << std::endl;
}