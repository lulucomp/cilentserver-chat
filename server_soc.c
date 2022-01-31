#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{
    int sockfd, newsockfd, portno, n;
    struct sockaddr_in serv_addr, client_addr;

    char buffer[1024];

    socklen_t len;

    // verificarea nr de linii introduse de user

    if(argc<2)
    {
        printf("provide required command-line input as <filename.c> <portno");
        exit(1);

    }

    portno=atoi(argv[1]);
    sockfd= socket(AF_INET, SOCK_STREAM, 0);


    // verificam daca socket-ul a fost creat corect

    if(sockfd<0)
    {
        printf("Error in openning socket!");
        exit(1);

    }
    // crearea structurii adresei serverului

    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(protno);

    // Atasam socket adresei si numarului portului specificat in structura.

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        printf("Error in binding socket");

        listen(sockfd, 5);

        len = sizeof(client_addr);


        newsockfd = accept(sockfd,(struct sockaddr *)&client_addr, &len);


        // verificam daca socket client este creat corect

        if(newsockfd<0)
        {
            printf("ERROR in accepting request.../");
                exti(1);
        }

        while(1)
        {
            bzero(buffer, 1024); // curatarea buffer
            // Citirea unor date ale clientului
            n=red(newsockfd, buffer, 1024);

            if(n<0){
                printf("ERROR in reading....");
                exit(1);
            }

            // print client request data
            printf("\nClient --> &s", buffer);

            bzero(buffer, 1024); // curatarea buffer

            // Rescurierea datelor pentru client

            fgets(buffer, 1024, stdin);
            n=write(newsockfd, buffer,1024);

            if(n<0)
            {
                printf("ERROR in writing....");
                exit(1);

            }
            // detectarea sfarsitului conversatiei

            if(!strncmp("bye", buffer, 3))
            {
                break;
            }
                    
        
        }
        close(newsockfd);
        close(sockfd);
    return 0;        

}

