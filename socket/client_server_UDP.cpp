//socket udp 服务端
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    //创建socket对象
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(1324);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    //绑定socket对象与通信链接
    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind\n");
        return -1;
    }
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);
	//循环，收到信息后输出，并回信
    while(1)
    {
        char buf =0;
        recvfrom(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
        printf("recv num =%hhd\n",buf);
        buf =66;
        sendto(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&cli,len);
    }
    close(sockfd);
}

//socket udp 客户端
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    //创建socket对象
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(1324);
    addr.sin_addr.s_addr = inet_addr("192.168.0.143");
	//循环，扫描终端输入，并向服务器端发送，同时接受服务端消息
    while(1)
    {
        printf("请输入一个数字：");
        char buf=0;
        scanf("%hhd",&buf);
        sendto(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&addr,sizeof(addr));
        socklen_t len=sizeof(addr);
        recvfrom(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&addr,&len);
        if(66 ==buf)
        {
            printf(" server 成功接受\n");
        }
        else
        {
            printf("server 数据丢失\n");
        }
    }
    close(sockfd);
}