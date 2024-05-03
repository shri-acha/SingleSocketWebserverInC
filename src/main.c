#include<stdio.h>
#include<sys/socket.h>//defines socket()
#include<stdlib.h> //Defines exit
#include<netinet/in.h> //Defines sockaddr_in,sin_port,sin_addr,sin_port

#define PORT 8080

void main(){

	int server_fd;
	struct sockaddr_in server_addr; //Is almost sockaddr but uses 

	if((server_fd = socket(AF_INET6,SOCK_STREAM,0)) < 0){
		perror("Error occured in starting the socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET6; //Assigns the family of IP address to ipv4
	server_addr.sin_addr.s_addr = INADDR_ANY; //assigns INADDR_ANY(all IP assigned to machine) 
	server_addr.sin_port = htons(PORT); //converts from host byte order into network byte order and assigns to sin(Socket Input taker)_port.
					    


	if(bind(server_fd,
		(struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0)
	{

		printf("%d",server_fd);
		perror("Bind Failure!");
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd,10)<0){
		perror("Listen Failed");
		exit(EXIT_FAILURE);
	}

	while(1){

		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int* client_fd =(int*) malloc(sizeof(int));
	
		if(*client_fd = accept(server_fd,
					(struct sockaddr*)&client_addr,
					&client_addr_len)<0) //It assigns the pointer to integer, client_fd an integer address returned by accept.
							     //Look up the syntax for accept() but probably the server_addr(accept the socket request to),client_addr stores the socket information,and size of client_addr is necessary for the acceptance of the request.
		{
			 
			perror("Error in accepting");	

		}



	}

}

