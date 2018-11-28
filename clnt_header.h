#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <ctype.h>
#include <netdb.h>

#define RCV_SIZE 1000000

typedef int64_t S64;
typedef int32_t S32;
typedef int16_t S16;
typedef int8_t S8;

typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

void * send_msg(void * arg);
void * recv_msg(void * arg);
struct sockaddr_in serv_addr;

pthread_mutex_t mutx;

void printError(U8 * errstr){
    fprintf(stderr, "%s\n", errstr);
    exit(1);
}
