#include <stdio.h>
#include <time.h>
#include "logger.h"

void log_event(const char event[])
{
    FILE *fp;
    time_t current_time;
    struct tm *time_info;

    fp = fopen("door_log.txt", "a");

    if (fp == NULL)
    {
        printf("Error: Unable to open log file.\n");
        return;
    }

    current_time = time(NULL);
    time_info = localtime(&current_time);

    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            time_info->tm_year + 1900,
            time_info->tm_mon + 1,
            time_info->tm_mday,
            time_info->tm_hour,
            time_info->tm_min,
            time_info->tm_sec,
            event);

    fclose(fp);
}

void view_logs(void)
{
    FILE *fp;
    char line[200];

    fp = fopen("door_log.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo logs found.\n");
        return;
    }

    printf("\n==============================\n");
    printf("         EVENT LOGS\n");
    printf("==============================\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);

    printf("==============================\n");
}