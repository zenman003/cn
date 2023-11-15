#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 10200

// Function to decrypt a message
void decrypt(char *message, int key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = ((message[i] - 'a'-key + 26) % 26)+'a';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = ((message[i]-'A'- key + 26) % 26)+'A';
        }
    }
}

void encrypt(char *message, int key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = ((message[i] - 'a' + key) % 26) + 'a';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = ((message[i] - 'A' + key) % 26) + 'A';
        }
    }
}

int main() {
    int sockfd, newsockfd, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("10.0.2.15");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    while (1) {
        char buf[256];
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        n = read(newsockfd, buf, sizeof(buf));
        printf("\nSERVER: Received the string %s from the client.\n", buf);
        decrypt(buf, 4);
        printf("\nSERVER: Decrypted the string %s.\n", buf);
        encrypt(buf, 4);
        printf("\nSERVER: Encrypted the string %s.\n", buf);
        n = write(newsockfd, buf, sizeof(buf));
        printf("\nSERVER: Sent the string %s to the client.\n", buf);
    }

    return 0;
}
