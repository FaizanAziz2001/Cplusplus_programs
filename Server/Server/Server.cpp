#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <time.h> 
#include <thread>
#include <vector>
#include <random>
#include <time.h>
#include <fstream>
#include <windows.h>


#pragma comment(lib, "Ws2_32.lib")
using namespace std;


#define DEFAULT_PORT "8000"
#define DEFAULT_BUFLEN 1024
#define DEFAULT_CLIENTS 3
#define FILE_TRANSFER_FLAG 0x01



void sendTransferAcknowledge(SOCKET ClientSocket) {
	int iResult;
	char transferFlag = FILE_TRANSFER_FLAG;
	iResult = send(ClientSocket, &transferFlag, 1, 0);
	if (iResult == SOCKET_ERROR) {
		cout << "send failed: " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();

		exit(1);
	}
}

bool checkForTransferAcknowledge(SOCKET ClientSocket) {
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		if (recvbuf[0] == FILE_TRANSFER_FLAG) {
			return true;
		}
	}
	else if (iResult == 0) {
		cout << "Connection closed" << endl;
		return false;
	}
	else {
		cout << "recv failed: " << WSAGetLastError() << endl;
		return false;
	}

	return false;

}

void initWinsock() {

	cout << "----------------Server----------------" << endl;
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0) {
		cout << "WSAStartup failed: " << iResult << endl;
		exit(1);
	}
}

void resolveAddress(struct addrinfo** result, struct addrinfo* hints) {
	int iResult;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, hints, result);
    if (iResult != 0) {
		cout << "getaddrinfo failed: " << iResult << endl;
		WSACleanup();
		exit(1);
	}
}

void createSocket(SOCKET* ListenSocket, struct addrinfo* result) {
	// Create a SOCKET for the server to listen for client connections

	*ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (*ListenSocket == INVALID_SOCKET) {
		cout << "socket failed: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}
}

void bindSocket(SOCKET* ListenSocket, struct addrinfo* result) {
	int iResult;

	// Setup the TCP listening socket
	iResult = bind(*ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
		cout << "bind failed: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(*ListenSocket);
		WSACleanup();
		exit(1);
	}
}

void listenSocket(SOCKET* ListenSocket) {
	int iResult;

	// Listen on the socket
	iResult = listen(*ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
		cout << "listen failed: " << WSAGetLastError() << endl;
		closesocket(*ListenSocket);
		WSACleanup();
		exit(1);
	}
	else
		cout << "listenning on port " << DEFAULT_PORT << endl;
}

void acceptClient(SOCKET* ClientSocket, SOCKET* ListenSocket) {
	// Accept a client socket


	*ClientSocket = accept(*ListenSocket, NULL, NULL);
    if (*ClientSocket == INVALID_SOCKET) {
		cout << "accept failed: " << WSAGetLastError() << endl;
		closesocket(*ListenSocket);
		WSACleanup();
		exit(1);
	}

}

void shutdownSocket(SOCKET* ClientSocket) {
	// shutdown the connection since we're done
	int iResult = shutdown(*ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown failed: " << WSAGetLastError() << endl;
		closesocket(*ClientSocket);
		WSACleanup();
		exit(1);
	}
}


// ---------------------------------------------------File Transfer Functions---------------------------------------------------

void getClientInfo(SOCKET* ClientSocket, string& current_user) {
	// get client username and id and store it in map
	// format is $username$id$

	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = recv(*ClientSocket, recvbuf, recvbuflen, 0);

	if (iResult > 0) {
		string username = "";
		string id = "";

		int i = 1;
		while (recvbuf[i] != '$') {
			username += recvbuf[i];
			i++;
		}
		i++;
		while (recvbuf[i] != '$') {
			id += recvbuf[i];
			i++;
		}

		current_user = id;
		string path = "mkdir " + id;

		cout << "Client " << id << " connected" << endl;

		// create directory for user
		system(path.c_str());

	}
	else if (iResult == 0) {
		cout << "Connection closed" << endl;
	}
	else {
		cout << "recv failed: " << WSAGetLastError() << endl;
	}
}

void sendInitialMessage(SOCKET ClientSocket,string& current_user) {

	getClientInfo(&ClientSocket,current_user);
	int iResult;
	string response = "Welcome to the server\n 1) Download a file, <filename>\n 2) Upload a file, <filename>\n 3) Delete a file, <filename>\n";

	iResult = send(ClientSocket, response.c_str(), response.size(), 0);
	if (iResult == SOCKET_ERROR) {
		cout << "send failed: " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();

		exit(1);
	}
}

void uploadFile(SOCKET ClientSocket,string filename) {
	cout << "Receiving file .... " << endl;
	int iResult;
	fstream file;
	file.open(filename, ios::out | ios::binary);

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

			if (recvbuf[0] == FILE_TRANSFER_FLAG) {
				break;
			}
			file.write(recvbuf, iResult);
			sendTransferAcknowledge(ClientSocket);
		}
		else if (iResult == 0) {
			cout << "Connection closed" << endl;
			file.close();
			return;
		}
		else {
			cout << "recv failed: " << WSAGetLastError() << endl;
			file.close();
			return;
		}
	} while (iResult > 0);

	file.close();
	cout << "Upload Complete!" << endl;
}

