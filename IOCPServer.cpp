#include "IOCPServer.h"

// ��ʼ��Socket
bool Server::_InitializeListenSocket()
{
	// AcceptEx �� GetAcceptExSockaddrs ��GUID�����ڵ�������ָ��
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	// ��������ַ��Ϣ�����ڰ�Socket
	struct sockaddr_in ServerAddress;

	// �������ڼ�����Socket����Ϣ
	listensocket = new _PER_SOCKET_CONTEXT;
	listensocket->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	// ����ַ��Ϣ
	ZeroMemory((char*)& ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(9999);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	//��һ���˿�
	bind(listensocket->m_Socket, (struct sockaddr*) & ServerAddress, sizeof(ServerAddress));
	//���м���
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
	// Ϊ�������̳߳�ʼ�����
	m_phWorkerThreads = new HANDLE[m_nThreads];

	return true;
}

void Server::start()
{
}
