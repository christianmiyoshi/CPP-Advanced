#include <execution>
#include <numeric>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <latch> 
#include <barrier>
#include <future>

using namespace std;

int calculateSum(int a, int b) {
    return a + b;
}
int calculateThrowException(int a, int b) {
    throw runtime_error{"Exception thrown from calculateThrowException"};
}


void packagedTaskExample () {
    cout << "packagedTaskExample" << endl;
    // Better than using promise explicitly
    packaged_task<int(int, int)> task {calculateSum};
    auto theFuture {task.get_future()};
    thread theThread {move(task), 10, 20};
    int result {theFuture.get()};
    cout << "Result: " << result << endl;
    theThread.join();
}

void asyncExample(){
    cout << "asyncExample" << endl;
    auto myFuture {async(calculateThrowException, 1, 2)};
    auto myFuture2 {async(launch::async, calculateSum, 1, 2)};
    auto myFuture3 {async(launch::deferred, calculateSum, 1, 2)};

    try {
        int result {myFuture.get()};
        cout << result << endl;
    } catch (const exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }

    try {
        int result {myFuture2.get()};
        cout << result << endl;
    } catch (const exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }
}

void sharedFutureExample(){
    // Shared future allow calling future.get() multiple times.
    cout << "sharedFutureExample" << endl;
    promise<void> thread1Started, thread2Started;
    promise<int> signalPromise;
    auto signalFuture {signalPromise.get_future().share()};
    
    auto function1 {[&thread1Started, signalFuture] {
        thread1Started.set_value();
        int parameter { signalFuture.get()};
        cout << "Parameter " << parameter << endl;
    }};

    auto function2 {[&thread2Started, signalFuture] {
        thread2Started.set_value();
        int parameter { signalFuture.get()};
        cout << "Parameter " << parameter << endl;
    }};

    auto result1 {async(launch::async, function1)} ;
    auto result2 {async(launch::async, function2)} ;

    thread1Started.get_future().wait();
    thread2Started.get_future().wait();

    signalPromise.set_value(10);
}


int main()
{
    packagedTaskExample();
    asyncExample();
    sharedFutureExample();
    return 0;
}