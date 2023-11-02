//
// Created by Administrator on 2023/11/1.
//

// join 函数的使用

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define PI  3.14

// 错误，不能返回函数内部的地址
//void* area(void* arg){
//    double r = *(double *)arg;
//    double res = PI * r * r;
//    return  &res;
//}

void* area(void* arg){
    double r = *(double *)arg;
    double *res = malloc(sizeof (double )); // void * 自动类型转换
    * res = PI * r * r;
    return  res;
}

int main(){
    pthread_t tid;
    double r = 10;
    pthread_create(&tid,NULL,area, &r);
    double *res;
    pthread_join(tid, &res);    // 阻塞主线程
    printf("res: %f",*res);
    free(res);
    return 0;
}