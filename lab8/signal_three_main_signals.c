#include<stdio.h> 
#include<stdlib.h> 
#include<signal.h>

int i = 0;
void quit(int code) {
	printf("\nInterrupt (code=%d, i=%d)\n",code,i);
	exit(123); 
}
int main(void) {
	signal(SIGINT, quit); 
	signal(SIGTERM, quit); 
	signal(SIGQUIT, quit);
	while(1)
             if (i++ % 5000000 == 0) 
		putc( '.',stderr);
        return(0);
}
