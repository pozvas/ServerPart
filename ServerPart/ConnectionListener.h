#pragma once
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h> 
#include <iostream>

#pragma warning(disable: 4996)


class ConnectionListener
{
private:
	SOCKET _connections[100];
    SOCKET _serverSoket;
	int _counter; 
    SOCKADDR_IN _addr; 
    int _sizeOfAddr;

    static void ClientHandler(SOCKET* connection) {
        int msg_size;
        while (true) {
            recv(*connection, (char*)&msg_size, sizeof(int), NULL);
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';
            recv(*connection, msg, msg_size, NULL);

            char msgResp[] = "OK";
            msg_size = 3;
            send(*connection, (char*)&msg_size, sizeof(int), NULL);
            send(*connection, msgResp, msg_size, NULL);

            delete[] msg;
        }
    }


public:
    ConnectionListener() : _counter(0) {
        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2, 2);
        if (WSAStartup(DLLVersion, &wsaData) != 0) {
            std::cout << "Error" << std::endl;
            exit(1);

        }

        _sizeOfAddr = sizeof(_addr);
        _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        _addr.sin_port = htons(1111);
        _addr.sin_family = AF_INET;
        _serverSoket = socket(AF_INET, SOCK_STREAM, NULL);

        bind(_serverSoket, (SOCKADDR*)&_addr, sizeof(_addr));
    }

    void Listen(){
        listen(_serverSoket, SOMAXCONN);
        SOCKET newConnection;
        for (int i = 0; i < 100; i++) {
            newConnection = accept(_serverSoket, (SOCKADDR*)&_addr, &_sizeOfAddr);
            if (newConnection == 0) {
                std::cout << "Error #2 \n";
            }
            else {
                std::cout << "Client Connected! \n";
                std::string msg = "Hola hola UNN";
                int msg_size = msg.size();
                send(newConnection, (char*)&msg_size, sizeof(int), NULL); 
                send(newConnection, msg.c_str(), msg_size, NULL); 

                _connections[i] = newConnection;
                _counter++;
                CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)&_connections[i], NULL, NULL);
            }
        }

    }

};

