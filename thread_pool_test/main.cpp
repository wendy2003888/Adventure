#include "threadpool.h"
#include <pthread.h>

static void* func(void* params) {
    printf("here\n");
    return NULL;
}

int main() {
    int num_threads = 3;
    ThreadPool pool(num_threads);
    for (int i = 0; i < 5; ++i) {
        pool.Schedule(&func, NULL);
    }
    while (1) {
        if (pool.JobSize() == 0) {
            pool.Stop();
            break;
        }
    }
    return 0;
}