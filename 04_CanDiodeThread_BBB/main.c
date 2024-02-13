#include <stdlib.h>
#include <pthread.h>

#include "gpio.c"
#include "can.c"


int main(void)
{
    pthread_t gpio_T;
    pthread_t can_T;

    pthread_create(&gpio_T, NULL, &gpioThread, NULL);
    pthread_create(&can_T, NULL, &canThread, NULL);

    pthread_join(gpio_T, NULL);
    pthread_join(can_T, NULL);

    return 0;
}
