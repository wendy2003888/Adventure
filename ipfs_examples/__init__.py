import ipfsapi
import os

api = ipfsapi.connect('127.0.0.1', 5001)
dir_path = os.path.dirname(os.path.realpath(__file__))
# dir_path = os.getcwd()
