#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// printf("Printable char = %i\n", (c - 32));
// printf("c = %c\n", c);
// printf("input = %c\n", input[cntIndex]);

bool *count_occur_of_character(FILE *src, char input[])
{
    int c = 0;
    int cntIndex = 0;
    bool findCharacter = false;
    static bool printableCharacters[95] = {false}; // 95 = 127chars - 32chars enable o

    while ((c = fgetc(src)) != EOF)
    {
        if (c == 10) // Finding enter character
        {
            cntIndex = 0;
            findCharacter = true;
        }
        else if ((c >= 32) && (c < 127)) // Protect uderflow array if c-32 < 0
        {
            if (input == NULL)
            {
                if ((cntIndex == 0) && (!(printableCharacters[c - 32])))
                {
                    printableCharacters[c - 32] = true;
                }
                cntIndex++;
            }
            else if ((input[cntIndex] == '\0') && findCharacter && (!(printableCharacters[c - 32])))
            {
                printableCharacters[c - 32] = true;
                findCharacter = false;
            }
            else if (c == input[cntIndex])
            {
                findCharacter = true;
                cntIndex++;
            }
            else
            {
                findCharacter = false;
            }
        }
    }

    return printableCharacters;
}

bool *count_occur_of_character_from_file(char *file1, char *file2)
{
    FILE *source_file;
    bool checkFile1 = false;

    if (file2 == NULL)
    {
        source_file = fopen(file1, "r");
        checkFile1 = true;
    }
    else
        source_file = fopen(file2, "r");

    if (source_file == NULL)
    {
        printf("-- source_file == NULL --");
        return 0;
    }

    bool *printableChar = NULL;

    // printf("File1 %i\n", checkFile1);
    // printf("File1 = %s\n", file1);
    // printf("File2 = %s\n", file2);

    if (checkFile1)
        *printableChar = count_occur_of_character(source_file, NULL);
    else
        *printableChar = count_occur_of_character(source_file, file1);

    fclose(source_file);

    return printableChar;
}

int main(int argc, char **argv)
{
    bool *printableChar = NULL;

    if (argc < 2)
        *printableChar = count_occur_of_character_from_file(argv[1], NULL);
    else
        *printableChar = count_occur_of_character_from_file(argv[1], argv[2]);

    for (int index = 32; index < 127; index++)
    {
        if (printableChar[index - 32])
            printf("%c, ", index);
    }
    printf("\n");
    return 0;
}