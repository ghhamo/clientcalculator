#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "util.h"

int main()
{

    int sock;
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    char *server_reply = (char *)malloc(sizeof(double));
    while (1)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            printf("Could not create socket");
            abort();
        }

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            perror("connect failed. Error");
            return 1;
        }
        int expressionStartIndex = 0;
        char *expressionString = readInput();
        unsigned int expressionLength = strlen(expressionString);
        for (int i = 0; i <= expressionLength; ++i)
        {
            char currentChar = expressionString[i];
            if (currentChar == '\n')
            {
                char *subString = getSubString(expressionStartIndex, i, expressionString);
                int subStringLength = i - expressionStartIndex + 1;

                if (send(sock, subString, subStringLength, 0) < 0)
                {
                    printf("Send failed. Error");
                    abort();
                }
                memset(server_reply, 0, sizeof(server_reply));
                if (recv(sock, server_reply, sizeof(double), 0) < 0)
                {
                    printf("Recv failed. Error");
                    abort();
                }
                else
                {
                    printf("%s\n", server_reply);
                }
                expressionStartIndex = i + 1;
            }
        }
    close(sock);
    }
}