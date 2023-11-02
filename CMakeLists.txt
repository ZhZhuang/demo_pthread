cmake_minimum_required(VERSION 3.23)
project(demo_pthread C)

set(CMAKE_C_STANDARD 99)


# 链接库否则报错： undefined reference to `pthread_create'
#target_link_libraries(demo_pthread PRIVATE pthread)

#add_executable(demo_pthread pthread-conflict-mutex.c producer-consumer.c)
#target_link_libraries(demo_pthread PRIVATE pthread)

add_executable(demo_pthread producer-consumer.c)
target_link_libraries(demo_pthread PRIVATE pthread)
