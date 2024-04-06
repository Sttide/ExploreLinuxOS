#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

void *OutputTest(void *args)
{
    printf("Thread Create.\r\n");
    sleep(3);
    pthread_exit(NULL);
}


int main()
{
    pthread_t pthreadTest;
    void *pretval;
    int iResult = 0;

    iResult = pthread_create(&pthreadTest, NULL, OutputTest, NULL);
    if (iResult != 0)
    {
        printf("Create Error.\r\n");
    }

    iResult = pthread_join(pthreadTest, &pretval);
    if (iResult != 0)
    {
        printf("Wait thread exit Error.\r\n");
    }

    printf("Main thread exit.\r\n");
    return 0;
}