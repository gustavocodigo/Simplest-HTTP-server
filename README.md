

# Simplest-HTTP-server
an simple http server single threaded written in C
to used for Inter Process Comunication


comunication between different process





# Compilation
- the compilation is simple including the header file to your source code.

then you can use GCC 
```sh
gcc main.c
```



# Warnings
- this first version is for linux based kernels only
- this should not be used on web with various users its single threaded to be simple and easy to use



# Example
- send html
```c
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
            strcat(msg_final, "<p>Hello world</p>");
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

```
![image](https://github.com/gustavocodigo/Simplest-HTTP-server/assets/108258194/f8b28e9b-ce5c-4192-b8f8-9efe01122719)





# Example 2
- simple api

```C
#include <stdio.h>
#include "simplest-http.h"

char response_buffer[1024];
char msg_final[1024];



int visicount = 0;

const char *routers(const char *method, const char *route, const char *client_buffer)
{
    if (strcmp(route,"/") == 0)
    {
        visicount ++; // increment 
       sprintf(msg_final, "{\"visitcout\": %i}", visicount);
    }
    sprintf(response_buffer, HTTP_HEADER_GOOD_FORMAT, strlen(msg_final), msg_final);
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

```
![image](https://github.com/gustavocodigo/Simplest-HTTP-server/assets/108258194/47930ac5-0165-4cf3-99ff-8c65878306a1)




