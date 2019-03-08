#include "threadpool.h"
#include <pthread.h>

static void* func(void* params) {
    printf("here");
//    pthread_exit(NULL);
    // why do you want to kill the thread here
    return NULL;
}

int main() {
    int num_threads = 3;
    ThreadPool pool(num_threads);
    for (int i = 0; i < 5; ++i) {
        pool.Schedule(&func, NULL);
    }
    return 0;
}