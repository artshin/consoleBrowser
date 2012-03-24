#define Windows 1
#define Unix 2
#define OS Windows

#if OS == Windows
   #include <winsock.h>
   #pragma comment(lib, "wsock32.lib")
#else
   #include <sys/socket.h>
   #include <netinet/in.h>
#endif

int net_start(void);
char* get_ip(const char*);
int net_stop(int);
int net_connect(int);
int net_socket();
void net_send(const char*,int);
char net_recieve(int);

struct sockaddr_in server;
struct hostent* serv;