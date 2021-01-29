#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Função para obter a hora
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
    // Criação pai
    time_t father_time;
    time(&father_time);

    printf("Processo pai nasceu: %s", get_time());
    fflush(stdout);

    sleep(14);

    // Criação filho_1
    pid_t pid_filho_1;
    pid_filho_1 = fork();

    // Checagem se filho_1 foi criado corretamente
    if (pid_filho_1 < 0)
    {
        printf("Erro");
    }
    // Executa de filho_1
    else if (pid_filho_1 == 0)
    {
        printf("Filho 1 nasceu: %s \n", get_time());
        fflush(stdout);

        sleep(12);
        // Criação neto_1
        pid_t pid_neto_1;
        pid_neto_1 = fork();

        // Checagem se neto_1 foi criado corretamente
        if (pid_neto_1 < 0)
        {
            printf("Erro");
        }
        // Executa de neto_1
        else if (pid_neto_1 == 0)
        {
            time_t grandson_time_1;
            time(&grandson_time_1);

            printf("Neto 1 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(12);

            time_t grandson_death_time_1;
            time(&grandson_death_time_1);

            printf("Neto 1 morreu: %s depois de %.0f anos.\n", get_time(), difftime(grandson_death_time_1, grandson_time_1));
            fflush(stdout);

            exit(8);
        }
        else
        // Volta para filho_1
        {
            sleep(18);

            printf("Filho 1 morreu: %s \n", get_time());
            fflush(stdout);

            // kill(pid_filho_1, SIGTERM);
        }
    }
    // Volta para pai
    else
    {
        sleep(2);

        // Criação filho_2
        pid_t pid_filho_2;
        pid_filho_2 = fork();

        // Checagem se filho_2 foi criado corretamente
        if (pid_filho_2 < 0)
        {
            printf("Erro");
        }
        // Executa filho_2
        else if (pid_filho_2 == 0)
        {
            printf("Filho 2 nasceu: %s \n", get_time());
            fflush(stdout);

            sleep(14);

            // Criação neto_2
            pid_t pid_neto_2;
            pid_neto_2 = fork();

            // Checagem se neto_2 foi criado corretamente
            if (pid_neto_2 < 0)
            {
                printf("Erro");
            }
            // Executa neto_2
            else if (pid_neto_2 == 0)
            {
                printf("Neto 2 nasceu: %s \n", get_time());
                fflush(stdout);

                sleep(18);

                printf("Neto 2 morreu: %s \n", get_time());
                fflush(stdout);

                // kill(pid_neto_2, SIGTERM);
            }
            else
            // Volta para filho_2
            {
                sleep(16);

                printf("Filho 2 morreu: %s \n", get_time());
                fflush(stdout);

                // kill(pid_filho_2, SIGTERM);
            }
        }
        else
        // Volta para pai
        {
            sleep(44);
            time_t father_death_time;
            time(&father_death_time);

            printf("Processo pai morreu: %f", difftime(father_death_time, father_time));
        }
    }

    return 0;
}