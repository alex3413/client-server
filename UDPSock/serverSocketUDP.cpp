#pragma comment(lib, ws2_32.lib)
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

inline bool InitializeSockets() {
        
        WSADATA WsaData;
        WORD DLLVersion = MAKEWORD(2,1);
        return WSAStartup( DLLVersion, &WsaData ) == NO_ERROR;
      
        return true;
    }

//inline void ShutdownSockets(){
//        WSACleanup();
    //}
    
void receivData(SOCKET sock){
	SOCKET socketUDP = sock; //socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	char msg[64] = "Ok";
	while (true){
		char packet[256];
		int maxPacketSize = sizeof(packet);
		
		SOCKADDR_IN fromAddres;
		int addresLength = sizeof(fromAddres);
		Sleep(5000);
		int receivedBytes = recvfrom(socketUDP, (char*)packet, maxPacketSize, 0, (SOCKADDR*)&fromAddres, &addresLength);
		if(receivedBytes<0){
			cout<<"recv failed: "<<WSAGetLastError()<<endl;
		//	closesocket(sock);
		//	WSACleanup();
		}
		
		int send_bytes = sendto(socketUDP, (const char*)msg, sizeof(msg), 0, (SOCKADDR*)&fromAddres, sizeof(SOCKADDR_IN));
		if(send_bytes != sizeof(msg)){
			cout<<"failed send packet; value = "<<send_bytes;
		}	
		
		int fromPort = ntohs(fromAddres.sin_port);
		cout<<packet<<" port: "<<fromPort<<endl;
	}
}
int main(int argc, char** argv) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1);
	if(WSAStartup(DLLVersion, &wsaData) != 0){
		cout<<"Error \n";
		exit(1);
	}
/*	if(!InitializeSockets()){
		cout<<"Error \n";
		exit(1);
	}
*/	int port;
		
	SOCKADDR_IN inAddr;
	inAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = htons(1234);
	
	SOCKET socketUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (bind(socketUDP, (SOCKADDR*)&inAddr, sizeof(inAddr)) < 0){
		cout<<"failed bind socket\n";
	}
	
	DWORD nonBlocking = 1;
	if(ioctlsocket(socketUDP, FIONBIO, &nonBlocking) != 0){
		cout<<"failed to set non-blocking"<<endl;
	}
	
	receivData(socketUDP );
		
	system("pause");
	return 0;
	
}
