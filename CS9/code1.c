#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>
#include <wordexp.h>
#include <signal.h>

float num1, num2;

char *takeInput();
void parseInput();
void printHelp();
void landingPage();
void handle_sigint(int sig);
void handle_sigtstp(int sig);
void setup_signal_handlers();

int main()
{
    setup_signal_handlers();
    landingPage();
    while (1)
    {
        char *input = takeInput();
        parseInput(input);
    }
    return 0;
}

void handle_sigint(int sig) {
    printf("\nbro masih menggunakan CTRL+C, ketik 'exit' buat keluar: Yo\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigtstp(int sig) {
    printf("\nShell tidak bisa di-suspend pakai Ctrl+Z! Gurt\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signal_handlers() {
    signal(SIGINT, handle_sigint); 
    signal(SIGTSTP, handle_sigtstp); 
}

void landingPage()
{
    puts(
        " _____ _____  ___  ______________ _   _ _         _____ \n"
        "|  _  /  ___| |  \\/  |  _  |  _  \\ | | | |       |  _  |\n"
        "| | | \\ `--.  | .  . | | | | | | | | | | |       | |_| |\n"
        "| | | |`--. \\ | |\\/| | | | | | | | | | | |       \\____ |\n"
        "\\ \\_/ /\\__/ / | |  | \\ \\_/ / |/ /| |_| | |____  .___/ /\n"
        " \\___/\\____/  \\_|  |_/\\___/|___/  \\___/\\_____/  \\____/ \n"


        "\n"
        "Copyright @ Netlab DTE\n"
        "Type \"help\" to see the list of commands\n"
        "Type \"exit\" to quit the shell\n");
    return;
}

void executeWithPipe(char *cmd1[], char *cmd2[]) {
    int fd[2];
    pipe(fd);
    pid_t pid1 = fork();

    if (pid1 == 0) {
        // Proses pertama (left side)
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execv(cmd1[0], cmd1);
        perror("exec1 failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Proses kedua (right side)
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execv(cmd2[0], cmd2);
        perror("exec2 failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// take input
char *takeInput()
{
    char *input;
    while (1)
    {
        input = readline("netlab>> ");
        if (strlen(input) != 0)
            return input;
    };
}

// parse input
void parseInput(char *input) {
    if (strchr(input, '|') != NULL) {
        char *left = strtok(input, "|");
        char *right = strtok(NULL, "|");

        char *cmd1[100], *cmd2[100];
        int i = 0;

        char *tok = strtok(left, " \n");
        while (tok != NULL) {
            cmd1[i++] = tok;
            tok = strtok(NULL, " \n");
        }
        cmd1[i] = NULL;

        i = 0;
        tok = strtok(right, " \n");
        while (tok != NULL) {
            cmd2[i++] = tok;
            tok = strtok(NULL, " \n");
        }
        cmd2[i] = NULL;

        // Ganti nama command jadi ./<command>
        char fullpath1[256], fullpath2[256];
        snprintf(fullpath1, sizeof(fullpath1), "./%s", cmd1[0]);
        snprintf(fullpath2, sizeof(fullpath2), "./%s", cmd2[0]);
        cmd1[0] = fullpath1;
        cmd2[0] = fullpath2;

        executeWithPipe(cmd1, cmd2);
        return;
    }
    else if (strlen(input) != 0)
    {
        add_history(input);
        char *token = strtok(input, " ");
        if (token == NULL)
        {
            return;
        }

        else if (strcmp(token, "print") == 0)
        {
            char *args[100];
            args[0] = "./print";
            int i = 1;

            while ((token = strtok(NULL, " ")) != NULL && i < 99) {
                args[i++] = token;
            }
            args[i] = NULL;
            pid_t pid = fork();
            if(pid == 0){
                execv("./print", args);
                perror("exec failed");
                exit(1);
            }
            else{
                wait(NULL);
            }
        }

        else if (strcmp(token, "buatdong") == 0)
        {
            char *args[256];
            args[0] = "./buatdong";

            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./buatdong", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }

        else if (strcmp(token, "bacadong") == 0)
        {
            char fullCommand[512] = "bacadong";
        
            char *next;
            while ((next = strtok(NULL, "")) != NULL) {
                strcat(fullCommand, " ");
                strcat(fullCommand, next);
                break; 
            }
        
            wordexp_t p;
            wordexp(fullCommand, &p, 0);
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bacadong", p.we_wordv);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
                wordfree(&p);
            }
        }
        
        else if (strcmp(token, "rahasiabanget") == 0)
        {
            char *args[256];
            args[0] = "./rahasiabanget";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./rahasiabanget", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }

        else if (strcmp(token, "bacapikiran") == 0)
        {
            char *args[256];
            args[0] = "./bacapikiran";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bacapikiran", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }        

        else if (strcmp(token, "itungwoi") == 0)
        {
            char *args[256];
            args[0] = "./itungwoi";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./itungwoi", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }        

        else if (strcmp(token, "bungkus") == 0)
        {
            char *args[256];
            args[0] = "./bungkus";
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bungkus", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }

        else if (strcmp(token, "buatfolder") == 0)
        {
            char *args[3];
            args[0] = "./buatfolder";
        
            token = strtok(NULL, " ");
            if (token == NULL) {
                fprintf(stderr, "Usage: buatfolder <folder_name>\n");
                return;
            }
        
            args[1] = token;
            args[2] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./buatfolder", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }
        
        else if (strcmp(token, "lihat") == 0)
        {
            char *args[256];
            args[0] = "./lihat";
            int i = 1;
        
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./lihat", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }     
        
        else if (strcmp(token, "dimana") == 0)
        {
            char *args[256];
            args[0] = "./dimana";
            int i = 1;
        
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./dimana", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }    

        else if (strcmp(token, "hapusdong") == 0)
        {
            char *args[256];
            args[0] = "./hapusdong";
            int i = 1;
        
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./hapusdong", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }
        // Contoh menambahkan case untuk fungsi shell baru
        else if (strcmp(token, "help") == 0)
        {
            // fork dan exec printHelp dari file printHelp.c
            pid_t pid = fork();
            if (pid == 0)
            {
                execl("./printHelp", "printHelp", NULL);
                perror("exec failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }

        else if (strcmp(token, "bukain") == 0)
        {
            char *args[4];
            args[0] = "./bukain";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 3) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bukain", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }
        
        else if (strcmp(token, "bersihindong") == 0)
        {
            char *args[4];
            args[0] = "./bersihindong";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 3) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bersihindong", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
            }
        }
        else{
            system(input);
        }
    }
}