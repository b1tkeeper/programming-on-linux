# Programming On Linux

## Brief Introduction

This project aims to help programming beginners, learn the basic concepts and usage of Linux programming.

## Code structure
Each c-file here contains a technology-specific dmeo.

### IPC (Inter-process communication)
- **ipc_fifo.c** Using named pipes to communicate between processes.
- **ipc_msg.c** Using message queue to communicate between processes.
- **ipc_pipe.c** Using pipes to communicate between processes.
- **ipc_sem.c** Using semaphore to communicate between processes.
- **ipc_shm.c** Using shared memory to communicate between processes.
- **ipc_socket.c** Using socket to communicate between processes.

### Concurrent Programming
- **crt_pthread.c** Concurrent programming using threads (pthread).

## Compile
```shell
make
```

## Clean
```shell
make clean
````