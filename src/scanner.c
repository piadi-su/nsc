#include <stdio.h>      
#include <stdbool.h>    
#include <stdlib.h>     
#include <unistd.h>     
#include <arpa/inet.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 


#include "scanner.h"



void scan(int range_p, int verbose, int fast_mode, char ip[32])
{
    

    int delay;
    
    Report *report = malloc(sizeof(Report));
    if(report == NULL){ return;}

    report->ports = NULL;
    report->count = 0;
    


    if(fast_mode == 2)
    {
		delay = 200000; // fast
    }
    else
    {
		delay = 2000000; // slow
    }
    




    struct sockaddr_in target;

    target.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &target.sin_addr);

    for (int port = 1; port <= range_p; port++) {
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			perror("socket");
			continue;
		}

		target.sin_port = htons(port);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = delay; 

		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

		int result = connect(sock, (struct sockaddr*)&target, sizeof(target));

		if (result == 0) 
		{
			if(verbose == 1)
			{
				printf("port %d open\n", port);
			}
			add_port(report, port);
		}

		close(sock);
    }
    
    print_report(report, ip);

    free(report->ports);
    free(report);

}


void add_port(Report *r, int port)
{
    int *tmp = realloc(r->ports, (r->count + 1) * sizeof(int));
    if(!tmp){ return;}
    r->ports = tmp;


    r->ports[r->count] = port;
    r->count++;
}

void print_report(Report *r, char ip[32])
{
    printf("\nnsc scan for: %s\n", ip);
    printf("PORT \n");

    for (int i = 0; i < r->count; i++) {
        printf("[+] %d  - open\n", r->ports[i]);
    }

    printf("Total open ports: %d\n", r->count);
}
    
