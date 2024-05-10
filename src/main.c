#include<stdio.h>
#include<sys/socket.h>//defines socket()
#include<stdlib.h> //Defines exit
#include<netinet/in.h> //Defines sockaddr_in,sin_port,sin_addr,sin_port
#include<pthread.h>
#define PORT 8080


void main(){

	int server_fd;
	struct sockaddr_in server_addr; //sockaddr_in is almost sockaddr but is used for ip4 addresses,and has padding with zeros to make the the memory
					//Equal to the sockaddr 

	if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Error occured in starting the socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET; //Assigns the family of IP address to ipv4
	server_addr.sin_addr.s_addr = INADDR_ANY; //assigns INADDR_ANY(all IP assigned to machine) 
	server_addr.sin_port = htons(PORT); //converts from host byte order into network byte order and assigns to sin(Socket Input taker)_port.
					    


	if(bind(server_fd,
		(struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0) 
		//bind requires the arguments of the empty server file descriptor(which is an integer
		//value that stores and represents the server and 
		//requires the socket address information{Type is casted to convert sockaddr[more standard storage]}). 
		//Checkout the documentation for sockaddr_in struct declaration,which has padding to have same storage as of sockaddr 
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
		int*client_fd = (int *) malloc(sizeof(int));

		if(*client_fd = accept(server_fd,
					(struct sockaddr*)&client_addr,
					&client_addr_len) < 0) //It assigns the pointer to integer, client_fd an integer address returned by accept.
							     //Look up the syntax for accept() but probably the server_addr(accept the socket request to)
							     //client_addr stores the socket information,and size of client_addr is necessary for the acceptance of the request.
		{
			perror("Error in accepting");	
		}
	//new thread to handle client request.
		pthread_t thread_id;
		pthread_create(&thread_id,NULL, handle_client,(void *)client_fd);
		pthread_detach(thread_id);
	}

}



