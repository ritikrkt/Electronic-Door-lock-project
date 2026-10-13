#include <stdio.h>
#include <conio.h>
#include "keypad.h"

void read_password(char password[])
{
    int index = 0;
    char ch;

    printf("Enter 4 digit password: ");

    while (1)
    {
        ch = getch();

        /* Digit input */
        if (ch >= '0' && ch <= '9')
        {
            if (index < 4)
            {
                password[index] = ch;
                index++;

                printf("*");
            }
        }

        /* Clear last digit */
        else if (ch == '*')
        {
            if (index > 0)
            {
                index--;

                printf("\b \b");
            }
        }

        /* Submit password */
        else if (ch == '#')
        {
            if (index == 4)
            {
                password[index] = '\0';
                printf("\n");
                break;
            }
            else
            {
                printf("\nPlease enter exactly 4 digits!\n");
                printf("Enter 4 digit password: ");

                index = 0;
            }
        }
    }
}