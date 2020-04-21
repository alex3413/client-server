#pragma comment(lib, ws2_32.lib)
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
using namespace std;
SOCKET csocket;
void clientHandler(){
	char msg[256];
	while(true){
		recv(csocket, msg, sizeof(msg), NULL);
		cout<<msg<<endl;
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
	
	 csocket = socket(AF_INET, SOCK_STREAM, NULL);
	
	if(connect(csocket, (SOCKADDR*)&inAddr, sizeof(inAddr)) != 0){
		cout<<"Error connect \n";
		exit(1);
	}
	
		cout<<"Connected \n";
		char msg[256] = "it's client";
		send(csocket, msg, sizeof(msg), NULL );
		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler, NULL, NULL, NULL);
		//char msg1[256];
		string str;
		while(true){
			getline(cin, str);
			int strSize = str.size();
			send(csocket, (char*)&strSize, sizeof(int), NULL);
			send(csocket, str.c_str(), sizeof(str), NULL);
			Sleep(20);
		}
	system("pause");
	return 0;
}
