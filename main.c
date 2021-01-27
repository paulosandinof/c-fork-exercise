#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

char *get_time()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return asctime(timeinfo);
}

void delay(int number_of_seconds)
{
    time_t rawtime;
    time(&rawtime);

    time_t end_time = rawtime + number_of_seconds;

    time_t current_time;

    printf("Current time: %li \n", time(&current_time));
    printf("End time: %li \n", end_time);

    while (time(&current_time) != end_time)
        ;
}

int main()
{
    printf("Processo pai nasceu: %s \n", get_time());
    fflush(stdout);

    sleep(14);
    //delay(30);

    pid_t pid_filho_1;
    pid_filho_1 = fork();

    if (!pid_filho_1)
    {
        printf("Filho 1 nasceu: %s \n", get_time());
        fflush(stdout);

        sleep(12);

        pid_t pid_neto_1;
        pid_neto_1 = fork();

        if (!pid_neto_1)
        {
            printf("Neto 1 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(12);

            printf("Neto 1 morreu: %s \n", get_time());
            fflush(stdout);
        }
        else
        {
            sleep(18);

            printf("Filho 1 morreu: %s \n", get_time());
            fflush(stdout);

            // kill(pid_filho_1, SIGTERM);
        }

        return 0;
    }
    else
    {
        sleep(2);

        pid_t pid_filho_2;
        pid_filho_2 = fork();

        if (!pid_filho_2)
        {
            printf("Filho 2 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(14);
            pid_t pid_neto_2;
            pid_neto_2 = fork();

            if (!pid_neto_2)
            {
                printf("Neto 2 nasceu: %s \n", get_time());
                fflush(stdout);

                sleep(18);

                printf("Neto 2 morreu: %s \n", get_time());
                fflush(stdout);

                // kill(pid_neto_2, SIGTERM);
            }
            else
            {
                sleep(16);

                printf("Filho 2 morreu: %s \n", get_time());
                fflush(stdout);

                // kill(pid_filho_2, SIGTERM);
            }
        }
        else
        {
            sleep(44);
            printf("Processo pai morreu: %s", get_time());
        }
    }

    return 0;
}