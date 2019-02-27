TF_CFLAGS=( $(python3 -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_compile_flags()))') )
TF_LFLAGS=( $(python3 -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_link_flags()))') )
CUDA_PATH = /usr/local/cuda
nvcc -std=c++11 -c -o test_op.cu.o kernel_example.cu.cc \
  ${TF_CFLAGS[@]} -D GOOGLE_CUDA=1 -x cu -Xcompiler -fPIC  -I/usr/local/cuda -L/usr/local/cuda/lib64 --expt-relaxed-constexpr -DNDEBUG
g++ -std=c++11 -shared -o test_op.so kernel_example.cc test_op.cu.o ${TF_CFLAGS[@]} -fPIC -L/usr/local/cuda/lib64 -lcudart ${TF_LFLAGS[@]} 



