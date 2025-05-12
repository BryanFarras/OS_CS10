#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int main() {
    write(STDOUT_FILENO, "\033[2J\033[H", 7);
    landingPage();
    return 0;
}

