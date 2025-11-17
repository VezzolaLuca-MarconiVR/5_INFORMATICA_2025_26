#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFFER 1024
#define NUM_STRINGS 10

int main()
{
    const char *pipe_path = "/tmp/mypipe";
    char buffer[MAX_BUFFER];
    char *strings[NUM_STRINGS];
    int fd = open(pipe_path, O_RDONLY);
    if (fd == -1)
    {
        perror("Errore di apertura della pipe!");
        return 1;
    }

    for (int i = 0; i < NUM_STRINGS; i++)
        strings[i] = NULL;

    int string_count = 0, temp_index = 0;
    char temp[MAX_BUFFER];

    while (string_count < NUM_STRINGS)
    {
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            break;

        for (int i = 0; i < bytes_read; ++i)
        {
            if (buffer[i] == '\n')
            {
                temp[temp_index] = '\0';
                strings[string_count] = strdup(temp);
                printf("Stringa %d: %s\n", string_count + 1, strings[string_count]);
                string_count++;
                temp_index = 0;
                if (string_count == NUM_STRINGS)
                    break;
            }
            else if (temp_index < MAX_BUFFER - 1)
            {
                temp[temp_index++] = buffer[i];
            }
        }
    }

    if (temp_index > 0 && string_count < NUM_STRINGS)
    {
        temp[temp_index] = '\0';
        strings[string_count] = strdup(temp);
        printf("Stringa %d: %s\n", string_count + 1, strings[string_count]);
        string_count++;
    }

    close(fd);

    for (int i = 0; i < NUM_STRINGS; i++)
    {
        if (strings[i])
            free(strings[i]);
    }

    printf("Consumatore - OUT!\n");
    return 0;
}
