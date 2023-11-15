#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdbool.h>
#define PORT 10200



void removeduplicates(char* sen)
{
    char words[100][100];
    int numwords=0;

    char* token=strtok(sen," ");
    while(token!=NULL)
    {
        bool flag=false;
        for(int i=0;i!=numwords;i++)
        {
            if(strcmp(token,words[i])==0)
            {
                flag=true;
                break;
            }
        }

       if(!flag)
            {
                strcpy(words[numwords],token);
                numwords++;
            }
        token=strtok(NULL," ");
        }

        sen[0]='\0';
        for(int j=0;j<numwords;j++)
        {
            strcat(sen,words[j]);
            if(j<numwords-1)
            {
                strcat(sen," ");
            }
        } 

        }


int main()
{
    int sockfd,newsockfd,n;
    struct sockaddr_in client,server;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("10.0.2.15");
    server.sin_port=htons(PORT);
    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    listen(sockfd,1);
    while(1)
    {
        int clin=sizeof(client);
        char sentence[100];
        newsockfd=accept(sockfd,(struct sockaddr*)&client,&clin);
        n=read(newsockfd,sentence,sizeof(sentence));
        removeduplicates(sentence);

        n=write(newsockfd,sentence,sizeof(sentence));
        close(newsockfd);
    }
    
    return 0;
}