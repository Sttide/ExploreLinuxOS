#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

int g_TestValue = 1;
pthread_mutex_t g_TestLock = PTHREAD_MUTEX_INITIALIZER;

void *ProcThread1(void *args)
{
    sleep(2);
    pthread_mutex_lock(&g_TestLock);
    g_TestValue++;
    printf("Thread 1 de g_TestValue:%d.\r\n", g_TestValue);
    g_TestValue++;
    printf("Thread 1 de g_TestValue:%d.\r\n", g_TestValue);
    pthread_mutex_unlock(&g_TestLock);
    pthread_exit(NULL);
}

void *ProcThread2(void *args)
{
    sleep(2);
    pthread_mutex_lock(&g_TestLock);
    sleep(2);
    g_TestValue++;
    printf("Thread 2 de g_TestValue:%d.\r\n", g_TestValue);
    g_TestValue++;
    printf("Thread 2 de g_TestValue:%d.\r\n", g_TestValue);
    pthread_mutex_unlock(&g_TestLock);
    pthread_exit(NULL);
}


int main()
{
    pthread_t pth1, pth2;
    void *pretval;

    int iResult = 0;

    pthread_mutex_init(&g_TestLock, NULL);
    iResult = pthread_create(&pth1, NULL, ProcThread1, NULL);
    if (iResult != 0)
    {
        printf("Create Error.\r\n");
    }

    iResult = pthread_create(&pth2, NULL, ProcThread2, NULL);
    if (iResult != 0)
    {
        printf("Create Error.\r\n");
    }

    iResult = pthread_join(pth1, &pretval);
    if (iResult != 0)
    {
        printf("Wait thread exit Error.\r\n");
    }
    iResult = pthread_join(pth2, &pretval);
    if (iResult != 0)
    {
        printf("Wait thread exit Error.\r\n");
    }
    pthread_mutex_destroy(&g_TestLock);
    printf("Main thread exit.\r\n");
    return 0;
}