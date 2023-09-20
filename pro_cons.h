#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <boost/lockfree/queue.hpp>
#include <queue>
using namespace std::literals;

std::mutex m;
std::condition_variable cv;
bool data_ready = false;
boost::lockfree::queue<int> shared_data;
std::queue<int> shared_data;

void consumer()
{
    while (1) {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [] { return data_ready; });

        shared_data.pop();
        std::cout << "consume :" << shared_data.size() << std::endl;
        
    }
}
void producer()
{
    while (1) {

        {
            std::lock_guard<std::mutex> lg(m);

            shared_data.push(1);
            std::cout << "producer " << shared_data.size() << std::endl;
            

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