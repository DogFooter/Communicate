#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <boost/lockfree/queue.hpp>
#include <queue>
#include <barrier>
using namespace std::literals;

std::mutex m;
std::condition_variable cv;
bool data_ready = false;


constexpr int max = 10000;
boost::lockfree::queue<int> shared_data(max);
//std::queue<int> shared_data;
std::once_flag init_flag;

void complete() noexcept {
    std::cout << " done" << std::endl;

}
std::barrier sync{ 3 ,complete };

void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

struct PrintFunctor {
    void operator()(int value) const {
        std::cout << std::this_thread::get_id() << "Consumed value: " << value << std::endl;
    }
};


void consumer()
{
    int num;

    while (1) {
        std::cout << std::this_thread::get_id() << std::endl;
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [] { return data_ready; });

        shared_data.consume_one(PrintFunctor());
        //sync.arrive_and_wait(); // 한 스레드의 과다소비 방지
    }
}
void producer()
{
    std::call_once(init_flag, init, 10, 3.4); //somthig initialized

    while (1) {

        {
            std::lock_guard<std::mutex> lg(m);

            shared_data.bounded_push(1);
            std::cout << "produced " << std::endl;


            data_ready = true;
        }
        cv.notify_all();
        //    cv.notify_one();
        //    std::this_thread::sleep_for(500ms); 
        //    cv.notify_one();
        //    std::this_thread::sleep_for(500ms); 
        //    cv.notify_one();
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    std::thread t3(consumer);
    std::thread t4(consumer);
    t1.join(); t2.join();
    t3.join(); t4.join();
}
