#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <winsock2.h>

int main(int argc, char * argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;

    char buffer[1024];

    if(argc<3){
        printf("provide required command line inputs as <filename.c> <server_IP_addr> <portno>");
        exit(1);
    }
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    //verificam daca socket este creat corect

    if(sockfd < 0){
        printf("ERROR in opening socket");
        exit(1);

    }
    // crearea structurii adresei serverului

    serv_addr.sin_family = AF_INET;

    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // Acum incercam conectarea la server

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))< 0)
    {
        printf("Connection failed...!!!");
        exit(1);
    }
    while(1)
    {
        bzero(buffer, 1024); // curatarea bufferului

        // Scriere date pentru serever

        fgets(buffer, 1024, stdin);
        n=write(sockfd, buffer, strlen(buffer));
        if(n<0){
            printf("ERROR in writing....");
            exit(1);

        }

        //  Primirea datelor de la server
        bzero(buffer, 1024); // curatare
        n=read(sockfd, buffer,1024);
        if(n<0)
        {
            printf("Error in reading... ");
            exit(1);

        }
        // print raspunsul serverului
        printf("\n Server --> %s", buffer);


        // detectarea sfarsitului conversatiei

        if(!strncmp("bye", buffer, 3))
            break;

    }
    close(sockfd);
    return 0;



}