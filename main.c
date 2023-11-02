#include <stdio.h>
#include <pthread.h>
#include <time.h>
//#include <windows.h>//使用Sleep的头
#include <unistd.h>

int g_number = 0;

#define MAX_COUNT 10000

// 注释 mutex 对比效果
// 加上，可以正常输出到5000，不加就会少于5000
pthread_mutex_t mut;


void *counter3(void* args) {

    int i = 1;
    while (i <= MAX_COUNT / 4) {
        pthread_mutex_lock(&mut);
        g_number++;
        pthread_mutex_unlock(&mut);
        printf("hi,i am pthread 3, my g_number is [%d]\n", g_number);
        //Sleep(1);// 单位ms
        //sleep(1);  // 单位s //unistd.h>
        usleep(1000); // 1000微秒 = 1毫秒
        i++;
    }
}

void *counter4(void* args) {
    int j = 1;
    while (j <= MAX_COUNT / 4) {
        pthread_mutex_lock(&mut);
        g_number++;
        pthread_mutex_unlock(&mut);
        printf("hi,i am pthread 4, my g_number is [%d]\n", g_number);
        //Sleep(1);     // windows中的函数
        //sleep(1); //unistd.h>
        usleep(1000); // 1000微秒 = 1毫秒 不i推荐
        j++;
    }
}

int main() {
    pthread_mutex_init(&mut, NULL);
    pthread_t t3;
    pthread_t t4;
    pthread_create(&t3, NULL, counter3, NULL);
    pthread_create(&t4, NULL, counter4, NULL);

    getchar();
    return 0;
}