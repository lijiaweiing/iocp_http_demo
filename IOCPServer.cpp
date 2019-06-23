#include "IOCPServer.h"

// 初始化Socket
bool Server::_InitializeListenSocket()
{
	// AcceptEx 和 GetAcceptExSockaddrs 的GUID，用于导出函数指针
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	// 服务器地址信息，用于绑定Socket
	struct sockaddr_in ServerAddress;

	// 生成用于监听的Socket的信息
	listensocket = new _PER_SOCKET_CONTEXT;
	listensocket->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	// 填充地址信息
	ZeroMemory((char*)& ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(9999);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定一个端口
	bind(listensocket->m_Socket, (struct sockaddr*) & ServerAddress, sizeof(ServerAddress));
	//进行监听
	listen(listensocket->m_Socket, SOMAXCONN);

	for (int i = 0; i < 10; i++) {

	}
	return false;
}

bool Server::_InitializeIOCP()
{
	m_hIOCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == m_hIOCompletionPort) {
		return false;
	}
	m_nThreads = 8;
	// 为工作者线程初始化句柄
	m_phWorkerThreads = new HANDLE[m_nThreads];

	return true;
}

void Server::start()
{
}
