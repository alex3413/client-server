#pragma comment(lib, ws2_32.lib)
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

SOCKET connections[3];
int count = 0;

void clientHandler(int index){
	int strSize;
	while(true){
		recv(connections[index], (char*)&strSize, sizeof(int), NULL);
		char *str = new char[strSize+1];
		str[strSize] = '\0';
		recv(connections[index], str, sizeof(str), NULL);
		for(int i=0; i<count; i++){
			if(i == index)
				continue;
			send(connections[i], str, sizeof(str), NULL);
		}
		delete []str;
		
	}
}

int main(int argc, char** argv) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1);
	if(WSAStartup(DLLVersion, &wsaData) != 0){
		cout<<"Error \n";
		exit(1);
	}
	
	SOCKADDR_IN inAddr;
	inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = htons(1111);
	
	SOCKET ssocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(ssocket, (SOCKADDR*)&inAddr, sizeof(inAddr));
	listen(ssocket, 3);
	
	int sizeSock = sizeof(inAddr);
		
	SOCKET connection;
	for(int i = 0; i < 3;i++){
		connection = accept(ssocket, (SOCKADDR*)&inAddr, &sizeSock);
		if(connection == 0){
	
			cout<<"Error connect ssock \n";
		}
		else{
			cout<<"Client Connected \n";
			char msg[256];
			recv(connection, msg, sizeof(msg), NULL );
			cout<<msg<<endl;
			Sleep(1000);
			connections[i] = connection;
			count++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler,(LPVOID)(i), NULL, NULL);
			}
	}
	system("pause");
	return 0;
}
