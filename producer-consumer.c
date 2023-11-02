//条件变量解决生产者消费者问题
// 有界缓冲区问题

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

char storage[10];// 仓库
int stock = 0;//库存量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//互斥锁
pthread_cond_t pcond = PTHREAD_COND_INITIALIZER;//生产者卧室
pthread_cond_t ccond = PTHREAD_COND_INITIALIZER;//消费者卧室

//显示库存  生产者:ABC <-- X    消费者:ABC --> X
void show(char* who,char* op,char prod){
    printf("%s:",who);
    for(int i = 0;i < stock;i++){
        printf("%c",storage[i]);
    }
    printf("%s%c\n",op,prod);
}

//生产者线程
void* producer(void* arg){
    char* who = (char*)arg;
    for(;;){
        //加锁
        pthread_mutex_lock(&mutex);
        //仓库是否满
        if(stock == 10){
            //睡入生产者卧室
            printf("%s:满仓\n",who);
            pthread_cond_wait(&pcond,&mutex);
        }
        //生产
        char prod = 'A' + rand() % 26;//随机字符
        show(who,"<--",prod);
        storage[stock] = prod;
        stock++;
        //唤醒消费者
        pthread_cond_signal(&ccond);
        //解锁
        pthread_mutex_unlock(&mutex);
        usleep((rand() % 100) * 1000);
    }
    return NULL;
}

//消费者线程
void* consumer(void* arg){
    char* who = (char*)arg;
    for(;;){
        //加锁
        pthread_mutex_lock(&mutex);
        //如果空,消费者睡入条件变量
        if(stock == 0){
            printf("%s:空仓\n",who);
            pthread_cond_wait(&ccond,&mutex);
        }
        //消费
        char prod = storage[--stock];
        show(who,"-->",prod);
        //唤醒生产者
        pthread_cond_signal(&pcond);
        //解锁
        pthread_mutex_unlock(&mutex);
        usleep((rand() % 100) * 1000);
    }
    return NULL;
}

int main(void){
    pthread_t tid;
    pthread_create(&tid,NULL,producer,"生产者");
    pthread_create(&tid,NULL,consumer,"消费者");
    getchar();
    return 0;
}



