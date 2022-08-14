#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    char *line;
    int fd1 = open("test", O_RDONLY);
    int fd2 = open("test3", O_RDONLY);
    /*while(1)
    {
        line = get_next_line(fd1);
        printf("%s",line);
        free(line);
        line = get_next_line(fd2);
        printf("%s",line);
        free(line);
        if (line == NULL)
            break;
    }*/
    line = get_next_line(fd1);
    printf("%s",line);
    free(line);
    line = get_next_line(fd2);
    printf("%s",line);
    free(line);
    //system("leaks a.out");
}