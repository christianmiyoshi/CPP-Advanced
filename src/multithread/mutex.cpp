#include <execution>
#include <numeric>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
 
using namespace std;

atomic_flag spinlock = ATOMIC_FLAG_INIT;
static const size_t NumberTheads {50};
static const size_t LoopsPerThread {100};

void spinlockWork(size_t threadNumber, vector<size_t>& data) {
    for (size_t i {0}; i < LoopsPerThread; i++) {
        while (spinlock.test_and_set()) {}
        data.push_back(threadNumber);
        spinlock.clear();
    }
}

void spinLock(){
    // Simple option only if thread will look the spinlock for bried moments
    vector <size_t> data;
    vector <thread> threads;
    for (int i{0}; i < 50; i++) {
        threads.push_back(thread {spinlockWork, i, ref(data)});
    }
    for (auto& t: threads) {
        t.join();
    }
    cout << "Spinlock" << endl;
    cout << "Expected size: " << NumberTheads * LoopsPerThread << endl;
    cout << "Size: " << data.size() << "\n" << endl;
}

mutex mut1;
void lockGuardWork(int id) {
    lock_guard<mutex> lock (mut1);
    cout << "Thread " << id << " is executing\n";
} // Lock is released when lock goes out of scope

void lockGuard(){ // Simplest lock
    // DO NOT USE lock() or unlock() from mutex mannually
    // Resource acquistion in initialization (RAII) should be used instead

    cout << "lockGuard" << endl;

    thread t1 {lockGuardWork, 1};
    thread t2 {lockGuardWork, 2};

    t1.join();
    t2.join();
}

void uniqueLockWork(int id){
    unique_lock<mutex> lock(mut1); // Lock is acquired
    cout << "Thread " << id << " is executing.\n";
    lock.unlock();
    this_thread::sleep_for(10ms);
    lock.lock();
    cout << "Thread " << id << " finished.\n";
} // Lock released when lock goes out of scope

shared_timed_mutex ms_sharedMutex;
void uniqueLockTime(int id){
    unique_lock lock {ms_sharedMutex, 200ms};
    if (lock) {
        cout << "lock acquired" << endl;
    } else {
        cout << "lock not acquired" << endl;
    }

} // Lock released when lock goes out of scope

void uniqueLock(){
    cout << "uniqueLock" << endl;
    thread t1 {uniqueLockWork, 1};
    thread t2 {uniqueLockWork, 2};
    thread t3 {uniqueLockTime, 3};

    t1.join();
    t2.join();
    t3.join();
}

shared_mutex sharedMtx;
int sharedData = 0;

void reader(int id) {
    std::shared_lock<shared_mutex> lock(sharedMtx);
    std::cout << "Reader " << id << " sees data: " << sharedData << "\n";
}

void writer(int id) {
    std::unique_lock<std::shared_mutex> lock(sharedMtx);
    sharedData += 10;
    std::cout << "Writer " << id << " updated data to: " << sharedData << "\n";
}

void sharedLock(){
    cout << "sharedLock" << endl;
    std::thread t1(reader, 1);
    std::thread t2(writer, 1);
    std::thread t3(reader, 2);

    t1.join();
    t2.join();
    t3.join();
}

mutex m1;
mutex m2;
void multipleLock(){
    cout << "multipleLock" << endl;
    unique_lock lock1 {m1, defer_lock};
    unique_lock lock2 {m2, defer_lock};

    lock(lock1, lock2);
    cout << "Lock 1 and 2 acquired" << endl;
} // Lock automatically released

void scopedLock(){
    // multipleLockAlternative
    cout << "scoped_lock" << endl;
    scoped_lock locks {m1, m2};
    cout << "Lock 1 and 2 acquired" << endl;
} // Lock automatically released

once_flag g_onceFlag;
void inicializeSharedResource()
{
    cout << "Shared resource initialized" << endl;
}

void callOnceWork(){
    call_once(g_onceFlag, inicializeSharedResource);
    cout << "Processing" << endl;
}

void callOnce() {
    cout << "callOnce" << endl;
    vector <thread> threads;
    for (int i{0}; i < 3; i++) {
        threads.push_back(thread {callOnceWork});
    }
    for (auto& t: threads) {
        t.join();
    }    
}

int main()
{
    spinLock(); 
    lockGuard();
    uniqueLock();
    sharedLock();
    multipleLock();
    scopedLock();
    callOnce();
    return 0;
}