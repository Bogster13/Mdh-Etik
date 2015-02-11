#include "main.h"

char* question();
char* response(info);
char* process(char string[]);
int mysqlkeywordid();
int mysqlanswer();
void main()
{
    char* stringin = (char*) calloc(2048, sizeof(char));
    char* response = (char*) calloc(2048, sizeof(char));
    char tempChar = ' ';
    int i = 0;
    int stringinLength = 0;
    printf("Steve: Good day peasant, I am lord Stephen Lancaster of Canterbury Castle, but you may address me as Lord Steve, master of networking.\n");
    printf("Steve: I'm an expert on Computer Newtorking and Routing Protocols. Please state your question.");
    do
    {
        printf("\nYou: ");
        gets(stringin);

        //replace any special characters in stringin with space
        stringinLength = strlen(stringin);
        for (i=0; i<stringinLength; i++)
        {
            if (stringin[i] == '?' || stringin[i] == '.' || stringin[i] == '!' || stringin[i] == '"' || stringin[i] == '\''  || stringin[i] == '+' || stringin[i] == ',' || stringin[i] == '&')
                stringin[i] = ' ';
        }
        process(stringin);

    } while (1);
    system("pause");
    system("exit");
}

char* process(char *inputpointer)
{
    char keyword[255];
    char *wordptrs[255];
    char *strStripped[255];
    char mysqlquery[255];
    int i=0;
    int y=0;
    int c=0;
    int keywordid;
    int answervalue;
    *(wordptrs) = strtok(inputpointer," ");
    while( *(wordptrs+i) != NULL )
    {
        ++i;
        *(wordptrs+i) = strtok(NULL," ");

    }
    while(*(wordptrs+y) != NULL)
    {
        snprintf(mysqlquery, 255, "SELECT Keywords.ID FROM Keywords WHERE Keywords.Keyword = '%s'", wordptrs[y]); //används för att lägga till en variabel i mysqlquery
        keywordid = mysqlkeywordid(mysqlquery);
        answervalue = mysqlanswer(keywordid);
        ++y;
    }
    if (answervalue == 1)
        printf("Steve: I must admit that I did not quite understand your question.");

    return NULL;
}

int mysqlkeywordid(char *mysqlquery)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "skagnet.se";
    char *user = "etikmdh";
    char *password = "etikmdh";
    char *database = "chatbot";
    int keywordid;
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, server,
        user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    do {
        /* send SQL query */
        if (mysql_query(conn, mysqlquery)) {        //mysqlquery-variablen används som query till mysql servern
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        while ((row = mysql_fetch_row(res)) != NULL)
        {
                keywordid = atoi(row[0]);
        }
        //printf("%d", keywordid);
    } while (keywordid == NULL);
    mysql_free_result(res);
    mysql_close(conn);
    return keywordid;
}

int mysqlanswer(int keywordid)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "skagnet.se";
    char *user = "etikmdh";
    char *password = "etikmdh"; /* set me first */
    char *database = "chatbot";
//    char *answer[255];
    char randomiseanswer[10][255] = {0};
    char mysqlquery[255];
    int i = 0;
    int n, z, a;
    int answervalue;
    int answerrows=0;
    srand(time(NULL));
    snprintf(mysqlquery, 255, "SELECT Answer FROM Answers WHERE Answers.Keyword_ID = '%d'", keywordid); //används för att lägga till en variabel i mysqlquery
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    /* send SQL query */

    if (mysql_query(conn, mysqlquery))
    {        //mysqlquery-variablen används som query till mysql servern
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    /* output table name */
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        answervalue = 0;
        strcpy(randomiseanswer[i], row[0]); //kopierar stringen till enn 2d array "test!"
        i++;
    }
    if (((row = mysql_fetch_row(res)) == NULL) && i == 0)
        answervalue = 1;

    for (z = 0; z < 10; z++) {
        if (randomiseanswer[z][0] == NULL)
            answerrows++;   //räknar hur många rader av 20 som inte har ett svar
        }
    if (answervalue == 0)
    {
        answerrows = 10 - answerrows; //tar värdet 20 från föregående for-loop och subtraherar med answerrows
        n = rand()%answerrows;
        printf("Steve: ");
        for (a = 0; a < 255; a++) {
            if (randomiseanswer [n][a] != NULL)
                printf("%c", randomiseanswer[n][a]);
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    return answervalue;
}
