// 6) Copia il contenuto di un file input.txt in un nuovo file output.txt

#include <stdio.h>

#define READ_PATH "input.txt"
#define WRITE_PATH "output.txt"
#define BUFFER_SIZE 256

int main()
{
    FILE *fptrRead = fopen(READ_PATH, "r");
    FILE *fptrWrite = fopen(WRITE_PATH, "w");
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    if (fptrRead == NULL || fptrWrite == NULL)
    {
        perror("The file could not be opened");
        return 1;
    }

    do
    {
        bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), fptrRead);
        fwrite(buffer, sizeof(buffer[0]), bytesRead, fptrWrite);
    } while (bytesRead > 0);

    fclose(fptrRead);
    fclose(fptrWrite);

    return 0;
}