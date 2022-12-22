#include <iostream>
#include <unistd.h>
#include <thread>
#include <memory>
class DataLoader {
public: 
    DataLoader() {
        terminated_ = false;
    }
    virtual ~DataLoader() {
        terminated_ = true;
        th->join();
    }
    void start() {
        th = std::make_unique<std::thread>(&DataLoader::loop, this);
    }
    void prepare() {
        reload();
    }

private:
    void loop() {
        while (!terminated_) {
            sleep(1);
            reload();
        }
    }
    std::unique_ptr<std::thread> th;
    virtual void reload() {
        std::cout << "Base Reload" << std::endl;
        return;
    }
    bool terminated_ = false;
};

class Data {
public:
    Data() {
        std::cout << "Data Contructed\n";
    }
    ~Data() {
        std::cout << "Data Desotried\n";
    }
    void incr() {
        content++;
        std::cout << "Data Current Content " << content << std::endl;
    }
private:
    int content = 0;
};

class MyDataLoader : public DataLoader {
public:
    MyDataLoader() {
        data_ptr = new Data();
    }
    ~MyDataLoader() {
        delete data_ptr;
    }
    void reload() {
        data_ptr->incr();
    }
private:
    Data* data_ptr;
};

int main() {
    MyDataLoader my_data_loader;
    my_data_loader.prepare();
    my_data_loader.start();
    sleep(5);
}