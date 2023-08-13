#ifndef SIMPLEST_HTTP_H
#define SIMPLEST_HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// source code

const char *HTTP_HEADER_GOOD_FORMAT = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: %ul\n\n%s";
const char *HTTP_HEADER_MISSING_FORMAT = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: %lu\n\n%s";
const char *HTTP_HEADER_GOOD_HTML_FORMAT = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %lu\n\n%s";


const char *methods[] = {
    "GET",
    "POST",
    "DELETE",
    "PATCH",
    "OPTIONS",
    "HEAD"
};


enum METHOD {
    GET, POST, DELETE,PATCH, OPTIONS, HEAD
};

const int METHOD_ARRAY_SIZE = 6;



extern const char * extract_route(const char *client_buffer, char *output)
{
    // o de cima será a requisiçao, o debaixo o formato do client_buffer
    // http://localhost:3000?ok=999

    // GET /?ok=999 HTTP/1.1
    // http://localhost:3000/test

    // GET /teste HTTP/1.1
    // http://localhost:3000

    // GET / HTTP/1.1
    // codigo de extrassao

      // POST / HTTP/1.1
    // codigo de extrassao


    char method[8];
    sscanf(client_buffer, "%s %s HTTP", method, output);
    for (int i = 0; i < METHOD_ARRAY_SIZE; i++)
    {
        if (strcmp(methods[i], method) == 0)
            return methods[i];
    }
}



typedef const char *(*ResponseCallback)(const char *method, const char *route, const char *buffer);

void extern run_server(int port, ResponseCallback responsecallback, int * running)
{
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[1024] = {0};
     char route[255];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Erro ao fazer o bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 10) < 0)
    {
        perror("Erro ao ouvir as conexões");
        exit(EXIT_FAILURE);
    }

    while (*running)
    {
        unsigned int cli_len = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
        if (newsockfd < 0)
        {
            perror("Erro ao aceitar a conexão");
            exit(EXIT_FAILURE);
        }

        read(newsockfd, buffer, sizeof(buffer));
       
        const char * method = extract_route(buffer, route);
        const char *response = responsecallback(method, route, buffer);
        write(newsockfd, response, strlen(response));
        memset(buffer, 0, sizeof(buffer));
        close(newsockfd);
    }

    close(sockfd);
}

#endif
