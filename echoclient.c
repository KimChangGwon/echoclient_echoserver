#include "clnt_header.h"

#define RCV_SIZE 10000

S8 filename[100];

S32 main(S32 argc, S8 * argv[])
{
    S8 hostname[50];
    S32 sock;
    pthread_t snd_thread, rcv_thread;
    void * thread_return;

    if(argc<2 || argc>3)
    {
        printf("Usage : %s <host> <port>\n", argv[0]);
        exit(1);
    }

    set_host(argv[1], hostname);
    pthread_mutex_init(&mutx, NULL);
    sock=socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(hostname);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) printError("connect() error");

    pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);

    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    pthread_mutex_destroy(&mutx);
    close(sock);
    return 0;
}

void * send_msg(void * arg)
{

    S8 sendBuf[10000];
    S32 sock=*((S32*)arg);

    while(1){
        printf("enter message\n");
        fgets(sendBuf, sizeof(sendBuf), stdin);
        sendBuf[strlen(sendBuf) - 1]= '\0';
        write(sock, sendBuf, strlen(sendBuf));

    }

    return NULL;
}

void * recv_msg(void * arg)
{
    S32 sock=*((S32*)arg);
    S8 from_server_msg[RCV_SIZE];
    S32 str_len;
    while(1){
        str_len=read(sock, from_server_msg, sizeof(from_server_msg));
        if(str_len == 0) return (void*)-1;
        pthread_mutex_lock(&mutx);
        printf("[echo msg] : ");
        from_server_msg[str_len]='\0';
        fputs(from_server_msg, stdout);
        fputs("\n", stdout);
        pthread_mutex_unlock(&mutx);
    }
    return NULL;
}

void set_host(S8 * URL, S8 * hostname)
{
    S32 a;

    for(a = 0;; a = a + 1)
    {
        if(URL[a] == ':') {hostname[a] = 0; break;}
        hostname[a] = URL[a];
    }

    if(!strcmp(hostname, "localhost")){
        memset(hostname, 0, sizeof(hostname));
        strcpy(hostname, "127.0.0.1");
    }
    else if(strcmp(hostname, "127.0.0.1"))
    {
        struct hostent * temp;
        temp = gethostbyname(hostname);
        strcpy(hostname, inet_ntoa(*(struct in_addr*)temp->h_addr_list[0]));
    }
    return;
}

