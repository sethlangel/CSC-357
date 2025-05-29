#define _GNU_SOURCE
#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#define PORT 10170

void signal_handler(int signum)
{
   int status;
   while((waitpid(-1, &status, WNOHANG) > 0))
      {
         if(WIFEXITED(status))
            {
               printf("Connection Closed with pid: %d\n", getpid());
	       break;
	    }
      }
}

void handle_request(int nfd)
{
   FILE *network = fdopen(nfd, "r");
   char *line = NULL;
   size_t size;
   ssize_t num;

   if (network == NULL)
   {
      perror("fdopen");
      close(nfd);
      return;
   }

   while((num = getline(&line, &size, network)) >= 0)
   {
      char *request_type = strtok(line, " \n");
      char *filename = strtok(NULL, " \n");
	
      if(strcmp(request_type, "GET") == 0)
      {
          int fd = open(filename, O_RDONLY);
	  if(fd == -1)
	  {
	     char buff[] = "Error: File failed to open.\n";
	     write(nfd, buff, sizeof(buff));
             free(line);
	     fclose(network);
	     exit(1);
          }

	  char buff[256];
          int bytes = read(fd, buff, sizeof(buff));
          if(bytes <= 0)
	  {
	     char error[] = "Error: Read 0 bytes in file.\n";
	     write(nfd, error, sizeof(error));
	     free(line);
	     fclose(network);
	     exit(1);
	  }
	
	  write(nfd, buff, bytes);  
      }
       else
       {
	  char buff[] = "Invalid use: GET <filename>\n";
	  write(nfd, buff, sizeof(buff));
       } 
   }
   
   free(line);
   fclose(network);
}

void run_service(int fd)
{
   while (1)
   {
      int nfd = accept_connection(fd);
      if (nfd != -1)
      {
	 pid_t pid;

	 if((pid = fork()) < 0)
	 {
	    perror("Error: Failed to create child process.\n");
	    exit(1);
	 }
	 else if(pid == 0)
	 {
	    printf("Connection established on pid: %d\n", getpid());
            handle_request(nfd);
	    exit(0);
	 }
	 else
	 {
	    printf("Available for more connections... with process: %d\n", getpid());
         }
      }
   }
}

int main(void)
{
   int fd = create_service(PORT);
   signal(SIGCHLD, signal_handler);
   if (fd == -1)
   {
      perror(0);
      exit(1);
   }

   printf("listening on port: %d\n", PORT);
   run_service(fd);
   close(fd);

   return 0;
}
