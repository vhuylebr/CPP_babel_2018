//Socket.cpp

#include "Socket.hpp"

Socket::Socket()
{
	//Create a socket
//	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP); // peut-être remplacer SOCK_STREAM par SOCK_DGRAM

	int s;

	if ((mySocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		std::cerr  <<"Socket Initialization: Error creating socket"<<endl;
		exit(84); // faire en dehors du constru
	}
	myBackup = mySocket;
}

bool Socket::SendData(char *buffer)
{
	send( mySocket, buffer, strlen(buffer), 0);
	//static_cast< const void *>(buffer.c_str()), buffer.length(), 0);
	return true;
}

bool Socket::RecvData(char *buffer, int size )
{
//	int i = 0;
	int i = recv( mySocket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Socket::CloseConnection()
{
	//std::cout <<"CLOSE CONNECTION"<<endl;
	closesocket( mySocket );
	mySocket = myBackup;
}

void Socket::GetAndSendMessage()
{
	char message[STRLEN];
//	std::string message;

	std::cin.ignore(); //without this, it gets the return char from the last cin and ignores the following one!
	std::cout  << "Send > ";
	std::cin.get(message, STRLEN);
	SendData(message);
}

void ServerSocket::StartHosting( int port )
{
	 Bind(port);
	 Listen();
}

void ServerSocket::Listen()
{
	//std::cout <<"LISTEN FOR CLIENT..."<<endl;

/*	if (listen (mySocket, 1 ) == -1)
	{
		std::cerr <<"ServerSocket: Error listening on socket\n";
		system("pause");
		exit(15);
	}*/

	std::cout <<"ACCEPT CONNECTION..."<<endl;

	acceptSocket = accept( myBackup, NULL, NULL );
	while ( acceptSocket == -1)
	{
		acceptSocket = accept( myBackup, NULL, NULL );
	}
	mySocket = acceptSocket;
}

void ServerSocket::Bind( int port )
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons( port );

	//std::cout <<"BIND TO PORT "<<port<<endl;

	if ( bind ( mySocket, (struct sockaddr*)&myAddress, sizeof(myAddress)) == -1)
	{
		std::cerr <<"ServerSocket: Failed to connect\n";
		system("pause");
		exit(14);
	}
}

void ClientSocket::ConnectToServer( const char *ipAddress, int port )
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr( ipAddress );
	myAddress.sin_port = htons( port );

	//std::cout <<"CONNECTED"<<endl;

	if ( connect( mySocket, (struct sockaddr*)&myAddress, sizeof( myAddress ) ) == -1)
	{
		std::cerr <<"ClientSocket: Failed to connect\n";
		system("pause");
		exit(13);
	} 
}
