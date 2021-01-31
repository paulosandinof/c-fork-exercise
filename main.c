#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Função para obter a hora
char *get_time()
{
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);

    char *formatted_time = malloc(sizeof(char) * 9);

    sprintf(formatted_time, "%.2i:%.2i:%.2i", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return formatted_time;
}

int main()
{
    // Criação pai
    time_t father_birth_time = time(NULL);
    char *father_formatted_birth_time = get_time();

    printf("Processo Pai nasceu em %s.\n", father_formatted_birth_time);
    fflush(stdout);

    sleep(14);

    // Criação filho_1
    pid_t pid_son_1;
    pid_son_1 = fork();

    if (pid_son_1 < 0) // Checagem se filho_1 foi criado corretamente
    {
        printf("Erro");
    }
    else if (pid_son_1 == 0) // Executa de filho_1
    {
        time_t son_birth_time_1 = time(NULL);
        char *son_formatted_birth_time_1 = get_time();

        printf("Processo Filho 1 nasceu em %s.\n", son_formatted_birth_time_1);
        fflush(stdout);

        sleep(12);

        // Criação neto_1
        pid_t pid_grandson_1;
        pid_grandson_1 = fork();

        if (pid_grandson_1 < 0) // Checagem se neto_1 foi criado corretamente
        {
            printf("Erro");
        }
        else if (pid_grandson_1 == 0) // Executa de neto_1
        {
            time_t grandson_birth_time_1 = time(NULL);
            char *grandson_formatted_birth_time_1 = get_time();

            printf("Processo Neto 1 nasceu em %s.\n", grandson_formatted_birth_time_1);
            fflush(stdout);

            sleep(12);

            time_t grandson_death_time_1 = time(NULL);

            printf("Processo Neto 1 nasceu em %s e morreu em %s aos %.0f anos.\n", grandson_formatted_birth_time_1, get_time(), difftime(grandson_death_time_1, grandson_birth_time_1));
            fflush(stdout);
        }
        else // Volta para filho_1
        {
            sleep(18);

            time_t son_death_time_1 = time(NULL);

            printf("Processo Filho 1 nasceu em %s e morreu em %s aos %.0f anos.\n", son_formatted_birth_time_1, get_time(), difftime(son_death_time_1, son_birth_time_1));
            fflush(stdout);
        }
    }
    else // Volta para pai
    {
        sleep(2);

        // Criação filho_2
        pid_t pid_son_2;
        pid_son_2 = fork();

        if (pid_son_2 < 0) // Checagem se filho_2 foi criado corretamente
        {
            printf("Erro");
        }
        else if (pid_son_2 == 0) // Executa filho_2
        {
            time_t son_birth_time_2 = time(NULL);
            char *son_formatted_birth_time_2 = get_time();

            printf("Processo Filho 2 nasceu em %s.\n", son_formatted_birth_time_2);
            fflush(stdout);

            sleep(14);

            // Criação neto_2
            pid_t pid_grandson_2;
            pid_grandson_2 = fork();

            if (pid_grandson_2 < 0) // Checagem se neto_2 foi criado corretamente
            {
                printf("Erro");
            }
            else if (pid_grandson_2 == 0) // Executa neto_2
            {
                time_t grandson_birth_time_2 = time(NULL);
                char *grandson_formatted_birth_time_2 = get_time();

                printf("Processo Neto 2 nasceu em %s.\n", grandson_formatted_birth_time_2);
                fflush(stdout);

                sleep(18);

                time_t grandson_death_time_2 = time(NULL);

                printf("Processo Neto 2 nasceu em %s e morreu em %s aos %.0f anos.\n", grandson_formatted_birth_time_2, get_time(), difftime(grandson_death_time_2, grandson_birth_time_2));
                fflush(stdout);
            }
            else // Volta para filho_2
            {
                sleep(16);

                time_t son_death_time_2 = time(NULL);

                printf("Processo Filho 2 nasceu em %s e morreu em %s aos %.0f anos.\n", son_formatted_birth_time_2, get_time(), difftime(son_death_time_2, son_birth_time_2));
                fflush(stdout);
            }
        }
        else // Volta para pai
        {
            sleep(44);

            time_t father_death_time = time(NULL);

            printf("Processo pai nasceu em %s e morreu em %s aos %.0f anos.\n", father_formatted_birth_time, get_time(), difftime(father_death_time, father_birth_time));
        }
    }

    return 0;
}