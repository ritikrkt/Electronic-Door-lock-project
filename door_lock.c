#include <stdio.h>
#include <string.h>
#include "door_lock.h"
#include "keypad.h"

char correct_password[5];
int door_state = LOCKED;

int is_valid_password(char password[])
{
    int i;

    if (strlen(password) != 4)
    {
        return 0;
    }

    for (i = 0; i < 4; i++)
    {
        if (password[i] < '0' || password[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

void load_password(void)
{
    FILE *fp;

    fp = fopen("password.txt", "r");

    if (fp == NULL)
    {
        strcpy(correct_password, "1234");

        printf("Password file not found.\n");
        printf("Default password loaded.\n");

        save_password();
        return;
    }

    fscanf(fp, "%4s", correct_password);

    fclose(fp);

    printf("Password loaded successfully.\n");
}

void save_password(void)
{
    FILE *fp;

    fp = fopen("password.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Unable to save password.\n");
        return;
    }

    fprintf(fp, "%s", correct_password);

    fclose(fp);
}

int check_password(char password[])
{
    if (strcmp(password, correct_password) == 0)
    {
        return 1;
    }

    return 0;
}

int change_password(void)
{
    char current_password[5];
    char new_password[5];
    char confirm_password[5];

    printf("\nCurrent password:\n ");
    read_password(current_password);

    if (strcmp(current_password, correct_password) != 0)
    {
        printf("\nIncorrect current password!\n");
        printf("Password cannot be changed.\n");

        return 0;
    }

    printf("\nNew password:\n");
    read_password(new_password);

    if (!is_valid_password(new_password))
    {
    printf("\nInvalid password!\n");
    printf("Password must contain exactly 4 digits.\n");

    return 0;
    }

    printf("\nConfirm new password:\n");
    read_password(confirm_password);

    if (!is_valid_password(confirm_password))
    {
    printf("\nInvalid password!\n");
    printf("Password must contain exactly 4 digits.\n");

    return 0;
    }

    if (strcmp(new_password, confirm_password) == 0)
    {
        strcpy(correct_password, new_password);

        save_password();

        printf("\nPASSWORD CHANGED SUCCESSFULLY!\n");

        return 1;
    }
    else
    {
        printf("\nPasswords do not match!\n");
        printf("Password not changed.\n");
        return 0;
    }
}

void unlock_door(void)
{
    door_state = UNLOCKED;

    printf("\nDOOR STATUS: UNLOCKED\n");
}

void lock_door(void)
{
    door_state = LOCKED;

    printf("\nDOOR STATUS: LOCKED\n");
}

void security_lockout(void)
{
    door_state = SECURITY_LOCKOUT;

    printf("\nSECURITY LOCKOUT ACTIVATED!\n");
}

int get_door_state(void)
{
    return door_state;
}