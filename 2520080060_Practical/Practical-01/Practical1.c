#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character
    command[strcspn(command, "\n")] = '\0';

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child Process
        printf("\n----- Child Process -----\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Executing command...\n\n");

        execl("/bin/sh", "sh", "-c", command, (char *)NULL);

        // Executes only if exec fails
        perror("Execution Failed");
        exit(1);
    }

    else
    {
        // Parent Process
        printf("\n----- Parent Process -----\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("\nWaiting for child process to finish...\n");

        wait(NULL);

        printf("\nChild process completed.\n");
    }

    return 0;
}
