#include <iostream>
#include <thread>
#include <unistd.h>
#include <atomic>

std::atomic<double> current(0);
double target = 10;

bool terminate =false;
double pre_error = 10;
double sum_error = 0;
void producer() {
    while (!terminate) {
        // p
        double error = target - current;
        double kp = 0.01;

        // i
        double ki = 0.01;
        sum_error += error;

        // d
        double delta_error = error - pre_error;
        double kd = 0.1;

        double input = kp * error;

        input += ki * sum_error;
        input += kd * delta_error;
        current = current + input;
        usleep(10000);
    }
}
void watcher() {
    while (!terminate) {
        std::cout << "target:" << target << ", current: " << current << std::endl; 
        usleep(100000);
    }
}
void destorier() {
    while (!terminate) {
        current = current - 0.01;
        if (current - 10 < 0.01 && current - 10 > -0.01) {
            current = current - 5;
        }
        usleep(10000);
    }
}
int main() {
    std::thread t1(producer);    
    std::thread t2(watcher);
    std::thread t3(destorier);

    sleep(20);
    terminate = true;
    t1.join();
    t2.join();
    t3.join();
}