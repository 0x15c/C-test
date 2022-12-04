#include <stdio.h>
#include <time.h>
#include <string.h>
extern int eventCount;
time_t time_ptr;
struct tm *local_tm_ptr;
typedef enum
{
    false,
    true
} stateFlag;
typedef enum
{
    info,
    warn,
    err,
    fatal
} eventLogHier;
FILE *eventLog;
void logPrinter(stateFlag ifEnabled_echo, const char *input, eventLogHier logHier);
void event_handler(stateFlag callin, int eventCode);
void log_init(const char *dirName, const char *logName);

void log_init(const char *dirName, const char *logName)
{

    
}

void event_handler(stateFlag ifEnabled_echo, int eventCode)
{
    switch (eventCode)
    {
    default:
        break;
    case 0:
        logPrinter(ifEnabled_echo, "Wrong arguments, program terminating.\n", fatal);
        break;
    }
}
void logPrinter(stateFlag ifEnabled_echo, const char *input, eventLogHier logHier)
{
    int eventCount;
    char eventCodeStr[10] = "";
    eventLog = fopen("eventlog.txt", "a");
    switch (logHier)
    {
    case 0:
        strcpy(eventCodeStr, "INFO");
        break;
    case 1:
        strcpy(eventCodeStr, "WARN");
        break;
    case 2:
        strcpy(eventCodeStr, "ERROR");
        break;
    case 3:
        strcpy(eventCodeStr, "FATAL");
        // fprintf(eventLog, "******FATAL******\n");
        break;
    }
    if (ifEnabled_echo == true)
    {
        puts(input);
    }
    time(&time_ptr);
    local_tm_ptr = localtime(&time_ptr);
    fprintf(eventLog, "[%s] ", eventCodeStr);
    fprintf(eventLog, "%d/%d/%d %d:%d:%d ", 1900 + local_tm_ptr->tm_year, local_tm_ptr->tm_mon + 1, local_tm_ptr->tm_mday, local_tm_ptr->tm_hour, local_tm_ptr->tm_min, local_tm_ptr->tm_sec);
    fprintf(eventLog, "[%s%d] %s", "Event Count = ", eventCount, input);
    fclose(eventLog);
}
