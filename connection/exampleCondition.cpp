// As seen on http://www.di.uniba.it/~reti/LabProRete/Interazione(TCP)Client-Server_Portabile.pdf
#if defined WIN32
# include <winsock.h>
#else
# define closesocket close
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
#endif

#include <stdio.h>

#define BUFFERSIZE 512
#define PROTOPORT 5193 // Numero di porta di default
# pragma comment(lib,"ws2_32.lib") //Winsock Library
void ClearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}

void ErrorHandler(char *errorMessage) {
	printf(errorMessage);
}

int main(void) {
#if defined WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2 ,2), &wsaData);
	if (iResult != 0) {
		printf("error at WSASturtup\n");
		return 0;
	}
#endif

// CREAZIONE DELLA SOCKET
	int Csocket;
	Csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Csocket < 0) {
		ErrorHandler("socket creation failed.\n");
		closesocket(Csocket);
		ClearWinSock();
		return 0;
	}
	// COSTRUZIONE DELL’INDIRIZZO DEL SERVER
	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("10.41.177.14"); // IP del server
	sad.sin_port = htons(5193); // Server port
	// CONNESSIONE AL SERVER
	if (connect(Csocket, (struct sockaddr *) &sad, sizeof(sad)) < 0) {
		ErrorHandler("Failed to connect.\n");
		closesocket(Csocket);
		ClearWinSock();
		return 0;
	}

	char* inputString = "prova"; // Stringa da inviare
	int stringLen = strlen(inputString); // Determina la lunghezza

	if (send(Csocket, inputString, stringLen, 0) != stringLen) {
		ErrorHandler("send() sent a different number of bytes than expected");
		closesocket(Csocket);
		ClearWinSock();
		return 0;
	}

	int bytesRcvd;
	int totalBytesRcvd = 0;
	char buf[BUFFERSIZE]; // buffer for data from the server
	printf("Received: "); // Setup to print the echoed string

	while (totalBytesRcvd < stringLen) {
		if ((bytesRcvd = recv(Csocket, buf, BUFFERSIZE - 1, 0)) <= 0) {
			ErrorHandler("recv() failed or connection closed prematurely");
			closesocket(Csocket);
			ClearWinSock();
			return 0;
		}
		totalBytesRcvd += bytesRcvd; // Keep tally of total bytes
		buf[bytesRcvd] = '\0'; // Add \0 so printf knows where to stop
		printf("%s", buf); // Print the echo buffer
	}
// CHIUSURA DELLA CONNESSIONE
	closesocket(Csocket);
	ClearWinSock();
	printf("\n"); // Print a final linefeed
	system("pause");
	return (0);
}