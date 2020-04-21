#pragma comment(lib, ws2_32.lib)
#include <iostream>
#include <winsock2.h>
#include <cstdlib>


using namespace std;
int main(int argc, char** argv) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1);
	if(WSAStartup(DLLVersion, &wsaData) != 0){
		cout<<"Error \n";
		exit(1);
	}
	
	SOCKADDR_IN inAddr;
	inAddr.sin_addr.s_addr = inet_addr("192.168.1.9");
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = htons(1111);
	
	SOCKET ssocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(ssocket, (SOCKADDR*)&inAddr, sizeof(inAddr));
	listen(ssocket, 3);
	
	int sizeSock = sizeof(inAddr);
		
	SOCKET connection;
	connection = accept(ssocket, (SOCKADDR*)&inAddr, &sizeSock);
	
	
	if(connection == 0){
	
		cout<<"Error connect ssock \n";
	}
	else{
		cout<<"Client Connected \n";
	}
	
	system("pause");
	return 0;
}
