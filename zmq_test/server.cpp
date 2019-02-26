#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUSH);
    try {
        socket.bind ("tcp://127.0.0.1:5555");
    } catch (zmq::error_t e) {
        std::cout<<e.what()<<std::endl;
    }
    


    const int num = 3;
    const int parts = 3;
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j <  parts; ++j) {
            int tmp = i;
             zmq::message_t msg (sizeof(tmp));
    //    sleep(1);
            memcpy (msg.data(), &tmp, sizeof(tmp));
            socket.send (msg, j == parts - 1 ? 0 : ZMQ_SNDMORE);
        }
    }       
    return 0;
}