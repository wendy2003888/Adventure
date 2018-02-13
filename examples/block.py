#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from . import api, dir_path
import io, os, typing

def send2block(f_path):
    with io.open(f_path, 'rb') as f:
        res = api.block_put(f)
        return res

def get_from_block(hash_url):
    try:
        res = api.block_get(hash_url)
        return res.decode('utf-8')  #convert binarystr to str
    except Exception as e:
        return {'err' : e}


if __name__ == "__main__":
    file_name = 'record.txt'
    f_path = os.path.join(dir_path, file_name)

    res_send = send2block(f_path)
    print ( 'key : %s, size : %d' % (res_send['Key'], res_send['Size']) )

    res_get = get_from_block(res_send['Key'])
    if type(res_get) != typing.Dict:
        print ( 'content : %s' % res_get)
    else:
        print ('error %s' % (res_get['err']))

