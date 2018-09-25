/*********************
TCP socket通信
服务器端流程如下：
1.创建serverSocket
2.初始化 serverAddr（服务器地址）
3.将socket和serverAddr 绑定 bind
4.开始监听 listen
5.进入while循环，不断的accept接入的客户端socket，进行读写操作write和read
6.关闭serverSocket
**********************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define SRVIP "127.0.0.1"
#define SRVPORT 10005
#define MAX_NUM 80
int main()
{
	//创建套接字
	//第一个参数为套接字使用的地址格式；
	//第二第三是套接字类型TCP(SOCK_STREAM,IPPROTO_TCP),UDP(SOCK_DGRAM,IPPTOTO_UDP);
    int serverSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(serverSock < 0)
    {	//如果发生错误，函数返回值为-1
        printf("服务器 socket 创建失败\n");
        exit(-1);
    }
    printf("服务器 socket 创建成功\n");

	//初始化服务器地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port = htons((u_short)SRVPORT);
    serverAddr.sin_addr.s_addr = inet_addr(SRVIP);

    //绑定，bind() 将一个socket绑定到指定的IP和端口上，socket只接受绑定IP和端口的数据
    if(bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr))==-1)
    {
        printf("绑定（bind）失败.IP[%s], Port[%d]\n", SRVIP, serverAddr.sin_port);
        exit(-1);
    }
    printf("绑定（bind）成功.IP[%s], Port[%d]\n", SRVIP, serverAddr.sin_port);

    //监听，当socket和一个地址绑定之后，listen()函数会开始监听可能的连接请求
    if(listen(serverSock,10)==-1)
    {
        printf("监听（listen）失败!\n");
    }
    printf("监听（listen）成功：port[%d]\n", serverAddr.sin_port);

    char recvBuf[MAX_NUM]={0};
    char sendBuf[MAX_NUM]={0};
	while(1)
    {
        struct sockaddr clientAddr;
        int size = sizeof(clientAddr);
        //阻塞，直到有新tcp客户端连接
		//在客户端创建并连接之前，一直阻塞在这里
        int clientSock = accept(serverSock, &clientAddr, &size);
        printf("***SYS***    New client touched.\n");
        //在客户端连接之后，在这个循环中不断接收和发送
		while(1)
        {
            //一直接收客户端socket的send操作
            if(recv(clientSock, recvBuf, MAX_NUM, 0) == -1)
            {	printf("read error.\n");  }
            else
            {
                printf("receiv from client:%s\n",recvBuf);
            }
            if(strcmp(recvBuf,"Quit") == 0 || strcmp(recvBuf,"quit") == 0)
            {
                strcpy(sendBuf, "Goodbye,my dear client!");
            }
            else
            {
                strcpy(sendBuf, "Hello Client.");
            }

            // 向客户端发送套接字
            if(send(clientSock, sendBuf , sizeof(sendBuf), MSG_NOSIGNAL) == -1)
            {
                printf("Send error!\n");
            }
            else
            {
                printf("Send to client:%s\n", sendBuf);
            }
            if(strcmp(recvBuf, "Quit") == 0 || strcmp(recvBuf, "quit") == 0)
            {
                break;
            }
            memset(recvBuf, 0, sizeof(recvBuf));
            memset(sendBuf, 0, sizeof(sendBuf));
        }
        close(clientSock);
    }

    //关闭监听socket
    close(serverSock);
    return 0;
}


    
/**************************
客户端流程：
1.创建clientSocket
2.初始化 serverAddr
3.链接到服务器 connect
4.利用send和recv进行读写操作
5.关闭clientSocket
**************************/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
            
#define CLTIP "127.0.0.1"
#define SRVPORT 10005
#define MAX_NUM 80
int main()
{
    // 延迟1s
    //sleep(1000);

    // socket() 为通讯创建一个端点，为套接字返回一个文件描述符
    int clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientsock < 0)
    {
        printf("socket creation failed\n");
        exit(-1);
    }
    printf("socket create successfully.\n");

    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons((u_short)SRVPORT);
    clientAddr.sin_addr.s_addr = inet_addr(CLTIP);

    if(connect(clientsock, (struct sockaddr*)&clientAddr, sizeof(struct sockaddr)) < 0)
    {
        printf("Connect error.IP[%s], port[%d]\n", CLTIP, clientAddr.sin_port);
        exit(-1);
    }
    printf("Connect to IP[%s], port[%d]\n", CLTIP, clientAddr.sin_port);

    char sendBuf[MAX_NUM]={0};
    char recvBuf[MAX_NUM]={0};
    while(fgets(sendBuf,MAX_NUM,stdin) != '\0')
    {
        if(send(clientsock, sendBuf, strlen(sendBuf) + sizeof(char), 0) == -1)
        {
            printf("send error!\n");
        }
        printf("send to server:%s\n", sendBuf);
        memset(sendBuf, 0, sizeof(sendBuf));

        if(recv(clientsock, recvBuf, MAX_NUM, 0) == -1)
        {
            printf("rev error!\n");
        }
        printf("receive from server:%s\n",recvBuf);
        if(strcmp(recvBuf,"Goodbye,my dear client!")==0)
        {
            break;
        }
        memset(recvBuf, 0, sizeof(recvBuf));
    }
    close(clientsock);
    return 0;
}