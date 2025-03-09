#include <iostream>
#include <tbb/task_group.h>
#include <tbb/global_control.h>
#include <chrono>
#include <tbb/parallel_for.h>

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

void tbbParallelFor(){
    cout << "tbbParallelFor\n";
    tbb::parallel_for(0, 10, [](int i) {
        std::cout << "Processando " << i << " na thread " << std::this_thread::get_id() << "\n";
    });
}

int main()
{
    threadPoolsTBBExample();
    tbbParallelFor();
    return 0;
}