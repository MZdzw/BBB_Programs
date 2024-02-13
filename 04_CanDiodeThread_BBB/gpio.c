#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LED_PATH "/sys/class/gpio/gpio60"

typedef enum State_e
{
    LOW, HIGH
}State_e;

void writeLED(State_e state)
{
    FILE* fptr;
    char filePath[30];
    strcpy(filePath, LED_PATH);
    strcat(filePath, "/value");
    fptr = fopen(filePath, "w");
    if (fptr == NULL)
        return;
    if (state == HIGH) 
    {
       fprintf(fptr, "%d", 1);
    }
    else 
    {
       fprintf(fptr, "%d", 0);
    }
    fflush(fptr);
    fclose(fptr);
}

void* gpioThread(void* arg)
{
    printf("Initialize gpio thread...\n");

    for(;;)
    {
        writeLED(HIGH);
        sleep(1);
        writeLED(LOW);
        sleep(1);
    }
}

