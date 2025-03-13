#include <execution>
#include <numeric>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <condition_variable>
 
using namespace std;

auto cv = std::condition_variable{};
auto q = std::queue<int>{};
auto mtx = std::mutex{};
constexpr int done = -1;

void print_ints(){
    auto i = int{0};
    while (i != done) {
        auto lock = std::unique_lock<std::mutex>{mtx};
        while (q.empty()) {
            cv.wait(lock);
        }
        i = q.front();
        q.pop();
        

        if (i!= done) {
            std::cout << "Got: " << i << endl;
        }
    }
}

auto generate_ints(){
    for(auto i: {1, 2, 3, done}) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock (mtx);
            q.push(i);
        }
        cv.notify_one();
    }
}

int main()
{
    cout << "Condition variable" << endl;
    auto producer = std::thread{generate_ints};
    auto consumer = std::thread{print_ints};

    producer.join();
    consumer.join();
    cout << "End" << endl;
}