void downloadFile(SOCKET ClientSocket, string filename) {

	cout << "Sending file .... " << endl;
	int iResult;
	ifstream file(filename, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		cout << "File not found" << endl;
		sendTransferAcknowledge(ClientSocket);
		return;
	}

	char buffer[DEFAULT_BUFLEN];
	while (!file.eof()) {
		file.read(buffer, DEFAULT_BUFLEN);
		int bytesRead = file.gcount();

		if (bytesRead > 0) {
			iResult = send(ClientSocket, buffer, bytesRead, 0);
			if (iResult == SOCKET_ERROR) {
				cout << "send failed: " << WSAGetLastError() << endl;
				closesocket(ClientSocket);
				WSACleanup();
				exit(1);
			}
			checkForTransferAcknowledge(ClientSocket);
		}
	}
	file.close();

	//send transfer acknowledge
	sendTransferAcknowledge(ClientSocket);

	cout << endl << "Transfer Complete!" << endl;

}

void deleteFile(SOCKET ClientSocket, string filename) {
	cout << "Deleting file .... " << endl;
	if (remove(filename.c_str()) != 0) {
		cout << "Error deleting file" << endl;
	}
	else {
		cout << "File successfully deleted" << endl;
	}
}

void handleClient(SOCKET ClientSocket,SOCKET ListenSocket) {

	string current_user;

	acceptClient(&ClientSocket, &ListenSocket);
	sendInitialMessage(ClientSocket,current_user);

	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
    do {

		cout << "------------------------------------------------" << endl;
		cout << "Waiting for client request..." << endl<<endl;

		iResult = recv(ClientSocket, recvbuf, recvbuflen-1, 0);
		recvbuf[iResult] = '\0';
			
        if (iResult > 0) {
			cout << "Server received: " << recvbuf << endl;
			sendTransferAcknowledge(ClientSocket);

			// response format is $<command>$<filename>$
			string command = "";
			string filename = current_user + '/';

			int i = 1;
			while (recvbuf[i] != '$') {
				command += recvbuf[i];
				i++;
			}
			i++;
			while (recvbuf[i] != '$') {
				filename += recvbuf[i];
				i++;
			}
			cout << "Command: " << command << endl<< "Filename: " << filename << endl << endl;

			if (command == "1") {
				downloadFile(ClientSocket, filename);
			}
			else if (command == "2") {
				uploadFile(ClientSocket, filename);
			}
			else if (command == "3") {
				deleteFile(ClientSocket, filename);
			}
			else {
					cout << "Invalid command" << endl;
			}	

		}
		else if (iResult == 0)
		{
			// shutdown the connection since we're done
			shutdownSocket(&ClientSocket);

			// cleanup
			closesocket(ClientSocket);
		}
        else {
			cout << "recv failed: " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
			WSACleanup();

			exit(1);
		}

	} while (iResult > 0);
}

int main()
{

	vector<thread> clientThreads;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;


    // Initialize Winsock
    initWinsock();
	srand(time(0));

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    resolveAddress(&result, &hints);

    // Create a SOCKET for the server to listen for client connections.
    createSocket(&ListenSocket, result);

    // Setup the TCP listening socket
    bindSocket(&ListenSocket, result);

    freeaddrinfo(result);

    listenSocket(&ListenSocket);
	cout << endl;

	while (true) {

	
		clientThreads.push_back(thread(handleClient, ClientSocket,ListenSocket));

	}

	for (auto& th : clientThreads) th.join();

    // No longer need server socket
    closesocket(ListenSocket);

    WSACleanup();

    return 0;
}
