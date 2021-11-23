#define MAX_CHAR 80 // Max character of each string
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  // exit

const unsigned short int PORT = 1234;

void msg(int sockfd)
{
    char buff[MAX_CHAR];
    int n;

    for (;;) { //while(1)
        bzero(buff, MAX_CHAR);
   
        // read message and save it on buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX_CHAR);
        n = 0;
        // copy message which is sent from server
        while ((buff[n++] = getchar()) != '\n');
   
        //send message to client
        write(sockfd, buff, sizeof(buff));
   
        // message contains "exit" then server exit.	
        if (strncmp("exit", buff, 4) == 0) {
            printf("Disconnected\n");
            break;
        }
    }
}

int main(void)
{
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
	ownAddress.sin_family = AF_INET;  //AF_INET= IPv4
	ownAddress.sin_port = htons(PORT);  //htons=change Host byte order TO Network byte order, Short data
	ownAddress.sin_addr.s_addr = INADDR_ANY;  //INADDR_ANY=listen on each 
                                                  //available network interface;
						  //can also listen on a specific address
	memset(&(ownAddress.sin_zero), '\0', 8);

	//bind to the address and port:
	if( bind(fd, (struct sockaddr *) &ownAddress, sizeof(struct sockaddr)) == -1)
	{
		perror( "bind" );
		exit(2);
	}

	//listen (wait) for incoming connections from clients:
	if( listen(fd, 5) == -1)  //5=backlog (waiting queue length), usually between 5 and 10
	{
		perror( "listen" );
		exit(3);
	}

    	puts("Waiting for incoming connections...");

	//accept the incoming connection, ie. establish communication with a client:
	while(1){
	
		addrlen = sizeof(struct sockaddr_in);
		if( (connectionfd = accept( fd, (struct sockaddr *)&remAddress, &addrlen)) == -1 ) 
		{
			perror( "accept" );
			exit(4);
		}
		inet_ntop(AF_INET, &(remAddress.sin_addr), str, INET_ADDRSTRLEN);
		printf("Connection from: %s\n", str);

		//now we have a working connection between this server and some client;
		//we can receive and send data
		msg(connectionfd);
	}

	close( connectionfd );  //close connection when finished with this client
	close( fd );  //close server's socket when all server work is finished
	return 0;
}
