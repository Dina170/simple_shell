#include "main.h"

int main(void)
{
    size_t n = 0;
    char *lineptr = NULL, *lineptr_copy = NULL, *token;
    ssize_t reads;
    char *delimter = " \n";
    char **argv;
    int counter, i, token_num;

    while (1)
    {
        token_num = 0;
        printf("($) ");
        reads = getline(&lineptr, &n, stdin);

        if (reads == -1)
        {
            printf("Exit...\n");
            return (-1);
        }

        lineptr_copy = malloc(sizeof(char) * reads);

        if (!lineptr_copy)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }

        strcpy(lineptr_copy, lineptr);

        token = strtok(lineptr, delimter);

        while (token != NULL)
        {
            token_num++;
            token = strtok(NULL, delimter);
        }
       
        argv = malloc(sizeof(char *) * token_num);

        token = strtok(lineptr_copy, delimter);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delimter);
        }
        argv[i] = NULL;
        

        
        
        exc(argv);
    }
        free(argv);
        free(lineptr);
        free(lineptr_copy);    

    return (0);
}
