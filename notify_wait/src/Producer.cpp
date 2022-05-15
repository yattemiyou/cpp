#include "Producer.h"

#include <iostream>

Producer::Producer(bool &notify, std::mutex &mtx, std::condition_variable &cv) : notify(notify), mtx(mtx), cv(cv)
{
}

void Producer::start()
{
    flag = false;

    task = std::async(std::launch::async, &Producer::run, this);
}

void Producer::stop()
{
    flag = true;

    task.wait();
}

void Producer::run()
{
    while (!flag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        bool waiting = mtx.try_lock();
        if (waiting)
        {
            mtx.unlock();
        }
        else
        {
            std::cout << "処理完了待機" << std::endl;
        }

        std::lock_guard<std::mutex> lk(mtx);
        notify = true;
        cv.notify_all();

        std::cout << "処理開始通知" << std::endl;
    }
}
