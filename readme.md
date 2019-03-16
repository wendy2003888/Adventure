Adventure
---------
My adventure time of ipfs, zeromq(zmq), tensorflow custom Op, thread pool, libpng.

Provide simple examples.

### ipfs
->ipfs

An example of usng ipfs apis

### ZeroMQ (zmq)
->zmq_test

A client examples in multithread. Using zmq::pollitem to check TIMEOUT, receiving multipart message.

A single process server example sending multipart message.

### Threadpool:
->threadpool

A simple threadpool using pthread or str::thread

### Tensorflow custom Op
->custom_op

An example of tensorflow custom op with GPU support. Fixed errors on the official guid.
Building command with GPU support.

run make.sh to build.

### libpng
->img_io

An example of using libpng read files from memory/buffer.

Including vector<char>, string, istream

main.cpp includes example of vector<char>, string
stream.cpp includes example of istream
```
g++ -std=c++1y -o main main.cpp -lpng -lz  && ./main
g++ -std=c++1y -o stream stream.cpp -lpng -lz  && ./stream
```
