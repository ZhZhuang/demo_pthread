//
// Created by Administrator on 2023/11/1.
//


#include <stdio.h>
#include <pthread.h>
#include <string.h> // strerror
#include <unistd.h> // sleep()

//线程过程函数
void* pthread_fun(void* arg){
    printf("thread:%lu, i am child thread, i received %s\n",pthread_self(), (char*)arg);
    return NULL;
}

int main(){
    printf("%lu thread, i am father thread\n",pthread_self());
    pthread_t  tid;
    int error = pthread_create(&tid,NULL,pthread_fun,"铁锅炖大鹅");
    if(error != 0){
        fprintf(stderr,"pthread_create:%s\n", strerror(error));
        return -1;
    }
    printf("%lu 线程:我是主线成,我创建了%lu子线程\n",pthread_self(),tid);

    // 必须有，否者主线程执行结束后，子线程无法执行
    sleep(1);
   return 0;
}