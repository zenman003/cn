#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#define PORT 10200

int main()
{
    int n,sockfd;
    struct sockaddr_in address;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("10.0.2.15");
    address.sin_port=htons(PORT);

    connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    char sentence[100];
    printf("enter the sentence\n");
    scanf("%[^\n]s",sentence);
    n=write(sockfd,sentence,sizeof(sentence));
    printf("the sentence recieved from server is\n");
    n=read(sockfd,sentence,sizeof(sentence));
    printf("%s",sentence);
    close(sockfd);
}