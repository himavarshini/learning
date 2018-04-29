import os


def compile_code():
    os.system("gcc ./ssl_shagen.c -o ssl_shagen -lssl -lcrypto");

compile_code
