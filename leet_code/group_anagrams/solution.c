#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 10

int main(int argc, char** argv)
{
    char *str = calloc(MAX_STRING_SIZE, sizeof(char));
    if (gets(str) == NULL)
    {
        perror("gets() failed");
        return EXIT_FAILURE;
    }

    puts(str);
    return EXIT_SUCCESS;
}
