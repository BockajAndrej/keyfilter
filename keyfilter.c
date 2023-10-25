#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char strlwr(char a)
{
    if ((a >= 65) && (a <= 90))
        a += 32;
    return a;
}
char strupr(char a){
    if((a >= 'a') && (a <= 'z'))
        a -= 32;
    return a;
}

void add_char_to_cityname(char cityName[], char input)
{
    if (strlen(cityName) < 100)
        strncat(cityName, &input, 1);
}

int count_occur_of_character(char input[], bool printableChar[], char cityName[])
{
    int c = 0;
    int cntIndex = 0;
    int cntChars = 0;
    bool enableToFindChar = true;
    bool findChar = false;
    bool ReadFullWord = false;

    while ((c = getchar()) != EOF)
    {
        //printf("Index = %i, Cntchar = %i, getchar = %c, expected = %c\n", cntIndex, cntChars, strupr(c), strupr(input[cntIndex]));
        if (c == 10) // Finding enter character
        {
            if (findChar && (input[cntIndex] == '\0'))
                cntChars++;
            if((cntChars < 1) && (strlen(cityName) > 1))
                memset(cityName, '\0', strlen(cityName));
            cntIndex = 0;
            ReadFullWord = false;
            enableToFindChar = true;
        }
        else if ((c >= 32) && (c < 127)) // Protect underflow array if c-32 < 0 on printable char
        {
            if (input == NULL) // Protect for NULL == input
            {
                if ((cntIndex == 0) && (!(printableChar[strupr(c) - 32])))
                {
                    printableChar[strupr(c) - 32] = true;
                    cntChars++;
                }
                cntIndex++;
            }

            else if (ReadFullWord)
                add_char_to_cityname(cityName, strupr(c));
            else if ((input[cntIndex] == '\0') && findChar)
            {
                printableChar[strupr(c) - 32] = true; // saves char
                if (cntChars < 1)
                {
                    add_char_to_cityname(cityName, strupr(c));
                    ReadFullWord = true;
                }
                findChar = false;
                enableToFindChar = false;
                cntChars++;
            }
            else if ((strupr(c) == strupr(input[cntIndex])) && enableToFindChar)
            {
                
                cntIndex++;
                findChar = true;
                if (cntChars < 1)
                    add_char_to_cityname(cityName, strupr(c));
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

void print_characters(bool printableChar[])
{
    for (int index = 32; index < 127; index++)
    {
        if (printableChar[index - 32])
            printf("%c", index);
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
    int cnt = 0;

    (void)argc;

    memset(cityName, 0, sizeof(cityName));

    cnt = count_occur_of_character(argv[1], printableChar, cityName);

    print_result(cnt, cityName, printableChar);

    return 0;
}