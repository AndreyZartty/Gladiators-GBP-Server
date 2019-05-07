//
// Created by jose on 27/03/19.
//
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <json-c/json.h>

#define PORT 3550
#define BACKLOG 4
#define MAXDATASIZE 1000

int main()
{

    int fd, fd2;

    struct sockaddr_in server;


    struct sockaddr_in client;



    if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        printf("error en socket()\n");
        exit(-1);
    }

    server.sin_family = AF_INET;

    server.sin_port = htons(PORT);


    server.sin_addr.s_addr = INADDR_ANY;


    bzero(&(server.sin_zero),8);

    if(bind(fd,(struct sockaddr*)&server,
            sizeof(struct sockaddr))==-1) {
        printf("error en bind() \n");
        exit(-1);
    }

    if(listen(fd,BACKLOG) == -1) {
        printf("error en listen()\n");
        exit(-1);
    }

    printf("Servidor abierto!\n");

    while(1) {

        unsigned int address_size = sizeof(client);

        if ((fd2 = accept(fd,(struct sockaddr *)&client,
                          &address_size))==-1) {
            printf("error en accept()\n");
            exit(-1);
        }

        printf("Se obtuvo una conexión de un cliente.\n");

        ssize_t r;

        char buff[MAXDATASIZE];

        for (;;)
        {
            r = read(fd2, buff, MAXDATASIZE);

            if (r == -1)
            {
                perror("read");
                return EXIT_FAILURE;
            }
            if (r == 0)
                break;
            printf("READ: %s\n", buff);
            struct json_object *codigo;
            json_object *parsed_json = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_json,"Codigo",&codigo);
            printf("Codigo: %s\n", json_object_get_string(codigo));
            memset(buff, 0, MAXDATASIZE);
        }

        close(fd2);

        //return EXIT_SUCCESS;
    }
}
