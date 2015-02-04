#include "main.h"

struct blergh
{

};

char* question();
char* response(info);
char* process(char string[]);

void main()
{
    
    char* stringin = (char*) calloc(40000, sizeof(char));
    char* response = (char*) calloc(10000, sizeof(char));
    char tempChar = ' ';
    int x = 0;



    gets(stringin);
    process(stringin);
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
    int x = 0;
    int y = 0;
    int length = 0;
    int prev = 0;
    int start = 0;
    int end = 0;
    int stepper = 0;
    length = strlen(string);
    string[length] = ' ';
    char words[400][100];
    for(x = 0; x <= length; x++)
    {
        if(string[x] == ' ')
        {
            end = x;
            for(start = prev; start <= end; start++)
            {
                words[y][stepper] = string[start];
                printf("%c", words[y][stepper]);
                stepper++;
            }
            prev = end+1;
            words[y][stepper] = '\n';
            y++;
        }
    }
    return NULL;
}
