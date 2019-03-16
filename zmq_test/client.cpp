#include <zmq.hpp>
#include <mutex>
#include <thread>
#include <iostream>


class Test {
public:
    Test() : ctx_(1), socket_(ctx_, ZMQ_PULL) {}     

    void run() {
        {
            std::lock_guard<std::mutex> lock(mu_);
            std::thread::id this_id = std::this_thread::get_id();
            try {
            socket_.connect("tcp://127.0.0.1:5555");
            } catch (zmq::error_t e) {
                printf("%s\n", e.what());
                return;
            }
            item = zmq::pollitem_t({static_cast<void*>(socket_), 0, ZMQ_POLLIN, 0});

            const int TIMEOUT = 10000;
            zmq::poll(&item, 1, TIMEOUT);
            if (item.revents & ZMQ_POLLIN) {
                bool next = true;
                while (next) {
                    zmq::message_t msg;
                    if (!socket_.recv(&msg, 0)) {
                        return;
                    }
                    next = msg.more();
                    int i;
                    memcpy(&i, msg.data(), msg.size());
                    std::cout<<i<<" thread id "<<this_id<<std::endl;
                }
            } else {
                return;
            }
        }
    }

private:
    std::mutex mu_;
    zmq::context_t ctx_;
    zmq::socket_t socket_;
    zmq::pollitem_t item;
};


int main() {
    const int numth = 3;
    std::thread th[numth];
    for (int i =0; i < numth; i++) {
        th[i] = std::thread(&Test::run, new Test());
    }
    for (int i = 0; i < numth; ++i) {
        th[i].join();
    }
    return 0;
}