#include "Consumer.h"

#include <chrono>
#include <iostream>

using std::chrono::seconds;
using std::chrono::steady_clock;

Consumer::Consumer(bool &notify, std::mutex &mtx, std::condition_variable &cv) : notify(notify), mtx(mtx), cv(cv)
{
}

void Consumer::start()
{
    flag = false;

    task = std::async(std::launch::async, &Consumer::run, this);
}

void Consumer::stop()
{
    flag = true;

    task.wait();
}

void Consumer::run()
{
    while (!flag)
    {
        std::cout << "待機中" << std::endl;
        std::cout << "------" << std::endl;

        std::unique_lock<std::mutex> lk(mtx);

        auto timeout = steady_clock::now() + seconds(5);
        auto is_notify = cv.wait_until(lk, timeout, [this]
                                       { return notify; });
        if (!is_notify)
        {
            std::cout << "タイムアウト" << std::endl;
            break;
        }

        notify = false;

        std::cout << "処理中" << std::endl;
    }
}
