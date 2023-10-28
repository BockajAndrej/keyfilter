#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Make from lowercase letters uppercase 
char strupr(char a);
//Adding a character to char array (cityname)
void add_char_to_cityname(char cityName[], char input);
//Searching for characters and city
int count_occur_of_character(char input[], bool printableChar[], char cityName[]);
//Prints only enable characters for future searching
void print_characters(bool printableChar[]);
//Prints according to assignment  
void print_result(int cnt, char cityName[], bool printableChar[]);

char strupr(char a)
{
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

    //It reads only one char 
    while ((c = getchar()) != EOF)
    {
        //printf("Index = %i, Cntchar = %i, getchar = %c, expected = %c\n", cntIndex, cntChars, strupr(c), strupr(input[cntIndex]));
        if (c == 10) // Searching for enter character
        {
            if (findChar && (input[cntIndex] == '\0'))
                cntChars++;
            if((cntChars < 1) && (strlen(cityName) > 1))
                memset(cityName, '\0', strlen(cityName));
            cntIndex = 0;
            ReadFullWord = false;
            enableToFindChar = true;
        }
        else if ((c >= 32) && (c < 127)) // Protect underflow array if c-32 < 0 on printable char and it supports only ascii characters
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
    bool printableChar[95] = {false};   // (95 = 127chars - 32) chars enable to print
    char cityName[100];                 // It will contain name of found city
    int cnt = 0;                        // Counter of foundable cities 

    (void)argc;
    if(argv[1] != NULL){
        if(strlen(argv[1]) == 0)
            argv[1] = NULL;
    }

    memset(cityName, 0, sizeof(cityName));  //Clear whole array 

    cnt = count_occur_of_character(argv[1], printableChar, cityName);

    print_result(cnt, cityName, printableChar);

    return 0;
}