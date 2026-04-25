#ifndef SCANNER_H
#define SCANNER_H


typedef struct ports{
    int port;
    char service[32]; 
}ports ;

typedef struct {
    int *ports;
    int count;
} Report;

void scan(int range_p, int verbose, int fast_mode, char ip[32]);
void add_port(Report *r, int port);
void print_report(Report *r, char ip[32]);
#endif
