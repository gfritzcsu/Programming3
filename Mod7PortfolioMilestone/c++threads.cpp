//============================================================================
// -------------------------------------------
// Program Name: C++ Threads Module 7 Portfolio Milestone
// Author: Greg Fritz
// Professor Herbert Pensado
// CSC-450-1 Programming 3
// Date: February 1, 2026
// -------------------------------------------
//============================================================================
//START PROGRAM
//    shared integer counter = 0
//    shared boolean reachedTwenty = false
//
//    create mutex m
//    create condition variable cv
//
//    print "Thread 1 will now count up to 20"
//    FUNCTION CountUp():
//        FOR i from 0 to 20:
//            lock m
//            counter = i
//            print "Thread 1:", counter
//            IF i == 20:
//                reachedTwenty = true
//                notify cv
//            unlock m
//            sleep a short time
//
//    FUNCTION CountDown():
//        lock m
//        wait on cv until reachedTwenty == true
//        unlock m
//
//        print "Thread 2 will now count down to 0"
//        FOR i from 20 down to 0:
//            lock m
//            counter = i
//            print "Thread 2:", counter
//            unlock m
//            sleep a short time
//
//    start thread t1 running CountUp
//    start thread t2 running CountDown
//    join t1
//    join t2
//END PROGRAM

#include <chrono>        
#include <condition_variable>   
#include <iostream>             
#include <mutex>                
#include <thread>               

namespace {

    // Mutex protects shared state for counter and reachedTwenty from race conditions
    std::mutex mtx;

    // Condition variable allows thread 2 to sleep efficiently until thread 1 reaches 20
    std::condition_variable cv;

    // Shared counter value updated by both threads protected by mtx
    int counter = 0;

    // Flag that indicates thread 1 has reached 20 protected by mtx
    bool reachedTwenty = false;

    // Thread 1 counts upward from 0 to 20
    void countUp() {
        std::cout << "Thread 1 will now count up to 20 threads\n";
        for (int i = 0; i <= 20; ++i) {

            // Lock the mutex so only one thread at a time can update shared state and print
            // This helps prevent race conditions and avoids interleaved console output.
            {
                std::lock_guard<std::mutex> lock(mtx);

                // Update shared counter and print current value
                counter = i;
                std::cout << "Thread 1:   " << counter << "\n";

                // When thread 1 reaches 20, set the flag and notify thread 2 to begin
                if (i == 20) {
                    reachedTwenty = true;

                    // notify_one wakes the waiting thread (thread 2) if it is waiting on cv
                    cv.notify_one();
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
    }

    // Thread 2 waits until thread 1 reaches 20, then counts down from 20 to 0
    void countDown() {

        // unique_lock is required for condition_variable::wait as it must be able to unlock/relock
        {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until reachedTwenty becomes true.
            // The predicate prevents missed signals and handles spurious wakeups safely.
            cv.wait(lock, [] { return reachedTwenty; });
        } // lock released here before starting loop as this minimizes time holding the mutex

        std::cout << "Thread 2 will now count down to 0 threads\n";
        for (int i = 20; i >= 0; --i) {

            // Lock while updating shared state and printing
            {
                std::lock_guard<std::mutex> lock(mtx);

                counter = i;
                std::cout << "Thread 2: " << counter << "\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
    }
}

int main() {
    std::cout << "Starting two-thread counter\n\n";

    // Start both threads.
    // Thread 2 will block immediately until thread 1 signals it when it hits 20.
    std::thread t1(countUp);
    std::thread t2(countDown);

    // Join ensures main waits for both threads to finish before exiting
    t1.join();
    t2.join();

    std::cout << "\nDone.\n";
    return 0;
}