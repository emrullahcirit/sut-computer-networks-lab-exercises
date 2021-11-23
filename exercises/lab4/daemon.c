#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAX 80


const unsigned short int PORT = 1234;

void msg(int sockfd)
{
	char buff[MAX];
	int n;
	
	for (;;) {
		
		bzero(buff, MAX);
		openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
		read(sockfd, buff, sizeof(buff));
		
		syslog (LOG_NOTICE, "From client: %s", buff);
		closelog();
		bzero(buff, MAX);
		n=0;

		write(sockfd, buff, sizeof(buff));	
	}

}

int main(void) {
        
        pid_t pid, sid;
        
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
       
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        // Change the file mode mask 
        umask(0);
   
        setlogmask (LOG_UPTO (LOG_NOTICE));
		openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);

		syslog (LOG_NOTICE, "Daemon started by User %d and ready for operation!", getuid ());
		closelog();
   
                
        // Create a new SID for the child process
        sid = setsid();
        if (sid < 0) {
                // Log the failure
                exit(EXIT_FAILURE);
        }
        

        
        // Change the current working directory
        if ((chdir("/")) < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }
        
        // Close out the standard file descriptors
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
        while (1) {
           
			int fd, connectionfd;
			struct sockaddr_in ownAddress;
			struct sockaddr_in remAddress;
			int addrlen;
			char str[INET_ADDRSTRLEN];

			//create a socket:
			if( (fd = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
			{
				perror( "socket" );
				exit(1);
			}

			//IP address and port number of the server:
			ownAddress.sin_family = AF_INET;
			ownAddress.sin_port = htons(PORT);  
			ownAddress.sin_addr.s_addr = INADDR_ANY; 
			memset(&(ownAddress.sin_zero), '\0', 8);

			if( bind(fd, (struct sockaddr *) &ownAddress, sizeof(struct sockaddr)) == -1)
			{
				perror( "bind" );
				exit(2);
			}

			
			if( listen(fd, 5) == -1)  //5=backlog (waiting queue length), usually between 5 and 10
			{
				perror( "listen" );
				exit(3);
			}

				puts("Waiting for incoming connections...");

			addrlen = sizeof(struct sockaddr_in);
			if( (connectionfd = accept( fd, (struct sockaddr *)&remAddress, &addrlen)) == -1 ) 
			{
				perror( "accept" );
				exit(4);
			}
			inet_ntop(AF_INET, &(remAddress.sin_addr), str, INET_ADDRSTRLEN);
			printf("Connection from: %s\n", str);
			msg(connectionfd); 
			
			addrlen = sizeof(struct sockaddr_in);
			if( (connectionfd = accept( fd, (struct sockaddr *)&remAddress, &addrlen)) == -1 ) 
			{
				perror( "accept" );
				exit(4);
			}
						
			inet_ntop(AF_INET, &(remAddress.sin_addr), str, INET_ADDRSTRLEN);

			printf("Connection from: %s\n", str); 
			

			close( connectionfd );  //close connection when finished with this client
			close( fd );  //close server's socket when all server work is finished
			return 0;
        }
   exit(EXIT_SUCCESS);
}

