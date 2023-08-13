#include <stdio.h>
#include "simplest-http.h"

char response_buffer[1024];
char msg_final[1024];


const char *routers(const char *method, const char *route, const char *client_buffer)
{
    msg_final[0] = '\0';

    if (strcmp(route,"/products") == 0)
    {
        strcat(msg_final, "<h1>Lista de produtos</h1>");
        for (int i = 0; i < 10; i++)
        {
            strcat(msg_final, "<p>Hello world</p>");
        }
    }
    sprintf(response_buffer, HTTP_HEADER_GOOD_HTML_FORMAT, strlen(msg_final), msg_final);
    printf("User used the method: %s\n", method);
    return response_buffer;
}




int main(int argc, char **argv)
{
    const int PORT = 2000;
    int running = 1;
    run_server(PORT, routers, &running);
    return 0;
}
