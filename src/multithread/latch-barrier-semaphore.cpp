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

using namespace std;


void latchExample() {
    cout << "latchExample" << endl;
    latch startLatch {1};

    vector<jthread> threads;

    for (int i{0}; i < 10; i++) {
        threads.push_back(
            jthread {
                [&startLatch] {
                    cout << "Initialize" << endl;
                    startLatch.wait();
                    // startLatch.arrive_and_wait();
                    cout << "Processing" << endl;
                }
            }
        );
    }

    cout << "Loading data" << endl;
    startLatch.count_down();    
}


void barrierCompletionFunction(){
    cout << "Barrier completion function" << endl;
}
void barrierExample(){
    cout << "\nbarrierExample" << endl;
    int numberThreadsBarrier {4};
    barrier barrierPoint {numberThreadsBarrier, barrierCompletionFunction};
    vector<jthread> threads;

    for (int i{0}; i < numberThreadsBarrier * 3; i++) {
        threads.push_back(
            jthread {
                [&barrierPoint, i] () {
                    cout << "Processing iteration " << i << endl;
                    barrierPoint.arrive_and_wait();                    
                }
            }
        );
    }    
}

void semaphoreExample(){
    cout << "\nsemaphoreExample" << endl;

    vector<jthread> threads;
    counting_semaphore semaphore {4};
    // binary_semaphore        

    for (int i{0}; i < 10 ; i++) {
        threads.push_back(jthread{
            [i, &semaphore] {
                semaphore.acquire();
                cout << "Processing " << i << endl;
                semaphore.release();
            }
        });
    }

}

int main()
{
    latchExample();
    barrierExample();
    semaphoreExample();
    return 0;
}