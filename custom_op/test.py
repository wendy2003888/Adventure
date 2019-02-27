import tensorflow as tf
test_op = tf.load_op_library('./test_op.so')
with tf.Session('') as sess:
  # test_op.example([[1, 2], [3, 4]]).eval()
  print (sess.run(test_op.example([[1, 2], [3, 4]])))