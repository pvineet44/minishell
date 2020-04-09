#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    char *buff;

	errno = 0;
	buff = getcwd(buff, 0);
    printf("%s\n", buff);
}