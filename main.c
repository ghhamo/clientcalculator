#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "util.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: calculator /path/to/input.txt");
        return 0;
    }
    int sock;
    struct sockaddr_in server;
    char *inputFileName = argv[1];
    FILE *outputFile = fopen("output.txt", "w");
    char *fileContent = readFile(inputFileName);
    int fileContentLength = strlen(fileContent);
    char *server_reply = (char *)malloc(sizeof(double));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
        abort();
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    int expressionStartIndex = 0;
    int i;
    for (i = 0; i <= fileContentLength; ++i)
    {
        char currentChar = fileContent[i];
        if (currentChar == '\n' || currentChar == '\0')
        {
            char *subString = getSubString(expressionStartIndex, i, fileContent);
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
                fprintf(outputFile, "%s\n", server_reply);
            }
            expressionStartIndex = i + 1;
        }
    }
    fclose(outputFile);
    close(sock);
}