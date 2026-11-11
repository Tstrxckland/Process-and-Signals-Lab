#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_received = 0;
volatile sig_atomic_t alarm_count = 0;
volatile sig_atomic_t stop_program = 0;

time_t start_time;

void alarm_handler(int sig)
{
    alarm_count++;
    printf("Hello World!\n");

    alarm_received = 1;

    alarm(1);
}

void int_handler(int sig)
{
    stop_program = 1;
}

int main(void)
{
    time_t end_time;

    start_time = time(NULL);

    signal(SIGALRM, alarm_handler);
    signal(SIGINT, int_handler);

    alarm(1);

    while (!stop_program)
    {
        pause();

        if (alarm_received)
        {
            printf("Turing was right!\n");
            alarm_received = 0;
        }
    }

    end_time = time(NULL);

    printf("\nProgram executed for %ld seconds.\n",
           (long)(end_time - start_time));

    printf("Total alarms received: %d\n",
           (int)alarm_count);

    return 0;
}