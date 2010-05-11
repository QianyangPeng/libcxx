//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <condition_variable>

// class condition_variable_any;

// template <class Lock, class Clock, class Duration>
//   cv_status
//   wait_until(Lock& lock, const chrono::time_point<Clock, Duration>& abs_time);

#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <cassert>

struct Clock
{
    typedef std::chrono::milliseconds duration;
    typedef duration::rep             rep;
    typedef duration::period          period;
    typedef std::chrono::time_point<Clock> time_point;
    static const bool is_monotonic =  true;

    static time_point now()
    {
        using namespace std::chrono;
        return time_point(duration_cast<duration>(
                monotonic_clock::now().time_since_epoch()
                                                 ));
    }
};

std::condition_variable_any cv;

typedef std::timed_mutex L0;
typedef std::unique_lock<L0> L1;

L0 m0;

int test1 = 0;
int test2 = 0;

int runs = 0;

void f()
{
    L1 lk(m0);
    assert(test2 == 0);
    test1 = 1;
    cv.notify_one();
    Clock::time_point t0 = Clock::now();
    Clock::time_point t = t0 + Clock::duration(250);
    while (test2 == 0 && cv.wait_until(lk, t) == std::cv_status::no_timeout)
        ;
    Clock::time_point t1 = Clock::now();
    if (runs == 0)
    {
        assert(t1 - t0 < Clock::duration(250));
        assert(test2 != 0);
    }
    else
    {
        assert(t1 - t0 - Clock::duration(250) < Clock::duration(5));
        assert(test2 == 0);
    }
    ++runs;
}

int main()
{
    {
        L1 lk(m0);
        std::thread t(f);
        assert(test1 == 0);
        while (test1 == 0)
            cv.wait(lk);
        assert(test1 != 0);
        test2 = 1;
        lk.unlock();
        cv.notify_one();
        t.join();
    }
    test1 = 0;
    test2 = 0;
    {
        L1 lk(m0);
        std::thread t(f);
        assert(test1 == 0);
        while (test1 == 0)
            cv.wait(lk);
        assert(test1 != 0);
        lk.unlock();
        t.join();
    }
}