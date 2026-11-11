#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    pid_t pid;
    pid_t completed_pid;
    int status;

    /* Create two child processes */
    for (int i = 0; i < 2; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            /* Seed random number generator differently for each child */
            srandom((unsigned int)(time(NULL) ^ getpid()));

            /* Random number of iterations from 1 to 30 */
            int iterations = (random() % 30) + 1;

            for (int j = 0; j < iterations; j++)
            {
                printf("Child Pid: %d is going to sleep!\n", getpid());
                fflush(stdout);

                /* Sleep for a random amount of time from 1 to 10 seconds */
                int sleep_time = (random() % 10) + 1;
                sleep(sleep_time);

                printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",
                       getpid(), getppid());
                fflush(stdout);
            }

            /* Child process terminates */
            exit(0);
        }
    }

    /* Parent waits for both children */
    for (int i = 0; i < 2; i++)
    {
        completed_pid = wait(&status);

        if (completed_pid > 0)
        {
            printf("Child Pid: %d has completed\n", completed_pid);
        }
    }

    return 0;
}