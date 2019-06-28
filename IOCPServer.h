#include <winsock2.h>
#include <MSWSock.h>
#include<Windows.h>
#include<vector>
#pragma comment(lib,"ws2_32.lib")
#define CONTAINING_RECORD(address, type, field) ((type *)( \
                                                  (PCHAR)(address) - \
                                                  (ULONG_PTR)(&((type *)0)->field)))

typedef enum _OPERATION_TYPE
{
	ACCEPT_POSTED,                     // 标志投递的Accept操作
	SEND_POSTED,                       // 标志投递的是发送操作
	RECV_POSTED,                       // 标志投递的是接收操作
	NULL_POSTED                        // 用于初始化，无意义

}OPERATION_TYPE;
typedef struct _PER_IO_CONTEXT
{
	// 每一个重叠网络操作的重叠结构(针对每一个Socket的每一个操作，都要有一个)              
	OVERLAPPED     m_Overlapped;
	// 这个网络操作所使用的Socket
	SOCKET         m_sockAccept;
	// WSA类型的缓冲区，用于给重叠操作传参数的
	WSABUF         m_wsaBuf;
	// 这个是WSABUF里具体存字符的缓冲区
	//char           m_szBuffer[MAX_BUFFER_LEN];
	// 标识网络操作的类型(对应上面的枚举)
	OPERATION_TYPE m_OpType;
};

typedef struct _PER_SOCKET_CONTEXT
{
	// 每一个客户端连接的Socket
	SOCKET      m_Socket;
	// 客户端的地址
	SOCKADDR_IN m_ClientAddr;
};
class Server {
private:
	HANDLE           m_hShutdownEvent;
	//DWORD WINAPI _WorkerThread(LPVOID lpparam);
	bool  _PostAccept();
	HANDLE* m_phWorkerThreads;             // 工作者线程的句柄指针
	int		m_nThreads;                    // 生成的线程数量
	HANDLE m_hIOCompletionPort;
	_PER_SOCKET_CONTEXT *listensocket;
private:
	bool _InitializeListenSocket();
	bool _InitializeIOCP();
public:
	void start();
};