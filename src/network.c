#include "network.h"

int net_start(void) {
	int port=80;
	#if OS == Windows
		WSADATA wsaData; /*  The WSADATA structure contains information about
						   the Windows Sockets implementation. */

		if (WSAStartup(MAKEWORD(1, 1), &wsaData)) {
			return 0;
		}
				/* The WSAStartup function initiates use of
				  WS2_32.DLL by a process, and returns zero if successful. */
	#endif

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	return 1;
}

char* get_ip(const char* hostname) {
	serv = gethostbyname(hostname);
	if (serv) {
		server.sin_addr = *(struct in_addr*) serv->h_addr;
		server.sin_addr.s_addr = inet_addr(inet_ntoa(server.sin_addr));
		memset(&(server.sin_zero), '\0', 8);
	}
	return inet_ntoa(server.sin_addr);
}

int net_socket() {
	return socket(AF_INET, SOCK_STREAM, 0);
}

int net_connect(int sd) {
	int cnt=0;
	if (sd!=INVALID_SOCKET) // Check that the socket connected
		cnt = connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
	if (!cnt)
		return 1;
	else
		return 0;
}

void net_send(const char* getstr, int sd) {
	send(sd, getstr, strlen(getstr), 0);
}

char net_recieve(int sd) {
	char buf[1];
	int rc=0;
	rc=recv(sd, buf, 1, 0);
	if (buf[0]>127||buf[0]<0) { //strip out unicode/unfriendly characters
	   buf[0]='\r';
	}
	if (rc)
		return buf[0];
	else
		return -1;
}

int net_stop(int sd) {
	#if OS == Windows
		closesocket(sd);
		WSACleanup( );
	#else
		close(sd);
	#endif
	return 1;
}