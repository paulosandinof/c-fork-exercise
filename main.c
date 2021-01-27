#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

char *get_time()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return asctime(timeinfo);
}

int main()
{
    printf("Processo pai nasceu: %s \n", get_time());
    fflush(stdout);

    sleep(14);

    pid_t pid_filho_1;
    pid_filho_1 = fork();

    if (pid_filho_1)
    {
        printf("Filho 1 nasceu: %s \n", get_time());
        fflush(stdout);

        sleep(12);

        pid_t pid_neto_1;
        pid_neto_1 = fork();

        if (pid_neto_1)
        {
            printf("Neto 1 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(12);

            printf("Neto 1 morreu: %s \n", get_time());
            fflush(stdout);

            // kill(pid_neto_1, SIGTERM);
        }
        else
        {
            sleep(18);

            printf("Filho 1 morreu: %s \n", get_time());
            fflush(stdout);

            // kill(pid_filho_1, SIGTERM);
        }
    }
    else
    {
        sleep(2);

        pid_t pid_filho_2;
        pid_filho_2 = fork();

        if (pid_filho_2)
        {
            printf("Filho 2 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(14);
            pid_t pid_neto_2;
            pid_neto_2 = fork();

            if (pid_neto_2)
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