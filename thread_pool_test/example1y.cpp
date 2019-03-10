#include "threadpool1y.h"
#include <memory>

using namespace std;

static void func(const int a, const double b) {
    printf("a=%d b=%f a*b = %f\n", a, b, a*b);
    return;
}

int main() {
    int num_threads = 3;
    shared_ptr<ThreadPool> pool = make_shared<ThreadPool>(num_threads);
    for (int i = 0; i < 5; ++i) {
        pool->Schedule(func, i, (double)i);
    }
    while (1) {
        if (pool->JobSize() == 0) {
            pool->Stop();
            break;
        }
    }
    return 0;
}