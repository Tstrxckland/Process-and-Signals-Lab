#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t alarm_received = 0;

void handler(int sig)
{
    printf("Hello World!\n");
    alarm_received = 1;
}

int main(void)
{
    signal(SIGALRM, handler);

    alarm(5);

    while (!alarm_received)
    {
        pause();
    }

    printf("Turing was right!\n");

    return 0;
}