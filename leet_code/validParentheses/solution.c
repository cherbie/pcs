#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define IS_OPEN_ASCII(C) (C == 40 || C == 91 || C == 123)
#define IS_CLOSED_ASCII(C) (C == 41 || C == 93 || C == 125)
#define IS_SIBLING_ASCII(L, R) ((L == 40 && R == 41) || (L == 91 && R == 93) || (L == 123 && R == 125))

bool isValid(char *s);

typedef struct
{
    uint8_t *tokens;
    size_t allocSize;
    size_t end;
    size_t start;
} AsciiTokenStack;
AsciiTokenStack makeAsciiTokenStack(size_t size);
void push(AsciiTokenStack *stack, uint8_t asciiChar);
uint8_t top(AsciiTokenStack *stack);
void pop(AsciiTokenStack *stack);
bool isEmpty(AsciiTokenStack *stack);

char *_getline(void);

inline bool isValid(char *s)
{
    size_t numTokens = strlen(s);
    AsciiTokenStack tokens = makeAsciiTokenStack(numTokens);
    for (int i = 0; i < numTokens; i++)
    {
        uint8_t ascii = (uint8_t)s[i];
        if (IS_CLOSED_ASCII(ascii))
        {
            if (isEmpty(&tokens))
            {
                return false;
            }
            uint8_t siblingAscii = top(&tokens);
            if (!IS_OPEN_ASCII(siblingAscii) || !IS_SIBLING_ASCII(siblingAscii, ascii))
            {
                return false;
            }
            pop(&tokens);
        }
        else
        {
            push(&tokens, ascii);
        }
    }
    return isEmpty(&tokens);
}

inline AsciiTokenStack makeAsciiTokenStack(size_t size)
{
    uint8_t *tokens = calloc(size, sizeof(uint8_t));
    return (AsciiTokenStack){
        tokens,
        size,
        0,
        0};
}

inline void push(AsciiTokenStack *stack, uint8_t asciiChar)
{
    if (stack->end >= stack->allocSize)
    {
        perror("exceeded memory allocation bounds");
        return;
    }
    stack->tokens[stack->end] = asciiChar;
    stack->end++;
}

inline uint8_t top(AsciiTokenStack *stack)
{
    if (isEmpty(stack))
    {
        perror("empty AsciiTokenStack");
        exit(EXIT_FAILURE);
    }
    return stack->tokens[stack->end - 1];
}

inline bool isEmpty(AsciiTokenStack *stack)
{
    return stack->end == stack->start;
}

inline void pop(AsciiTokenStack *stack)
{
    if (stack->end > stack->start)
    {
        stack->end--;
    }
    else
    {
        perror("nothing to pop from stack");
    }
}

char *_getline(void)
{
    size_t lenmax = 100, len = lenmax;
    char *line = malloc(lenmax * sizeof(char)), *linep = line;
    int c;

    if (line == NULL)
    {
        perror("error allocating chars for line");
        return NULL;
    }

    for (;;)
    {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (c == '\n')
        {
            line++;
            break;
        }

        if (--len == 0)
        {
            len = lenmax;
            size_t numchars = line - linep;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL)
            {
                free(linep);
                return NULL;
            }
            line = linen + numchars;
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

int main(int argc, char *argv[])
{
    char *numTestCasesLine = _getline();
    int numTestCases = atoi(numTestCasesLine);
    free(numTestCasesLine);
    for (int i = 0; i < numTestCases; i++)
    {
        char *testCase = _getline();
        printf("%s - %s\n", testCase, isValid(testCase) ? "true" : "false");
        free(testCase);
    }
    return EXIT_SUCCESS;
}
