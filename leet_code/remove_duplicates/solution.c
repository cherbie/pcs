#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STORE_SIZE 201

int removeDuplicates(int *nums, int numsSize)
{
    int k = 0, store[MAX_STORE_SIZE] = {0};
    for (int i = 0; i < numsSize; i++)
    {
        if ((store[100 + nums[i]]++) == 0)
        {
            nums[k++] = nums[i];
        }
    }
    return k;
}

struct IntArray
{
    int *array;
    size_t size;
};

struct IntArray readlineArrayNums(void)
{
    size_t numTerms = 0, termsAllocationSize = 10;
    int *terms = calloc(termsAllocationSize, sizeof(int));
    if (terms == NULL)
    {
        perror("readlineArrayNums: memory allocation error");
        exit(1);
    }

    int magnitude = 0, number = 0;
    bool digitSeen = false, isNegative = false;
    for (;;)
    {
        const char c = fgetc(stdin);
        if (isdigit((int)c))
        {
            number += magnitude == 0 ? atoi(&c) : atoi(&c) * magnitude;
            magnitude++;
            digitSeen = true;
        }
        else if (c == '-')
        {
            isNegative = true;
        }
        else
        {
            if (digitSeen)
            {
                terms[numTerms++] = isNegative ? number * -1 : number;
                magnitude = 0, number = 0;
                digitSeen = false;
                isNegative = false;
            }
            if (c == '\n' || c == EOF)
            {
                break;
            }
        }
    }

    struct IntArray array = {terms, numTerms};
    return array;
}

int readlineNumTestCases(void)
{
    int magnitude = 0, number = 0;
    for (;;)
    {
        const char c = fgetc(stdin);
        if (isdigit((int)c))
        {
            number += magnitude == 0 ? atoi(&c) : atoi(&c) * magnitude;
            magnitude++;
        }
        else
        {
            if (c == '\n')
            {
                break;
            }
        }
    }

    return number;
}

int main(int argc, char **argv)
{
    int numTestCases = readlineNumTestCases();

    for (int i = 0; i < numTestCases; i++)
    {
        struct IntArray terms = readlineArrayNums();
        int numDuplicates = removeDuplicates(terms.array, terms.size);
        printf("#: %d\n", numDuplicates);

        free(terms.array);
    }

    return EXIT_SUCCESS;
}
