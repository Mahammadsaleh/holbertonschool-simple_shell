#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t p_process;

    my_pid = getpid();
    p_process = getppid();
    printf("%u\n", my_pid);
    printf("%i\n", p_process);
    return (0);
}
