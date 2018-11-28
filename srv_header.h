#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUFSIZE 10000
#define MAX_CLNT 10

typedef int64_t S64;
typedef int32_t S32;
typedef int16_t S16;
typedef int8_t S8;

typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

typedef struct argstruct{
    U32 clnt_sock;
    U8 flag;
} argstrt;

void * handle_clnt(void * arg);
void send_msg(U8 * msg, U32 len, U32 clnt_sock, U8 flag);
pthread_mutex_t mutx;


void printError(U8 * errstr){
    fprintf(stderr, "%s\n", errstr);
    exit(1);
}
