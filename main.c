#include <stdio.h>
#include "threadpool.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void * printData(void *arg)
{
    int val = *(int *)arg;
    printf("thread %ld is working number:%d\n", pthread_self(), val);
    
    /* 休眠1000ms */
    sleep(1);
}

int main()
{
    threadPool_t m_p;
    threadPoolInit(&m_p, 5, 10, 100);

    
    int *nums = (int *)malloc(sizeof(int) * 100);

    for (int idx = 0; idx < 100; idx++)
    {   
        nums[idx] = idx + 100;
        threadPoolAddTask(&m_p, printData, &nums[idx]);
    }
    sleep(3);


    /* 释放 */
    if (nums)
    {
        free(nums);
        nums = NULL;
    }
    
    /* 释放线程池 */
    threadPoolDestroy(&m_p);
    
}