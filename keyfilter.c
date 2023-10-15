#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int count_occur_of_character(FILE *src, char input[], bool printableChar[], char cityName[])
{
    int c = 0;
    int cntIndex = 0;
    int cntChars = 0;
    bool enableToFindChar = false;
    bool findChar = false;
    bool ReadFullWord = false;

    while ((c = fgetc(src)) != EOF)
    {

        if (c == 10) // Finding enter character
        {
            cntIndex = 0;
            ReadFullWord = false;
            enableToFindChar = true;
        }
        else if ((c >= 32) && (c < 127)) // Protect underflow array if c-32 < 0
        {
            if (input == NULL) // Protect for NULL == input
            {
                if ((cntIndex == 0) && (!(printableChar[c - 32])))
                {
                    printableChar[c - 32] = true;
                    cntChars++;
                }
                cntIndex++;
            }

            else if (ReadFullWord)
            {
                char auxiliaryChar = c;
                strncat(cityName, &auxiliaryChar, 1);
            }
            else if ((input[cntIndex] == '\0') && findChar)
            {
                printableChar[c - 32] = true; // saves char
                ReadFullWord = true;
                findChar = false;
                enableToFindChar = false;
                cntChars++;
                char auxiliaryChar = c;
                strncat(cityName, &auxiliaryChar, 1);
            }
            else if ((c == input[cntIndex]) && enableToFindChar)
            {
                cntIndex++;
                findChar = true;
                char auxiliaryChar = c;
                if (cntChars < 1)
                    strncat(cityName, &auxiliaryChar, 1);
            }
            else
            {
                enableToFindChar = false;
                findChar = false;
                if (cntChars < 1)
                    memset(cityName, '\0', strlen(cityName));
            }
        }
    }

    return cntChars;
}

int count_occur_of_character_from_file(char *file1, char *file2, bool printableChar[], char cityName[])
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
        return -1;
    }

    int cnt = 0;

    if (checkFile1)
        cnt = count_occur_of_character(source_file, NULL, printableChar, cityName);
    else
        cnt = count_occur_of_character(source_file, file1, printableChar, cityName);

    fclose(source_file);

    return cnt;
}

void print_characters(bool printableChar[])
{
    for (int index = 32; index < 127; index++)
    {
        if (printableChar[index - 32])
            printf("%c, ", index);
    }
}

void print_result(int cnt, char cityName[], bool printableChar[])
{
    if (cnt == 0)
        printf("Not found\n");
    else if (cnt == 1)
        printf("Found: %s\n", cityName);
    else
    {
        printf("Enable: ");
        print_characters(printableChar);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    bool printableChar[95] = {false}; // (95 = 127chars - 32) chars enable to print
    char cityName[100];

    memset(cityName, 0, sizeof(cityName));

    int cnt = 0;

    if (argc < 2)
        cnt = count_occur_of_character_from_file(argv[1], NULL, printableChar, cityName);
    else
        cnt = count_occur_of_character_from_file(argv[1], argv[2], printableChar, cityName);

    if (cnt == -1)
        return 1;

    print_result(cnt, cityName, printableChar);

    return 0;
}