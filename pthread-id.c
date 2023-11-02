//线程的ID
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/syscall.h>//syscall
//线程过程函数
void* pthread_fun(void* arg){

    printf("子线程:   进程的PID:%d\n",getpid());
    printf("子线程:POSIX线程TID:%lu\n",pthread_self());
    printf("子线程: 系统内核TID:%ld\n",syscall(SYS_gettid));

    return NULL;
}

int main(void){
    printf("主线程:   进程的PID:%d\n",getpid());
    printf("主线程:POSIX线程TID:%lu\n",pthread_self());
    printf("主线程: 系统内核TID:%ld\n",syscall(SYS_gettid));
    pthread_t tid;
    pthread_create(&tid,NULL,pthread_fun,NULL);
    pthread_join(tid,NULL);
    return 0;
}
