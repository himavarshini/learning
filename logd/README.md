# logd
##### a simple, generic logging daemon

## Release V 0.0.1
1. Initial version tested (AF_UNIX) Logd program with a test tool for logging

## Introduction
The Logd daemon is any other similar logging daemon that logs to a file in the daemon's own format..

The Logd uses shared memory (create + truncate & mmap) to log instead of opening and writing to the file. This has the following advantages.

1. writing to the memory is faster .. its only the memcpy and not actual disk write.
2. the file syncing is possible from the remote application (thus the actual contents can be dumped into the disk anytime the application needs)

The interface is much of a binary information transfer than a serialized byte transfer. This will be changed in the future.

The Logd uses [libsysapi](https://github.com/devnaga/libsysapi) to interact with the system level calls and any other APIs.. thus you see the very less amounts of code size.

The final log file that is generated, will have its size truncated to the actual number of bytes written to the shared memory.

The Logd employs a chroot mechanism to disallow any of the processes writing log file to the core system directories.

## To compile

1. clone the [libsysapi](https://github.com/devnaga/libsysapi)
   ``` git clone https://github.com/devnaga/libsysapi.git ```
2. compile it with ```make clean && make```
3. install it by doing ```sudo cp libsysapi.so /usr/lib/ && sudo ldconfig```
4. clone the [logd](https://github.com/devnaga/logd)
   ``` git clone https://github.com/devnaga/logd.git ```
5. compile it with ```make clean && make```
