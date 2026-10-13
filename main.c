#include <stdio.h>
#include "keypad.h"
#include "door_lock.h"
#include "timer.h"
#include "logger.h"

int main()
{
    char password[5];
    int choice;
    int attempts;

    load_password();

    while (1)
    {
        printf("\n==============================\n");
        printf("     ELECTRONIC DOOR LOCK\n");
        printf("==============================\n");

       if (get_door_state() == LOCKED)
        {
            printf("Door Status : LOCKED\n");
        }
        else if (get_door_state() == UNLOCKED)
        {
            printf("Door Status : UNLOCKED\n");
        }
        else if (get_door_state() == SECURITY_LOCKOUT)
        {
        printf("Door Status : SECURITY LOCKOUT\n");
        }

        printf("\n1. Unlock Door\n");
        printf("2. Lock Door\n");
        printf("3. Change Password\n");
        printf("4. View Event Logs\n");
        printf("5. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (get_door_state() == UNLOCKED)
            {
                printf("\nDoor is already unlocked.\n");
                continue;
            }

            attempts = 0;

            while (attempts < 3)
            {
                read_password(password);

                if (check_password(password))
                {
                    printf("\nACCESS GRANTED!\n");

                    unlock_door();
                    log_event("Door unlocked");

                    printf("Door will automatically lock in 10 seconds...\n");

                    delay_seconds(10);

                    lock_door();
                    log_event("Door auto-locked");

                    printf("DOOR AUTO-LOCKED!\n");

                    break;
                }
                else
                {
                    attempts++;

                    printf("\nWRONG PASSWORD!\n");

                    log_event("Wrong password");

                    if (attempts < 3)
                    {
                        printf("Attempts remaining: %d\n",
                               3 - attempts);
                    }
                }
            }

            if (attempts == 3)
            {
                printf("\n==============================\n");
                printf("       SECURITY ALERT!\n");
                printf("==============================\n");
                printf("3 WRONG ATTEMPTS!\n");
                printf("ALARM ACTIVATED!\n");

                security_lockout();

                log_event("Alarm activated");

                printf("SYSTEM LOCKED FOR 10 SECONDS...\n");

                delay_seconds(10);

                lock_door();

                printf("\nSECURITY LOCKOUT CLEARED!\n");
                printf("You can try again.\n");

                log_event("Security lockout cleared");
            }
        }

        else if (choice == 2)
        {
            if (get_door_state() == LOCKED)
            {
                printf("\nDoor is already locked.\n");
            }
            else
            {
                lock_door();

                log_event("Door manually locked");
            }
        }

       else if (choice == 3)
        {
            if (change_password())
            {
                log_event("Password changed");
            }
            else
            {
                log_event("Password change failed");
            }
        }
        else if (choice == 4)
        {
            view_logs();
        }
        else if (choice == 5)
        {
            printf("\nExiting Electronic Door Lock...\n");
            break;
        }

        else
        {
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}