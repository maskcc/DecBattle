#include <string>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <lua.hpp>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <vector>
using namespace std;

int test12()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in connsvr;
	connsvr.sin_family = AF_INET;
	connsvr.sin_port = htons(10077);
	inet_aton("127.0.0.1", &connsvr.sin_addr);
	socklen_t len = sizeof(sockaddr);
	int ret = connect(sock, (struct sockaddr*)&connsvr, len);
	cout << "connect succed, ret is:" << ret <<endl; 

	typedef struct BaseMsg_t
	{
		uint32_t sz;
		void *msg;

	}BaseMsg;

	char sendBuff[1024] = {0};
	char *bin = sendBuff;
	char buff[50] = {"are you ok, nartuo~~~"};
	BaseMsg msg;
	msg.sz = sizeof(buff);
	msg.msg = (void*)buff;

	int nsz = htonl(msg.sz);
	memcpy(bin, (char*)(&nsz), 4);
	memcpy(bin+ 4, msg.msg, sizeof(buff));
	cout <<msg.sz << msg.msg << "sizeof buff" << sizeof(buff) << endl;
	write(sock, (char*)sendBuff, msg.sz + 4);
	write(sock, (char*)sendBuff, msg.sz + 4);
	write(sock, (char*)sendBuff, msg.sz + 4);
    sleep(1);

}
int test6(int sock)
{
/*	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in connsvr;
	connsvr.sin_family = AF_INET;
	connsvr.sin_port = htons(10077);
	inet_aton("127.0.0.1", &connsvr.sin_addr);
	socklen_t len = sizeof(sockaddr);
	int ret = connect(sock, (struct sockaddr*)&connsvr, len);
	cout << "connect succed, ret is:" << ret <<endl; 
*/
	typedef struct BaseMsg_t
	{
		uint32_t sz;
		void *msg;

	}BaseMsg;

	char sendBuff[1024] = {0};
	char *bin = sendBuff;
	char buff[50] = {"are you ok, nartuo~~~"};
	BaseMsg msg;
	msg.sz = sizeof(buff);
	msg.msg = (void*)buff;

	int nsz = htonl(msg.sz);
	memcpy(bin, (char*)(&nsz), 4);
	memcpy(bin+ 4, msg.msg, sizeof(buff));
	//cout <<msg.sz << msg.msg << "sizeof buff" << sizeof(buff) << endl;
    cout << sock << endl;
	write(sock, (char*)sendBuff, msg.sz + 4);
	write(sock, (char*)sendBuff, msg.sz + 4);
	write(sock, (char*)sendBuff, msg.sz + 4);

}
int test5()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in svr;
	socklen_t svrlen;
	svr.sin_family = AF_INET;
	svr.sin_port = htons(10099);
	svr.sin_addr.s_addr = htonl(INADDR_ANY);

	svrlen = sizeof(svr);
	bind(sockfd, (struct sockaddr*)&svr, svrlen);
	if(0 == fork())
	{
		for(;;){
			listen(sockfd, 5);
			cout << "server is listend!" << endl;
			accept(sockfd, NULL, NULL);
			cout << "a connection come!" << endl;
			break;
		}
		wait();
	}else
	{
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		sleep(3);
		struct sockaddr_in connsvr;
		connsvr.sin_family = AF_INET;
		connsvr.sin_port = htons(10099);
		inet_aton("127.0.0.1", &connsvr.sin_addr);
		socklen_t len = sizeof(sockaddr);
		int ret = connect(sock, (struct sockaddr*)&connsvr, len);
		cout << "connect succed, ret is:" << ret <<endl; 

		int sock2 = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in connsvr2;
		connsvr2.sin_family = AF_INET;
		connsvr2.sin_port = htons(10098);
		inet_aton("127.0.0.1", &connsvr2.sin_addr);
		len = sizeof(sockaddr);
		ret = connect(sock2, (struct sockaddr*)&connsvr2, len);
		cout << "connect2 succed, ret is:" << ret <<endl; 

	}
}

int test4()
{
	int arr[1024];
	int rem = 1;
	memset(arr, 1, 1024 * sizeof(int));
	memset(arr, rem, 1024 * sizeof(int));
	cout << arr[0] <<endl;



}
int test3()
{
	char *cur;
	char buff[1024] = "123456789";
	cur = buff;
	cout << "sizeof cur is>>" << sizeof(cur) <<endl;
	cout << "strlen cur is>>" << strlen(cur) << endl;

	cur = cur + 3;
	cout << "after moved 3 sizeof cur is>>" << sizeof(*cur) << endl;
	cout << "after moved 3 strlen cur is>>" << strlen(cur) << endl;

}

