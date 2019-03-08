#include <pthread.h>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
class Job {
public:
    Job(void*(*func)(void*), void* args) : func_(func), args_(args) {
        pthread_mutex_init(&mu_, NULL);
    }

    ~Job() {
        pthread_mutex_destroy(&mu_);
    }

    void Run() {
        pthread_mutex_lock(&mu_);
        printf("inside run");
        (*func_)(args_);
        pthread_mutex_unlock(&mu_);
    }
private:
    void*(*func_)(void*);
    void* args_;
    pthread_mutex_t mu_;
};


class ThreadPool{
public:
    ThreadPool(const int num) : threads_(num), stop_(false) {
        pthread_mutex_init(&q_mu_, NULL);
        pthread_cond_init(&q_cond_, NULL);
        for (int i = 0; i < num; ++i) {
            pthread_create(&threads_[i], NULL, &ThreadPool::Entry, this);
        }
    }

    ~ThreadPool() {
        if (!jobs_.empty()) {
            jobs_.pop();
        }
        for (int i = 0; i < threads_.size(); ++i) {
            pthread_join(threads_[i], NULL);
        }
        pthread_cond_destroy(&q_cond_);
        pthread_mutex_destroy(&q_mu_);
    }

    bool Schedule(void*(*func)(void*), void* args) {
        pthread_mutex_lock(&q_mu_);
        jobs_.push(new Job(func, args));
        printf("scheduled jobs %d\n", (int)jobs_.size());
        pthread_mutex_unlock(&q_mu_);
        pthread_cond_signal(&q_cond_);
        return true;
    }

    void* Execute() {
        while (1) {
            pthread_mutex_lock(&q_mu_);
            printf("wait job\n");
            while (!stop_ && jobs_.empty()) {
                pthread_cond_wait(&q_cond_, &q_mu_);
            }
            Job* job = jobs_.front();
            jobs_.pop(); // Not working here
            job->Run();
            delete(job);
            printf("remain job %d\n", (int)jobs_.size());
            pthread_mutex_unlock(&q_mu_);
        }
        pthread_exit(NULL);
        return NULL;
    }

    static void* Entry(void* self) {
        return static_cast<ThreadPool*>(self)->Execute();
    }

    // void Stop() {
    //     stop_ = true;
    // }

private:
    int num = 0;
    bool stop_;
    vector<pthread_t> threads_;
    queue<Job*> jobs_;
    pthread_mutex_t q_mu_;
    pthread_cond_t q_cond_;
    
};


