#ifndef CONSUMER_H
#define CONSUMER_H

#include <future>

class Consumer
{
public:
    Consumer(bool &notify, std::mutex &mtx, std::condition_variable &cv);

    void start();

    void stop();

private:
    void run();

    bool &notify;
    std::mutex &mtx;
    std::condition_variable &cv;

    std::future<void> task;
    std::atomic<bool> flag;
};
#endif
