// 不加 互斥锁 输出的结果不确定

/**
 ***************** POSIX线程提供的同步机制 *****************
    互斥锁（Mutexes）：互斥锁用于保护临界区，以确保在同一时间只有一个线程可以访问被保护的共享资源。
    条件变量（Condition Variables）：它们允许一个线程等待某个条件为真，然后通知其他线程，当条件满足时，它们可以继续执行。
    信号量（Semaphores）：信号量是一种用于线程同步的计数器。它可以用于控制并发访问共享资源的数量
    屏障（Barriers）：屏障用于等待一组线程达到某个点之后再继续执行。
    读写锁（Read-Write Locks）：读写锁允许多个线程同时读取共享资源，但只允许一个线程写入共享资源。
    自旋锁：可以使用pthread_spin_init来初始化自旋锁
 */



#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;;

int A = 0;

void* pthread_fun(void* arg){
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&m);
        A++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(){

    pthread_t tid, tid2;
    pthread_create(&tid,NULL,pthread_fun,NULL);
    pthread_create(&tid2,NULL,pthread_fun,NULL);

    pthread_join(tid,NULL);
    pthread_join(tid2,NULL);

    printf("res: %d \n", A);

    pthread_mutex_destroy(&m);
    return 0;
}