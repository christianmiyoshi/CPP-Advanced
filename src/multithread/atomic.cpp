#include <execution>
#include <numeric>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
 
using namespace std;

void increment (int& counter) {
    for (int i{0}; i < 100; i++) {
        counter++;
        this_thread::sleep_for(1ms);
    }
}

void data_race(){
    int counter {0};
    vector <thread> threads;
    for (int i{0}; i < 10; i++) {
        threads.push_back(thread{increment, ref(counter)});
    }
    for (auto& t: threads) {
        t.join();
    }
    cout << "Result Data Race: " << counter << endl;
}

void increment_atomic (atomic<int>& counter) {
    for (int i{0}; i < 100; i++) {
        counter++;
        this_thread::sleep_for(1ms);
    }
}

void increment_atomic_option_2 (int& counter) {
    atomic_ref<int> atomicCounter {counter};
    for (int i{0}; i < 100; i++) {
        atomicCounter++;
        this_thread::sleep_for(1ms);
    }
}

void increment_atomic_best_version (atomic<int>& counter) {
    int result {0};
    for (int i{0}; i < 100; i++) {        
        this_thread::sleep_for(1ms);
    }
    counter += result;
}

void atomic_safe(){
    atomic<int> counter {0};
    vector <thread> threads;
    for (int i{0}; i < 10; i++) {
        threads.push_back(thread{increment_atomic, ref(counter)});
    }
    for (auto& t: threads) {
        t.join();
    }
    cout << "Result Atomic Safe: " << counter << endl;
}

int main()
{
    data_race();
    atomic_safe();
    return 0;
}