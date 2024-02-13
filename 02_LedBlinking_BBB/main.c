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

int main(void)
{
    printf("Start to blink 5 times...\n");

    for (unsigned int i = 0; i < 5; ++i)
    {
        writeLED(HIGH);
        sleep(1);
        writeLED(LOW);
        sleep(1);
    }
    
    printf("It ends\n");
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// 
// int main()
// {
//     FILE *iodir,*ioval;
// 
//     // io = fopen("/sys/class/gpio/export", "w");
//     // fseek(io,0,SEEK_SET);
//     // fprintf(io,"%d",39);
//     // fflush(io);
// 
//     iodir = fopen("/sys/class/gpio/gpio60/direction", "w");
//     fseek(iodir,0,SEEK_SET);
//     fprintf(iodir,"out");
//     fflush(iodir);
// 
//     ioval = fopen("/sys/class/gpio/gpio60/value", "w");
//     fseek(ioval,0,SEEK_SET);
// 
//     while(1)
//     {
//         fprintf(ioval,"%d",1);
//         fflush(ioval);
//         sleep(1);
//         fprintf(ioval,"%d",0);
//         fflush(ioval);
//         sleep(1);
//     }
// 
//     // fclose(io);
//     fclose(iodir);
//     fclose(ioval);
//     return 0;
// }
