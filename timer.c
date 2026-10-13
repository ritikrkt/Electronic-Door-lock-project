#include <time.h>
#include "timer.h"

void delay_seconds(int seconds)
{
    time_t start_time;
    time_t current_time;

    start_time = time(NULL);

    while (1)
    {
        current_time = time(NULL);

        if (current_time - start_time >= seconds)
        {
            break;
        }
    }
}