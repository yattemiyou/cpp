#include <fcntl.h>
#include <semaphore.h>
#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define NAME "/sample"

int main(int argc, char *argv[])
{
    pid_t pid = getpid();

    // 「ls -l /dev/shm/sem.sample」
    sem_t *semaphore = sem_open(NAME, O_CREAT, 0600, 1);

    for (int i = 0; i < 10; i++)
    {
        sem_wait(semaphore);

        sleep(1);
        printf("%d : %d\n", pid, time(NULL));

        sem_post(semaphore);
        sched_yield();
    }

    sem_close(semaphore);

    sem_unlink(NAME);

    return 0;
}
