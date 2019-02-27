load("//tensorflow:tensorflow.bzl", "tf_custom_op_library")

cc_library(
    name = "kernel_example",
    hdrs = ["kernel_example.h"],
)

tf_custom_op_library(
    name = "test_op.so",
    srcs = ["kernel_example.cc"],
    gpu_srcs = ["kernel_example.cu.cc"],
    deps = [":kernel_example"],
)
