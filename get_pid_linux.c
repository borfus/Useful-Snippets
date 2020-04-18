#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_pid(char *process_name)
{
    char pid_command[64] = "pidof -s ";
    strcat(pid_command, process_name);
            
    FILE *command_results = popen(pid_command, "r");

    char results_conversion[16];
    fgets(results_conversion, 16, command_results);
    int pid = atoi(results_conversion);

    pclose(command_results);

    return pid;
}

int main(int argc, char *argv[])
{
    printf("%i\n", get_pid(argv[1]));
    return 0;
} 
