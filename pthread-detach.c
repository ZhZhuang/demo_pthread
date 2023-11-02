// 分离线程
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* pthread_fun(void* arg){
    for(int i=0;i<100;i++){
        //putchar('-');
        printf("子线程：%d\n",i);
        usleep(100000);
    }
    return NULL;
}


int main(){
    // 关闭缓冲区，否者不输出
    //setbuf(stdout,NULL);

    pthread_t tid;
    int error = pthread_create(&tid,NULL,pthread_fun,NULL);
    if(error != 0){
        fprintf(stderr,"pthread_create:%s\n", strerror(error));
        return -1;
    }
    //pthread_join(tid,NULL); // 阻塞主线程

    //pthread_detach(tid); //分离线程
    //将线程设置成分离线程,内核负责回收线程资源
    //pthread_detach(tid);
    for(int i=0;i<100;i++){
        //putchar('+');
        printf("主线程：%d\n",i);
        usleep(10000);
    }

    pthread_join(tid,NULL); // 阻塞主线程
    return 0;
}