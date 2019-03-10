#include <cstdio>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>

using namespace std;

class Job {
public:
    Job(function<void()> func) : func_(func) {
    }

    ~Job() {
    }

    void Run() {
        func_();
    }
private:
    function<void()>func_;
};


class ThreadPool{
public:
    ThreadPool(const int num) : threads_(num), stop_(false) {
        for (int i = 0; i < num; ++i) {
            threads_[i] = thread([](ThreadPool* self){ self->Execute(); }, this);
        }
    }

    ~ThreadPool() {
        Stop();
        if (!jobs_.empty()) {
            jobs_.pop();
        }
    }

    template <class F, class... Args>
    bool Schedule(F&& func, Args&&... args) {
        {
            unique_lock<mutex> lk(q_mu_);
            auto f = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
            unique_ptr<Job> job = make_unique<Job>([f](){ f(); });
            jobs_.push(std::move(job));
            printf("scheduled jobs %d\n", (int)jobs_.size());
        }
        q_cv_.notify_one();
        return true;
    }

    void Execute() {
        while (1) {
            unique_ptr<Job> job = nullptr;
            {
                unique_lock<mutex> lk(q_mu_);
                printf("wait job\n");
                while (!stop_ && jobs_.empty()) {
                    q_cv_.wait(lk);
                }
                if (stop_) {
                    break;
                }
                job = std::move(jobs_.front());
                jobs_.pop();
                printf("remain job %d\n", (int)jobs_.size());
            }
            job->Run();
        }
        return;
    }

    int JobSize() {
        int size = 0;
        {
            lock_guard<mutex> lk(q_mu_);
            size = jobs_.size();
        }
        return size;
    }

    void Stop() {
        if (stop_) {
            return;
        }
        stop_ = true;
        q_cv_.notify_all();
        for (int i = 0; i < threads_.size(); ++i) {
            threads_[i].join();
        }
    }

private:
    bool stop_;
    vector<thread> threads_;
    queue<unique_ptr<Job>> jobs_;
    mutex q_mu_;
    condition_variable q_cv_;
};


