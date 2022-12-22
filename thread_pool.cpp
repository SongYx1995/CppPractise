#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>

class ThreadPool {
public:
    ThreadPool(int thread_num) : thread_num_(thread_num) {
        for (int i = 0; i < thread_num_; i++) {
            workers_.push_back(std::thread(
                [this](){
                    while(true) {
                        if (stop_) {
                            return;
                        }
                        std::function<void()> task;
                        {
                            std::lock_guard<std::mutex> lg(mut_);
                            if (!queue_.empty()) {
                              task = queue_.front();
                              queue_.pop();
                            }
                        }
                        if (task != nullptr) {
                            task();
                        }
                    }
                })
            );
        }
    }
    void enqueue(std::function<void()> f) {
        queue_.push(f);
    }
    ~ThreadPool() {
        stop_ = true;
        for (int i = 0; i < workers_.size(); i++) {
            workers_[i].join();
        }
    }

    // void concurrent_run(std::vector<std::function<void()>> jobs, int timeout_ms, std::vector<bool> &status) {
    //     for (int i = 0; i < jobs.size(); i++) {
    //         enqueue(jobs[i]);
    //     }
    //     for (int )
    // }
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> queue_;
    std::mutex mut_;
    int thread_num_;
    bool stop_ = false;
};


int main() {
    ThreadPool pool(10);
    std::atomic<int> vals[10];
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
        vals[i] = 0;
    }
    pool.enqueue([&vals]{
        vals[0] = 1; 
        std::cout << "worker" << std::endl;
        }
    );

    pool.enqueue([&vals]{
        vals[1] = 2; 
        std::cout << "worker" << std::endl;
        }
    );

    pool.enqueue([&vals]{
        vals[2] = 3; 
        std::cout << "worker" << std::endl;
        }
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
        std::cout << vals[i] << std::endl;
    }
    // auto gen_func = [&vals](int sleep_time_ms, int idx, int val_set) {
    //     return [&vals, sleep_time_ms, idx, val_set]() {
    //        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
    //         vals[idx] = val_set;
    //     };
    // };

    // std::vector<std::function<void()>> func_list = {
    //     gen_func(10, 0, 1),
    //     gen_func(20, 1, 2),
    //     gen_func(30, 2, 3),
    //     gen_func(40, 3, 4),
    //     gen_func(50, 4, 5),
    //     gen_func(60, 5, 6),
    //     gen_func(70, 6, 7),
    //     gen_func(80, 7, 8),
    //     gen_func(90, 8, 9),
    //     gen_func(100, 9, 10),
    // };

    // const int timeout_ms = 55;
    // std::vector<bool> expect_status = {
    //     true, true, true, true, true, false, false, false, false, false
    // };

    // std::vector<bool> status;
    // pool.concurrent_run(func_list, timeout_ms, status);

    // for (size_t i = 0; i < status.size(); i++) {
    //     std::cout << expect_status[i] << " " << status[i] << std::endl;
    // }
}