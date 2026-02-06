// Program Name: Java Threads Module 7 Portfolio Milestone
// Author: Greg Fritz
// Professor Name here
// CSC-450-1 Programming 3
// Date: February 8, 2026
// Psuedocode
//START PROGRAM
//    shared integer counter = 0
//    shared boolean reachedTwenty = false
//
//    create lock m
//    create condition variable cv
//
//    print "Thread 1 will now count up to 20"
//
//    FUNCTION CountUp():
//        FOR i from 0 to 20:
//            lock m
//            counter = i
//            print "Thread 1:", counter
//            IF i == 20:
//                reachedTwenty = true
//                signal cv
//            unlock m
//            sleep a short time
//
//    FUNCTION CountDown():
//        lock m
//        wait on cv until reachedTwenty == true
//        unlock m
//
//        print "Thread 2 will now count down to 0"
//
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
//============================================================================

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class javathreads {

    // Lock protects shared state counter and reachedTwenty from race conditions
    private static final Lock mtx = new ReentrantLock();

    // Condition allows thread 2 to sleep efficiently until thread 1 reaches 20
    private static final Condition cv = mtx.newCondition();

    // Shared counter value updated by both threads protected by mtx
    private static int counter = 0;

    // Flag that indicates thread 1 has reached 20 protected by mtx
    private static boolean reachedTwenty = false;

    // Thread 1 counts upward from 0 to 20
    private static void countUp() {
        System.out.println("Thread 1 will now count up to 20 threads");
        for (int i = 0; i <= 20; i++) {

            // Lock so only one thread at a time can update shared state and print
            // This helps prevent race conditions and avoids interleaved console output.
            mtx.lock();
            try {
                // Update shared counter and print current value
                counter = i;
                System.out.println("Thread 1:   " + counter);

                // When thread 1 reaches 20, set the flag and signal thread 2 to begin
                if (i == 20) {
                    reachedTwenty = true;

                    // signal wakes one waiting thread thread 2 if it is waiting on cv
                    cv.signal();
                }
            } finally {
                mtx.unlock();
            }

            sleepQuietly(75);
        }
    }

    // Thread 2 waits until thread 1 reaches 20, then counts down from 20 to 0
    private static void countDown() {

        // Wait until reachedTwenty becomes true.
        // The while-loop prevents missed signals and handles spurious wakeups safely.
        mtx.lock();
        try {
            while (!reachedTwenty) {
                try {
                    cv.await();
                } catch (InterruptedException e) {
                    // If interrupted while waiting, restore interrupt status and exit thread
                    Thread.currentThread().interrupt();
                    System.out.println("Thread 2 interrupted while waiting. Exiting.");
                    return;
                }
            }
        } finally {
            // Release lock before the loop to minimize time holding the lock
            mtx.unlock();
        }

        System.out.println("Thread 2 will now count down to 0 threads");
        for (int i = 20; i >= 0; i--) {

            // Lock while updating shared state and printing
            mtx.lock();
            try {
                counter = i;
                System.out.println("Thread 2: " + counter);
            } finally {
                mtx.unlock();
            }

            sleepQuietly(75);
        }
    }

    private static void sleepQuietly(long millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            // Preserve interrupt status (best practice)
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) {
        System.out.println("Starting two-thread counter\n");

        // Start both threads.
        // Thread 2 will block immediately until thread 1 signals it when it hits 20.
        Thread t1 = new Thread(javathreads::countUp, "Thread-1");
        Thread t2 = new Thread(javathreads::countDown, "Thread-2");

        t1.start();
        t2.start();

        // Join ensures main waits for both threads to finish before exiting
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.out.println("Main interrupted. Exiting.");
        }

        System.out.println("\nDone.");
    }
}