int test2()
{
	char buff[1024] = {0};
	int net = htonl(33);
	memcpy(buff, (char*)(&net), 4);
	cout << "net is:" << net <<endl;
	cout << "buff is:" <<buff <<endl;
	cout << "int buff:" << *((int*)(char*)buff) << endl;
	cout << "changed buff:" << ntohl(*((int*)(char*)buff)) << endl;

}
int test()
{
	for(;;){
		if(1 > 2)
		{return -1;}
		break;
		cout << "after break" << endl;
	}

}


using namespace std;
class Socket
{
	public:
		Socket()
		{
			m_addr = "";
			m_port = 99;
			m_fd = -1;
			m_connType = 1;
			m_idx = -1;
			m_lastRecvTime = 0; 

		}


	protected:
	protected:
		string   m_addr;   
		uint16_t m_port;   
		int32_t  m_fd;     
		int32_t m_connType; 
		int32_t m_idx;     

		uint64_t m_lastRecvTime; 

};
void test7()
{
	Socket *sock = new Socket[65535];
	sleep(40);


}


	int	
initSock(char* listenip, int32_t port)
{     
	/*start listen port*/
	int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr = {0};   
	socklen_t addrlen = sizeof(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port =  htons(port);
	if(0 == inet_aton(listenip, &servaddr.sin_addr))
	{        
		return -1;
	}
	if(0 != bind(sockfd, (struct sockaddr* )&servaddr, addrlen))
	{
		return -1;
	}
	if(0 != listen(sockfd, 5))
	{
		return -1;
	}

	return sockfd;
}
typedef struct epoll_event EPOLL_EV;
int initEpoll(int fd)
{
	EPOLL_EV ev = {0};
	int efd = epoll_create(1024);
	ev.events = EPOLLIN;
	ev.data.fd = efd;
	epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
	return efd;

}
void test8()
{
	int sockfd = initSock("0.0.0.0", 9988);
	int pfd = initEpoll(sockfd);
	int fds[1024] = {0};
	int idx = 0;
	EPOLL_EV ev[64] = {0};
	for(;;)
	{
		memset(ev, 0, sizeof(EPOLL_EV) * 64);
		int n = epoll_wait(pfd, ev, 64, -1);
		while(n > 0)
		{
			if(ev[n - 1].events & EPOLLIN != 0)
			{
				int xx = accept(sockfd, NULL, NULL);
				cout << "靠 fd " <<xx << endl;
				--n;
			}
		}


	}





}

static void
sp_nonblocking(int32_t fd) {
	int32_t flag = fcntl(fd, F_GETFL, 0);
	if ( -1 == flag ) {
		return;
	}

	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}
void* test9(void*)
{
	int port = 0;
	char *addr;
	int type = 0;
	if(0 == type)
{
	port = 10077;	
	addr = "127.0.0.1";
}
	else if(1 == type)
{
	port = 10077;	
	addr = "120.25.92.230";

}
	else if(2 == type)
{
	port = 18103; 
	addr = "127.0.0.1";
}
	else if(3 == type)
{
	port = 10077;	
	addr = "127.0.0.1";

}
	else if(4 == type)
{
	port = 10077;
	addr = "127.0.0.1";

}
	vector<int> List;
	for(int c = 0; c < 3; c++)
	{
		int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0)
		{
			perror(strerror(errno));
			exit(-1);
		}
		List.push_back(sockfd);
	}
	struct sockaddr_in servaddr = {0};   
	socklen_t addrlen = sizeof(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port =  htons(port);
	if(0 == inet_aton(addr, &servaddr.sin_addr))
	{        
		perror(strerror(errno));
		exit(-1);
	}

	size_t len = sizeof(servaddr);
	for(int c = 0; c < List.size(); c++)
	{
		int ret = connect(List[c], (struct sockaddr*)& servaddr, len);
		if(ret < 0)
		{
			perror(strerror(errno));
			exit(-1);
		}
        test6(List[c]);
	}

}

void test10()
{
	int threads = 1;
	pthread_t th[threads];
	for(int c = 0; c < threads; c++ )
		pthread_create(&th[c],NULL, test9, NULL);
	
	for(int c = 0; c < threads; c++ )
		pthread_join(th[c], NULL);
	sleep(20);
	cout << "i am alive" <<endl;

}
void testlua()
{
	//	lua_State *L = luaL_newstate();
	//int r = luaL_dofile(l, "bootstrap.lua");
	//   int r = luaL_loadfile(l, "bootstrap.lua");

	//  printf("result is %d\n", r);
	// perror(strerror(errno));
	// r = lua_pcall(l, 0, LUA_MULTRET, 0);
	// printf("result is %d\n", r);
	// perror(strerror(errno));


	//	luaL_openlibs(L);

	//	int errorCode = 0;
	//if(errorCode != luaL_dofile(L,"bootstrap.lua"))
	// {
	//   puts(lua_tostring(L, -1));
	//  abort();
	//}


	// Clean up the lua context
	//	lua_close(L);

}
int main() {
	//test7();
	//test8();
	//test12();
    test10();
}
