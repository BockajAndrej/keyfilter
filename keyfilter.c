#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// printf("Printable char = %i\n", (c - 32));
// printf("c = %c\n", c);
// printf("input = %c\n", input[cntIndex]);

bool *count_occur_of_character(FILE *src, char input[], bool printableChar[])
{
    int c = 0;
    int cntIndex = 0;
    bool findCharacter = false;
    // static bool printableChar[95] = {false};

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
                if ((cntIndex == 0) && (!(printableChar[c - 32])))
                {
                    printableChar[c - 32] = true;
                }
                cntIndex++;
            }
            else if ((input[cntIndex] == '\0') && findCharacter && (!(printableChar[c - 32])))
            {
                printableChar[c - 32] = true;
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

    return printableChar;
}

bool *count_occur_of_character_from_file(char *file1, char *file2, bool printableChar[])
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

    if (checkFile1)
        count_occur_of_character(source_file, NULL, printableChar);
    else
        count_occur_of_character(source_file, file1, printableChar);

    fclose(source_file);

    return printableChar;
}

int main(int argc, char **argv)
{
    bool printableChar[95] = {false}; // (95 = 127chars - 32) chars enable to print

    if (argc < 2)
        count_occur_of_character_from_file(argv[1], NULL, printableChar);
    else
        count_occur_of_character_from_file(argv[1], argv[2], printableChar);

    for (int index = 32; index < 127; index++)
    {
        if (printableChar[index - 32])
            printf("%c, ", index);
    }
    printf("\n");
    return 0;
}