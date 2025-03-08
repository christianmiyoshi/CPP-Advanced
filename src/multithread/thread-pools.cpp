#include <iostream>
#include <tbb/task_group.h>
#include <tbb/global_control.h>
#include <chrono>

using namespace std;

void task_function(int id) {
    cout << "Task " << id << " is executing on thread " << this_thread::get_id() << "\n";
    this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
}

void threadPoolsTBBExample(){
    cout << "threadPoolsTBBExample\n";
    tbb::global_control control(tbb::global_control::max_allowed_parallelism, 4);

    tbb::task_group tg;

    for (int i = 0; i < 10; i++) {
        tg.run([i] { task_function(i); });
    }

    tg.wait();
    cout << "All tasks completed!\n";
}

int main()
{
    threadPoolsTBBExample();
    return 0;
}