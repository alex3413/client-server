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
	inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = htons(1111);
	
	SOCKET csocket = socket(AF_INET, SOCK_STREAM, NULL);
	
	if(connect(csocket, (SOCKADDR*)&inAddr, sizeof(inAddr)) != 0){
		cout<<"Error connect \n";
	}
	else 
		cout<<"Connected \n";
	system("pause");
	return 0;
}
