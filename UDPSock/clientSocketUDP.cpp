#pragma comment(lib, ws2_32.lib)
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

int main(int argc, char** argv) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1);
	if(WSAStartup(DLLVersion, &wsaData) != 0){
		cout<<"Error \n";
		exit(1);
	}
	int port;
	
	SOCKADDR_IN inAddr;
	inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = htons(1234);
	char msg[256];
	cin>>msg;
	SOCKET socketUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int send_bytes = sendto(socketUDP, (const char*)msg, sizeof(msg), 0, (SOCKADDR*)&inAddr, sizeof(SOCKADDR_IN));
	if(send_bytes != sizeof(msg)){
		cout<<"failed send packet; value = "<<send_bytes;
	}
	char msg1[256];
	int err = recvfrom(socketUDP,(char*)msg1, sizeof(msg1),0,0,0);
	if(err > 0){
		cout<<msg1<<endl;
	}
	closesocket(socketUDP);
		system("pause");
	return 0;
}
