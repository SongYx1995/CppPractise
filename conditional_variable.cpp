#include <iostream>
#include <condition_variable>
#include <thread>
#include <string>
#include <unistd.h>

std::mutex m;
std::condition_variable cv;
bool ready = false;
bool processed =false;
std::string data;
void worker_thread() {
    std::unique_lock<std::mutex> lk(m);
    std::cout << "Worker thread Begin\n";
    cv.wait(lk, []{return ready;});
    std::cout << "Worker thread is processing data\n";

    data += " after processing";
    processed = true;
    lk.unlock();
    cv.notify_one();
}
int main() {
    std::thread worker(worker_thread);
    sleep(1);
    {
        std::lock_guard<std::mutex> lg(m);
        data = "Example data";
        ready = true;
        std::cout << "main() data is ready for processing\n";
    }
    cv.notify_one();
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << std::endl;
    worker.join();
}