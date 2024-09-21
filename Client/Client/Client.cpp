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

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

#define DEFAULT_BUFLEN 10000
#define DEFAULT_PORT "8000"
#define DEFAULT_CLIENTS 1
#define FILE_TRANSFER_FLAG 0x01


string generateRandomUsername()
{
	string username = "";
    for (int i = 0; i < 10; i++)
    {
		username += rand() % 26 + 65;
	}
	return username;
}

// -----------------------------------------Helper Functions-----------------------------------------
int intRand(const int& min, const int& max) {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void sendTransferAcknowledge(SOCKET ConnectSocket) {
    int iResult;
    char transferFlag = FILE_TRANSFER_FLAG;
    iResult = send(ConnectSocket, &transferFlag, 1, 0);
    if (iResult == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
}

bool checkForTransferAcknowledge(SOCKET ConnectSocket) {
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
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

	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	int iResult = WSAStartup(version, &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed: " << iResult << endl;
        WSACleanup();
		exit(1);
	}
}

void shutDownSocket(SOCKET ConnectSocket) {
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        cout << "shutdown failed: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
}


// -----------------------------------------File Transfer Functions-----------------------------------------    

void sendClientInfo(SOCKET ConnectSocket,int id, string username) {
	string message="$"+username+"$"+to_string(id) + "$";

	int iResult = send(ConnectSocket, message.c_str(), message.size(), 0);
    if (iResult == SOCKET_ERROR) {
		cout << "send failed: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}
}

void uploadfile(SOCKET ConnectSocket,string filename) {

    cout << "Uploading file..." << endl;
	int iResult;
    ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
		cout << "File not found" << endl;
		return;
	}


    char buffer[DEFAULT_BUFLEN];
    while (!file.eof()) {
		file.read(buffer, DEFAULT_BUFLEN);
		int bytesRead = file.gcount();

        if (bytesRead > 0) {
			iResult = send(ConnectSocket, buffer, bytesRead, 0);
            if (iResult == SOCKET_ERROR) {
				cout << "send failed: " << WSAGetLastError() << endl;
				closesocket(ConnectSocket);
				WSACleanup();
				exit(1);
			}
            checkForTransferAcknowledge(ConnectSocket);
		}
	}
	file.close();
    //send transfer acknowledge
    sendTransferAcknowledge(ConnectSocket);

    cout << "Upload Complete!" << endl;

}

void downloadFile(SOCKET ConnectSocket,string filename) {

    cout << "Downloading file..." << endl;
    int iResult;
    fstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file.is_open()) {
		cout << "File not found" << endl;
		return;
	}

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0) {

            if (recvbuf[0] == FILE_TRANSFER_FLAG) {
				break;
			}
            file.write(recvbuf, iResult);
            sendTransferAcknowledge(ConnectSocket);
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
    cout << "Download Complete" << endl;
}

void sendFilename(SOCKET ConnectSocket, string message) {
	int iResult = send(ConnectSocket, message.c_str(), message.size(), 0);
    if (iResult == SOCKET_ERROR) {
		cout << "send failed: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}
    else
    {
		cout << "Client sent: " << message << endl;
	}
}

void receiveInitialMenu(SOCKET ConnectSocket, string username) {
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    iResult = recv(ConnectSocket, recvbuf, recvbuflen - 1, 0);
    recvbuf[iResult] = '\0';


    if (iResult > 0)
        cout << "Client " << username << " received: " << recvbuf << endl;
    else if (iResult == 0)
        cout << "connection closed" << endl;
    else if (iResult < 0)
        cout << "recv failed: " << WSAGetLastError() << endl;
}

void deleteFile(SOCKET ConnectSocket) {
    cout << "Deleting file....." << endl;
    cout << "File deleted" << endl;
}

void operationType(SOCKET ConnectSocket,int id,string username) {
    int operation;
    string filename;
    string message;

    sendClientInfo(ConnectSocket,id, username);
    receiveInitialMenu(ConnectSocket, username);


    while (true)
    {
        cout << "------------------------------------------------" << endl << endl;
        cout << "Enter filename: ";
        cin >> filename;
        cout << "Enter operation: ";
        cin >> operation;
        cout << endl;

        message= "$" + to_string(operation) + "$" + filename + '$';

        sendFilename(ConnectSocket, message);
        if (!checkForTransferAcknowledge(ConnectSocket))
        {
            cout << "No response from server" << endl;
            return;
        }

        switch (operation) {
        case 1:
            downloadFile(ConnectSocket, filename);
            break;
        case 2:
            uploadfile(ConnectSocket, filename);
            break;
        case 3:
            deleteFile(ConnectSocket);
            break;
        default:
            cout << "Invalid operation" << endl;
            break;
        }
        system("pause");
    }

}

int runClient(int id,string letter) {

    srand(id);
    cout << "Client " << letter << " running with id "<< id << endl;

	struct addrinfo* result = NULL, * ptr = NULL, hints;
	int iResult;
	SOCKET ConnectSocket = INVALID_SOCKET;


    const char* address = "localhost";

    initWinsock();
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    // Resolve the server address and port
    iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

 
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    operationType(ConnectSocket,id, letter);

    // cleanup
    shutDownSocket(ConnectSocket);
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;

}

int main() {

    vector<thread> threads;
 
    cout << "Running " << DEFAULT_CLIENTS << " clients" << endl<<endl;
    for (int i = 0; i < DEFAULT_CLIENTS; i++) {
        int id = intRand(1, 10000);
        string username = generateRandomUsername();
        

        threads.push_back(thread(runClient,id,username));

        // for sequential printing
        Sleep(0.1);
	}

	for (auto& th : threads) th.join();

	return 0;
}