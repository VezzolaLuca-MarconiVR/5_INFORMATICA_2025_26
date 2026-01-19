// 5) Leggi e stampa sullo schermo tutto il contenuto del file parole.txt

#include <stdio.h>

#define FILE_NAME "parole.txt"
#define BUFFER_SIZE 256

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r"); // r stands for read only
    size_t bytesRead;
    char buffer[BUFFER_SIZE];

    if (fptr == NULL)
    {
        perror("The could not be opened");
        return 1;
    }

    do
    {
        bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), fptr);
        /*
        The %.*s is a precision format specifier for strings.

        - %s normally prints the entire string until it hits a null terminator \0.
        - %.*s tells printf to print only the first N characters, where N is supplied as
            an argument before the string itself.
        */
        printf("%.*s", bytesRead, buffer);

    } while (bytesRead > 0); // loop until end of file

    printf("\n");

    fclose(fptr);

    return 0;
}