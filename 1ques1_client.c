#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to encrypt a message
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
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];
    int encryptionKey = 4; // Key for encryption

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.0.2.15");
    address.sin_port = htons(10200);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nCLIENT: Enter the string: ");
    scanf("%s", ch);
    encrypt(ch, encryptionKey);
    write(sockfd, ch, sizeof(ch));
    printf("\nCLIENT: Sent the string %s to the server.\n", ch);
    read(sockfd, buf, sizeof(buf));
    printf("\nCLIENT: Received the string %s from the server.\n", buf);
    close(sockfd);
    return 0;
}
