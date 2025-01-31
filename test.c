#include <unistd.h>
#include <stdio.h>
# include <fcntl.h>

int main(void)
{
    char *cmds[2];
    cmds[0] = "cat";
    cmds[1] = NULL;
    char *cmd = "/bin/cat";
    int fd = open("a", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
    execve(cmd, cmds, NULL);
    return (0);
}