#include <future>

#include "Producer.h"
#include "Consumer.h"

bool notify = false;
std::mutex mtx;
std::condition_variable cv;

int main(int argc, char *argv[])
{
    Producer p(notify, mtx, cv);
    Consumer c(notify, mtx, cv);

    c.start();
    p.start();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    p.stop();
    c.stop();

    return 0;
}
