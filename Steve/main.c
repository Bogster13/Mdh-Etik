#include "main.h"

struct blergh
{

};

void main()
{
    char* stringin;
    char* response;
    char tempChar = ' ';
    int x = 0;

    stringin = (char*) calloc(1, sizeof(char));
    response = (char*) calloc(100, sizeof(char));

    gets(stringin);

    printf("%s", stringin);

    system("pause");

    system("exit");
}

char* question()
{

    return NULL;
}

char* response(info)
{
    if(info == NULL)
    {
        printf("DOES NOT COMPUTE");
    }
    return NULL;
}

char* process(char string[])
{
    int length = 0;
    int x = 0;
    int prev = 0;
    int y = 0;
    int stepper = 0;
    length = strlen(string);
    char words[40][100];
    int start = 0;
    int end = 0;

    for(x = 0; x < length; x++)
    {
        if(string[x] == ' ')
        {
            end = x;
            for(start = prev; start < end; start++)
            {
                words[stepper][y] = string[start];
            }
            y++;
        }
        prev = end+1;
    }

    return NULL;
}
