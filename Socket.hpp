//Socket.h
//#pragma once

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

# define closesocket close
using namespace std;

const int STRLEN = 256;

class Socket {
protected:
//	WSADATA wsaData;
	int mySocket;
	int myBackup;
	int acceptSocket;
	sockaddr_in myAddress;
public:
	Socket();
	~Socket() {}
	bool SendData(char *);
	bool RecvData(char *, int );
	void CloseConnection();
	void GetAndSendMessage();
};

class ServerSocket : public Socket
{
public:
	void Listen();
	void Bind( int port );
	void StartHosting( int port );
};

class ClientSocket : public Socket
{
public:
	void ConnectToServer( const char *ipAddress, int port );
};