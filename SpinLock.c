#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <linux/spinlock.h>

int g_TestValue = 1;
spinlock_t g_TestLock = SPIN_LOCK_UNLOCKED;


void *ProcThread1(void *argv)
{
    sleep(2);
    spin_lock(&g_TestLock);
    g_TestValue++;
    printf("Thread 1 de g_TestValue:%d.\r\n", g_TestValue);
    g_TestValue++;
    printf("Thread 1 de g_TestValue:%d.\r\n", g_TestValue);
    spin_unlock(&g_TestLock);
    pthread_exit(NULL);
}

void *ProcThread2(void *argv)
{
    sleep(2);
    spin_lock(&g_TestLock);
    g_TestValue++;
    printf("Thread 2 de g_TestValue:%d.\r\n", g_TestValue);
    g_TestValue++;
    printf("Thread 2 de g_TestValue:%d.\r\n", g_TestValue);
    spin_unlock(&g_TestLock);
    pthread_exit(NULL);
}

int main()
{
    pthread_t pth1, pth2;
    int iResult = 0;

    spin_lock_init(&g_TestLock);
    iResult = pthread_create(pth2, NULL, ProcThread1, NULL);
    if (iResult != 0)
    {
        printf("Create Error.\r\n");
    }
    
    iResult = pthread_create(pth2, NULL, ProcThread2, NULL);
    if (iResult != 0)
    {
        printf("Create Error.\r\n");
    }
}