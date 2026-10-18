#include <stdio.h>        
#include <stdbool.h>      
#include <stdlib.h>       
#include <string.h>       
#include <unistd.h>       
#include <arpa/inet.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  

#include "scanner.h"       


void print_help(const char *prog);



typedef struct {
    int group1 ;
    int group2 ;
    int group3 ;
    char ip[32];
}scanConf;



int main(int argc, char *argv[])
{
    int range = 0;

    //
    
    if(argc > 5)
    {
	printf("to many arguments\n");
	return EXIT_FAILURE;
    }

    if(argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
		print_help(argv[0]);
		return EXIT_SUCCESS;
    }
    

    scanConf *conf = calloc(1, sizeof(scanConf));
    if(conf == NULL){return EXIT_FAILURE;}


    for(int i = 1; i < argc; i++)
    {
		//group 1
		if(strcmp(argv[i], "-p") == 0)
		{
			conf->group1= 1;
		}

		else if (strcmp(argv[i], "-p-") == 0) 
		{
			conf->group1= 2;
		}

		//group 2
		else if(strcmp(argv[i], "-v") == 0)
		{
			conf->group2= 1;
		}

		else if(strcmp(argv[i], "-o") == 0)
		{
			conf->group2= 2;
		}

		//group 3
		else if(strcmp(argv[i], "-s") == 0)
		{
			conf->group3= 1;
		}

		else if(strcmp(argv[i], "-f") == 0)
		{
			conf->group3= 2;
		}

		//ip
		else
		{
			strncpy(conf->ip, argv[i], sizeof(conf->ip) - 1);
			conf->ip[sizeof(conf->ip) - 1] = '\0';
		}
    }


    if(conf->group1 ==0 ||
       conf->group2 ==0 ||
       conf->group3 ==0 ||
       strlen(conf->ip) ==0)
    {
		printf("Error: check the parameters\n");
		free(conf);
		return EXIT_FAILURE;
    }
    
    if(conf->group1 == 2)
    {
		range = 65535;
    }
    else 
    {
		range = 1024;
    }

    scan(range, conf->group2, conf->group3, conf->ip);



   

    free(conf);
    return EXIT_SUCCESS;
}




void 
print_help(const char *prog)
{
    printf("\n");
    printf("usage: %s [group 1] [group 2] [group 3] <ip-address>\n", prog);
    printf("options:\n");
    printf("[1]\n");
    printf("-p = scan only up to port 1024\n");
    printf("-p- = scan all ports\n");
    printf("\n");
    printf("[2]\n");
    printf("-v = verbose (you can see all of the scan process)\n");
    printf("-o = see only the open port at the report\n");
    printf("\n");
    printf("[3]\n");
    printf("-s = slow scan (traffic less noticeable)\n");
    printf("-f = aggressive scan (traffic more noticeable)\n");
    printf("\n");
    
}

