#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>

float num1, num2;
// prototypes
char *takeInput();
void parseInput();
void printHelp();
void landingPage();


int main()
{
    landingPage();
    while (1)
    {
        char *input = takeInput();
        parseInput(input);
    }
    return 0;
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
void parseInput(char *input)
{
    if (strcmp(input, "exit") == 0)
        exit(0);
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
            char *args[256];
            args[0] = "./bacadong";
        
            int i = 1;
            while ((token = strtok(NULL, " ")) != NULL && i < 255) {
                args[i++] = token;
            }
            args[i] = NULL;
        
            pid_t pid = fork();
            if (pid == 0) {
                execv("./bacadong", args);
                perror("exec failed");
                exit(1);
            } else {
                wait(NULL);
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