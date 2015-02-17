#include "main.h"

void main()
{
    char* stringin = (char*) calloc(2048, sizeof(char));
    char tempChar = ' ';
    int i = 0;
    int stringinLength = 0;
    printf("Lord Steve: Good day peasant, I am lord Stephen Lancaster of Canterbury Castle, but you may address me as Lord Steve, master of networking.\n");
    printf("Lord Steve: I'm an expert on Computer Newtorking and Routing Protocols. Please state your question.");
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
    char mysqlquery[255];
    char words[100][255] = {" "};
    int x = 0;
    int i=0;
    int y=0;
    int wordsearch = 1;
    int row = 0;
    int steve = 0;
    int letter = 0;
    int stepper = 0;
    int keywordid;
    int answervalue;
    char differencestring[255];
    int length = 0;
    int cmp = 0;
    int wordlen = 0;
    int nomore = 0;
    length = strlen(inputpointer);

    for(stepper = 0; stepper <= length; stepper++)
    {
        words[row][letter] = inputpointer[stepper];
        letter++;
        if(inputpointer[stepper] == ' ')
        {
            words[row][letter-1] = '\n';
            row++;
            letter = 0;
        }
    }
    for(stepper = 0; stepper <= row; stepper++)
    {
        if(strcmp(words[stepper], "steve\n") == 0 || strcmp(words[stepper], "Steve\n") == 0 || strcmp(words[stepper], "steve") == 0 || strcmp(words[stepper], "Steve") == 0)
        {
            steve = 1;
        }
        if(strcmp(words[stepper], "my\n") == 0)
        {
            if(strcmp(words[stepper+1], "name\n") == 0 || strcmp(words[stepper+1], "name") == 0)
            {
                printf("\nLord Steve: I don't have the patience to remember the names of people of your stature.\n");
                wordsearch = 0;
            }
        }
        if(strcmp(words[stepper], "your\n") == 0)
        {
            if(strcmp(words[stepper+1], "name\n") == 0 || strcmp(words[stepper+1], "name") == 0)
            {
                if(steve == 0)
                {
                    printf("\nLord Steve: How dare you forget my name, you lowly PEASANT.\n");
                    wordsearch = 0;
                }
                if(steve == 1)
                {
                    printf("\nLord Steve: You said my name in your own sentence you arse.\n");
                    wordsearch = 0;
                }
            }
        }
        if(strcmp(words[stepper], "difference\n") == 0 || strcmp(words[stepper], "difference") == 0)
        {
            for(x = 0; x <= row; x++)
            {

                if(strcmp(words[x], "and\n") == 0 || strcmp(words[x], "and") == 0)
                {
                    wordsearch = 2;

                }
            }
        }
        if(strcmp(words[stepper], "AD\n") == 0 || strcmp(words[stepper], "AD") == 0 || strcmp(words[stepper], "ad\n") == 0 || strcmp(words[stepper], "ad") == 0)
        {
            wordsearch = 3;
        }
    }


    //här ska vi lägga till en if-sats som kollar igenom varje ord i wordptrs för att se om de innehåller "metric" eller "ad"
    //om metric eller ad hittas så skall keywordet skickas vidare till en annan funktion än "mysqlanswer"  som hämtar AD för routingprotokollet som har skrivits in


    //denna funktion skickar en query till databasen med hjälp av funktionen mysqlanswer, TILL Answers-tabellen
    if(wordsearch == 1)
    {
        for(stepper = 0; stepper <= row; stepper++)
        {
            snprintf(mysqlquery, 255, "SELECT Keywords.ID FROM Keywords WHERE Keywords.Keyword = '%s'", words[stepper]); //används för att lägga till en variabel i mysqlquery
            keywordid = mysqlkeywordid(mysqlquery);
            answervalue = mysqlanswer(keywordid);
        }
        if (answervalue == 1)
        {
            printf("Lord Steve: I must admit that I did not quite understand your question.");
        }
    }

    if(wordsearch == 2)
    {
        for(x = 0; x <= row; x++)
        {
            if(strcmp(words[x], "and\n") == 0 || strcmp(words[x], "and") == 0)
            {

                if(strcmp(words[x-1], words[+1]) <0 )
                {
                    wordlen = strlen(words[x-1]);
                    words[x-1][wordlen-1] = '\0';
                    strcpy(differencestring, words[x-1]);
                    strcat(differencestring, words[x+1]);
                    snprintf(mysqlquery, 255, "SELECT ID FROM KeywordsD WHERE KeywordsD.KeywordD = '%s'", differencestring);
                    keywordid = mysqlkeywordid(mysqlquery);
                    answervalue = diffSQL(keywordid);
                }
                if(strcmp(words[x-1], words[+1]) >0 )
                {
                    wordlen = strlen(words[x-1]);
                    words[x-1][wordlen-1] = '\0';
                    strcpy(differencestring, words[x+1]);
                    strcat(differencestring, words[x-1]);
                    snprintf(mysqlquery, 255, "SELECT ID FROM KeywordsD WHERE KeywordsD.KeywordD = '%s'", differencestring);
                    keywordid = mysqlkeywordid(mysqlquery);
                    answervalue = diffSQL(keywordid);
                }
                if(strcmp(words[x-1], words[+1]) == 0 )
                {
                    printf("\n Lord Steve: They are both the same word, you Donkey.\n");
                }

            }
        }


    }
    if(wordsearch == 3)
    {
        for(stepper = 0; stepper <= row; stepper++)
        {
            snprintf(mysqlquery, 255, "SELECT Keywords.ID FROM Keywords WHERE Keywords.Keyword = '%s'", words[stepper]); //används för att lägga till en variabel i mysqlquery
            keywordid = mysqlkeywordid(mysqlquery);
            answervalue = ADSQL(keywordid);
        }
}


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

int diffSQL(int keywordid)
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
    snprintf(mysqlquery, 255, "SELECT Difference FROM Differences WHERE Differences.KeywordD_ID = '%d'", keywordid); //används för att lägga till en variabel i mysqlquery
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

int ADSQL(int keywordid)
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
    snprintf(mysqlquery, 255, "SELECT AD FROM ADs WHERE ADs.Keyword_ID = '%d'", keywordid); //används för att lägga till en variabel i mysqlquery
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
