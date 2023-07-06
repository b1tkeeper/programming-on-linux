all: ipc_pipe ipc_fifo ipc_shm ipc_sem ipc_msg ipc_socket crt_pthread

LIBS := -lglib-2.0 -lpthread -lm
LIB_DIR := -L/usr/lib/x86_64-linux-gnu/glib-2.0
INCLUDE_DIR := -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

CC := gcc
CFLAGS := -Wall $(INCLUDE_DIR)
LDFLAGS := --static

ipc_pipe: ipc_pipe.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_pipe ipc_pipe.c $(LIBS)

ipc_fifo: ipc_fifo.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_fifo ipc_fifo.c $(LIBS)

ipc_shm: ipc_shm.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_shm ipc_shm.c $(LIBS)

ipc_sem: ipc_sem.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_sem ipc_sem.c $(LIBS)

ipc_msg: ipc_msg.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_msg ipc_msg.c $(LIBS)

ipc_socket: ipc_socket.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o ipc_socket ipc_socket.c $(LIBS)

crt_pthread: crt_pthread.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB_DIR) -o crt_pthread crt_pthread.c $(LIBS)

clean:
	rm ipc_pipe ipc_fifo ipc_shm ipc_sem ipc_msg ipc_socket crt_pthread